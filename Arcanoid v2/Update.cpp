#include "./Engine.h"

float IntersectionAxis(float a, float b, float x, float y, float x_, float y_, int halfSizeBall, int width) { // (x - x_) / a = (y - y_) / b
	if (x_ != -1) {
		if (a != 0)
			return -b * (x - x_) / a + y;
		else
			return b < 0 ? halfSizeBall : width - halfSizeBall;
	}

	if (y_ != -1) {
		if (b != 0)
			return -a * (y - y_) / b + x;
		else
			return a < 0 ? halfSizeBall : width - halfSizeBall;
	}
}

float IntersectionSquare(float a, float b, float x, float y, float x_, float y_, int halfSizeBall, int width) { // (x - x_) / a = (y - y_) / b
	if (x_ != -1) {
		if (a != 0)
			return -b * (x - x_) / a + y;
		else
			return b < 0 ? width - halfSizeBall : width + halfSizeBall;
	}

	if (y_ != -1) {
		if (b != 0)
			return -a * (y - y_) / b + x;
		else
			return a < 0 ? width - halfSizeBall : width + halfSizeBall;
	}
}

void Engine::ProcessBoardScreen(Ball& ball) {
	if (ball.position.x <= ball.size / 2 || ball.position.x >= resolution.x - ball.size / 2 || ball.position.y <= ball.size / 2 || ball.position.y >= resolution.y - ball.size / 2) {
		if (ball.position.y < resolution.y - ball.size / 2)
		{
			if (ball.position.y == ball.size / 2 || ball.position.y == resolution.y - ball.size / 2)
				ball.direction.y = -ball.direction.y;
			else {
				float x_ = IntersectionAxis(ball.direction.x, ball.direction.y, ball.position.x, ball.position.y, -1,
					ball.direction.y < 0 ? ball.size / 2 : resolution.y - ball.size / 2, ball.size / 2, resolution.x);
				float y_ = IntersectionAxis(ball.direction.x, ball.direction.y, ball.position.x, ball.position.y,
					ball.direction.x < 0 ? ball.size / 2 : resolution.x - ball.size / 2, -1, ball.size / 2, resolution.x);
				ball.position = Vector2f(y_ <= ball.size / 2 || y_ >= resolution.y - ball.size / 2 ? x_ : (ball.direction.x < 0 ? ball.size / 2 : resolution.x - ball.size / 2),
					x_ <= ball.size / 2 || x_ >= resolution.x - ball.size / 2 ? y_ : (ball.direction.y < 0 ? ball.size / 2 : resolution.y - ball.size / 2));
				ball.direction = Vector2f(ball.position.x == ball.size / 2 || ball.position.x == resolution.x - ball.size / 2 ? -ball.direction.x : ball.direction.x,
					ball.position.y == ball.size / 2 || ball.position.y == resolution.y - ball.size / 2 ? -ball.direction.y : ball.direction.y);
			}
		}
		if (ball.position.y >= resolution.y) {
			for (int i = 0; i < bonuses.size(); i++)
				bonuses[i]->DropBonus();
			ball.status = false;
			score -= 1;
			bool liveBall = false;
			for (int i = 0; i < balls.size(); i++) {
				if (ball.status == true) {
					liveBall = true;
					break;
				}
			}
			if (!liveBall) {
				defeats++;
				score = 0;
				balls.clear();
				balls.push_back(Ball(10, Vector2f(395, 780), originalSpeedBall));
				carriage.myCarriage.setPosition(Vector2f(375, 790));
				carriage.position = Vector2f(375, 790);
			}
		}
	}
}

void Engine::ProcessBallSquare(Ball& ball) {
	int sizeSquare = squares[0][0]->size;
	if ((int)(ball.position.y - ball.size / 2) / (sizeSquare + spaceBetweenSquares) <= squares.size() - 1) {
		Square* thisSquare = squares[(int)(ball.position.y - ball.size / 2) / (sizeSquare + 20)][(int)ball.position.x / (sizeSquare + spaceBetweenSquares)];
		if (thisSquare->StatusLive != false && fabs(thisSquare->position.x - ball.position.x) <= ball.size / 2 + thisSquare->size / 2 &&
			fabs(thisSquare->position.y - ball.position.y) <= ball.size / 2 + thisSquare->size / 2) {
			score++;
			float x_ = IntersectionSquare(ball.direction.x, ball.direction.y, ball.position.x, ball.position.y, -1,
				ball.direction.y < 0 ? thisSquare->position.y + thisSquare->size / 2 + ball.size / 2
				: thisSquare->position.y - thisSquare->size / 2 - ball.size / 2, ball.size / 2, thisSquare->size);
			float y_ = IntersectionSquare(ball.direction.x, ball.direction.y, ball.position.x, ball.position.y,
				ball.direction.x < 0 ? thisSquare->position.x + thisSquare->size / 2 + ball.size / 2 :
				thisSquare->position.x - thisSquare->size / 2 - ball.size / 2, -1, ball.size / 2, thisSquare->size);
			ball.position = Vector2f(y_ < thisSquare->position.y - thisSquare->size / 2 - ball.size / 2 ||
				y_ > thisSquare->position.y + thisSquare->size / 2 + ball.size / 2 ? x_ : (ball.direction.x < 0 ?
					thisSquare->position.x + thisSquare->size / 2 + ball.size / 2 : thisSquare->position.x - thisSquare->size / 2 - ball.size / 2),
				x_ < thisSquare->position.x - thisSquare->size / 2 - ball.size / 2 || x_ > thisSquare->position.x + thisSquare->size / 2 + ball.size / 2 ?
				y_ : (ball.direction.y < 0 ? thisSquare->position.y + thisSquare->size / 2 + ball.size / 2 :
					thisSquare->position.y - thisSquare->size / 2 - ball.size / 2));
			if (thisSquare->ContainBonus) {
				thisSquare->ContainBonus = false;
				for (int i = 0; i < bonuses.size(); i++) {
					if (bonuses[i]->position.x == thisSquare->position.x && bonuses[i]->position.y == thisSquare->position.y) {
						bonuses[i]->moving = true;
						break;
					}
				}
			}
			thisSquare->ProcessCollision(ball);
		}
	}
}

void Engine::update(float dtAsSeconds) {
	for (int i = 0; i < bonuses.size(); i++) {
		bonuses[i]->ProcessCoallision();
		bonuses[i]->ProcessBonus();
		bonuses[i]->update(dtAsSeconds);
	}
	for (auto& ball : balls) {
		if (ball.status == false)
			continue;
		ProcessBoardScreen(ball);
		ProcessBallSquare(ball);
		if (ball.direction.y > 0 && ball.position.y >= resolution.y - carriage.size.y && ball.position.x - ball.size / 2 > carriage.position.x - carriage.size.x / 2 &&
			ball.position.x + ball.size / 2 < carriage.position.x + carriage.size.x / 2)
			carriage.ProcessCoallision(ball);
		ball.Move(dtAsSeconds);
	}
	carriage.update(dtAsSeconds);
	carriage.position = Vector2f(carriage.position.x < carriage.size.x / 2 ? carriage.size.x / 2 :
		(carriage.position.x > resolution.x - carriage.size.x / 2 ? resolution.x - carriage.size.x / 2 : carriage.position.x), carriage.position.y);
}