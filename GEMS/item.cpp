#include "item.h"

Square::Square(int x, int y, int size, char colour) : position(x, y), myQuads(Vector2f(size, size)) {//(x, y) - центр квадратика
	this->size = size;
	this->colour = colour;
	this->speed = 400;
	this->moving = false;
	order_move.push_back(0);
	order_move.push_back(0);
	move_to = position;
	myQuads.setOrigin(Vector2f(size / 2, size / 2));
	myQuads.setPosition(Vector2f(position.x, position.y));
	switch (colour) {
	case 'b':
		myQuads.setFillColor(Color{ 0, 0, 255, 255 });
		break;
	case 'r':
		myQuads.setFillColor(Color::Red);
		break;
	case 'g':
		myQuads.setFillColor(Color{ 0, 255, 0, 127 });
		break;
	case 'y':
		myQuads.setFillColor(Color::Yellow);
		break;
	case 'p':
		myQuads.setFillColor(Color::Magenta);
		break;

	case 'w':
		//myQuads.setFillColor(Color{ 255, 255, 255, 255 });
		return;
	}
}

Square::Square(){}

void Square::is_move(Vector2f to_position) {
	move_to = to_position;
	moving = true;
	order_move[0] = (to_position.x - position.x) / (size + size / 2);
	order_move[1] = (to_position.y - position.y) / (size + size / 2);
}

void Square::stop_move() {
	moving = false;
	order_move[0] = 0;
	order_move[1] = 0;
	position = move_to;
}

void Square::update(float elapsedTime) {
	position = Vector2f(position.x + speed * elapsedTime * order_move[0], position.y + speed * elapsedTime * order_move[1]);
	if (((move_to.x - position.x) * order_move[0]) < 0 ||
		((move_to.y - position.y) * order_move[1]) < 0 ||
		position.x == move_to.x && position.y == move_to.y) {
		stop_move();
	}
	myQuads.setPosition(position);
}

bool Square::get_moving() {
	return moving;
}

Vector2f Square::get_move_to() {
	return move_to;
}