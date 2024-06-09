#include "./Square.h"


Square::Square(int size, Vector2f position, bool ContainBonus) : myQuads(Vector2f(size, size)) {
	this->position = position;
	this->size = size;
	this->ContainBonus = ContainBonus;
	StatusLive = true;
	hp = rand() % 3;
	myQuads.setOrigin(Vector2f(size / 2, size / 2));
	myQuads.setPosition(position);
	ChangeColor(colors[hp]);
}

void Square::ChangeColor(char color) {
	switch (color) {
	case 'r':
		myQuads.setFillColor(Color::Red);
		break;
	case 'g':
		myQuads.setFillColor(Color::Green);
		break;
	case 'y':
		myQuads.setFillColor(Color::Yellow);
		break;
	}
}

void Square::ProcessCollision(Ball& ball) {
	if (fabs(this->position.x - ball.position.x) == this->size / 2 + ball.size / 2 && ball.direction.x != 0) {
		ball.direction = Vector2f(-ball.direction.x, ball.direction.y);
	}
	else {
		ball.direction = Vector2f(ball.direction.x, -ball.direction.y);
	}
	/*ball.direction = Vector2f(fabs(position.y - ball.position.y) < fabs(position.x - ball.position.x) ? -ball.direction.x :
		ball.direction.x, fabs(position.y - ball.position.y) < fabs(position.x - ball.position.x) ? ball.direction.y : -ball.direction.y);*/
	ProcessSpecial(ball);
}

DefaultSquare::DefaultSquare(int size, Vector2f position, bool ContainBonus) : Square(size, position, ContainBonus) {}

void DefaultSquare::ProcessSpecial(Ball& ball) {
	hp -= 1;
	if (hp == -1)
		StatusLive = false;
	else
		ChangeColor(colors[hp]);
	if (ContainBonus) {
		ContainBonus = false;
		// обработка для бонуса
	}
}

upSpeedSquare::upSpeedSquare(int size, Vector2f position, bool ContainBonus) : Square(size, position, ContainBonus) {
	myQuads.setOutlineThickness(3);
	myQuads.setOutlineColor(sf::Color(250, 150, 100));
}

void upSpeedSquare::ProcessSpecial(Ball& ball) {
	hp -= 1;
	if (hp == -1)
		StatusLive = false;
	else
		ChangeColor(colors[hp]);
	if (ball.speed <= 480)
		ball.speed += ball.speed * 0.2;
}

UnIndestructibleSquare::UnIndestructibleSquare(int size, Vector2f position, bool ContainBonus) : Square(size, position, ContainBonus) {
	myQuads.setFillColor(Color::White);
}

void UnIndestructibleSquare::ProcessSpecial(Ball& ball) {

}