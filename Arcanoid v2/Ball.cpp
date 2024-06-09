#include "./Ball.h"

Ball::Ball(int size, Vector2f position, int speed) : myBall(5) {
	this->size = size;
	this->position = position;
	this->speed = speed;
	status = true;
	myBall.setOrigin(Vector2f(size / 2, size / 2));
	myBall.setPosition(position);
	myBall.setFillColor(Color::White);
	direction = Vector2f(0, -1);
}

void Ball::Move(float dtAsSeconds) {
	position = Vector2f(position.x + speed * dtAsSeconds * direction.x, position.y + direction.y * speed * dtAsSeconds);
	myBall.setPosition(position);
}