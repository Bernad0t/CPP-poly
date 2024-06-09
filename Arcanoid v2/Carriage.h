#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "./Ball.h"

using namespace sf;
using namespace std;

class Carriage {
	int speed;
	Vector2f SectionDirection[10];
public:
	bool isMoveLeft;
	bool isMoveRight;

	Vector2f size;// x = width, y = heigth
	Vector2f position;
	RectangleShape myCarriage;

	Carriage(Vector2f position, int size_x, int speed);

	void MoveLeft(float dtAsSeconds);
	void MoveRight(float dtAsSeconds);

	void update(float dtAsSeconds);

	void ProcessCoallision(Ball& ball);
};
