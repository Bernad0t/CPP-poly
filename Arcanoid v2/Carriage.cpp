#include "./Carriage.h"

Carriage::Carriage(Vector2f position, int size_x, int speed) : myCarriage(Vector2f(size_x, 10)) {
	this->position = position;
	isMoveLeft = false;
	isMoveRight = false;
	this->speed = speed;
	size = Vector2f(size_x, 10);
	myCarriage.setPosition(position);
	myCarriage.setFillColor(Color::Blue);
	myCarriage.setOrigin(Vector2f(size.x / 2, 0));
	for (int i = 0; i < 10; i++) {
		SectionDirection[i] = Vector2f(-0.7 + i * 0.7 / 5, -pow(1 - pow(-0.7 + i * 0.7 / 5, 2), 0.5));
	}
}

void Carriage::MoveLeft(float dtAsSeconds) {
	position = Vector2f(position.x - dtAsSeconds * speed, position.y);
	myCarriage.setPosition(position);
}

void Carriage::MoveRight(float dtAsSeconds) {
	position = Vector2f(position.x + dtAsSeconds * speed, position.y);
	myCarriage.setPosition(position);
}

void Carriage::update(float dtAsSeconds) {
	if (isMoveLeft)
		MoveLeft(dtAsSeconds);
	if (isMoveRight)
		MoveRight(dtAsSeconds);
}

void Carriage::ProcessCoallision(Ball& ball) {
	ball.direction = SectionDirection[(int)((ball.position.x - position.x + size.x / 2 + ball.size / 2) / (size.x / 10 + 1))];
}