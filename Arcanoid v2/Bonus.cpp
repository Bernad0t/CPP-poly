#include "./Engine.h"

Engine::Bonus::Bonus(Vector2f position, Engine* engine) : myBonus(5) {
	this->engine = engine;
	this->position = position;
	moving = false;
	start = false;
	size = 10;
	speed = 200;
	myBonus.setPosition(position);
	myBonus.setOrigin(Vector2f(size / 2, size / 2));
}

void Engine::Bonus::update(float dtAsSeconds) {
	if (moving) {
		position.y = position.y + speed * dtAsSeconds;
		myBonus.setPosition(position);
	}

}

void Engine::Bonus::ProcessCoallision() {
	if (moving) {
		if (fabs(position.x - engine->carriage.position.x) <= size / 2 + engine->carriage.size.x && fabs(position.y - engine->carriage.position.y)
			<= size / 2 + engine->carriage.size.y) {
			start = true;
			moving = false;
		}
		else if (position.y > engine->resolution.y + size / 2)
			moving = false;
	}
}

Engine::upSpeedBall::upSpeedBall(Vector2f position, Engine* engine) : Bonus(position, engine) {
	myBonus.setFillColor(Color::Green);
}

void Engine::upSpeedBall::DropBonus() {
	start = false;
}

void Engine::upSpeedBall::ProcessBonus() {
	if (start) {
		for (int i = 0; i < engine->balls.size(); i++)
			if (engine->balls[i].speed < engine->originalSpeedBall * 1.5)
				engine->balls[i].speed *= 1.5;
		start = false;
	}
}

Engine::extandCarriage::extandCarriage(Vector2f position, Engine* engine) : Bonus(position, engine) {
	myBonus.setFillColor(Color::Blue);
}

void Engine::extandCarriage::ProcessBonus() {
	if (start) {
		if (engine->carriage.size.x < engine->originalSizeCarriage * 1.25) {
			engine->carriage.size.x *= 1.25;
			engine->carriage.myCarriage.setSize(Vector2f(engine->carriage.size.x, engine->carriage.size.y));
		}
	}
}

void Engine::extandCarriage::DropBonus() {
	if (start) {
		engine->carriage.size.x /= 1.25;
		engine->carriage.myCarriage.setSize(Vector2f(engine->carriage.size.x, engine->carriage.size.y));
		start = false;
	}
}

Engine::additionalBottom::additionalBottom(Vector2f position, Engine* engine) : Bonus(position, engine) {
	myBonus.setFillColor(Color::Magenta);
}

void Engine::additionalBottom::ProcessBonus() {
	if (start) {
		for (int i = 0; i < engine->balls.size(); i++) {
			if (engine->balls[i].position.y >= engine->resolution.y - engine->balls[i].size / 2 && engine->balls[i].status != false &&
				engine->balls[i].direction.y > 0) {
				engine->balls[i].direction.y = -engine->balls[i].direction.y;
				start = false;
			}
		}
	}
}

void Engine::additionalBottom::DropBonus() {}

Engine::changeDirectionBall::changeDirectionBall(Vector2f position, Engine* engine) : Bonus(position, engine) {
	myBonus.setFillColor(Color::Red);
}

void Engine::changeDirectionBall::ProcessBonus() {
	if (start) {
		int chance = rand() % 100;
		if (chance < 3) {
			for (int i = 0; i < engine->balls.size(); i++) {
				float direction_x = (float)rand() / RAND_MAX;
				engine->balls[i].direction = Vector2f(pow(-1, rand() % 2) * direction_x, pow(-1, rand() % 2) * pow(1 - direction_x * direction_x, 0.5));
			}
			start = false;
		}
	}
}

void Engine::changeDirectionBall::DropBonus() {}