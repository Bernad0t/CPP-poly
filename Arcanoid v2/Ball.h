#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
public:
	Ball(int size, Vector2f position, int speed);

	int size;
	CircleShape myBall;
	Vector2f position;
	Vector2f direction; // направляет шарик. по модулю должен быть 1. X value = смещение по х, Y аналогично 
	int speed;
	bool status; // dead = false; live = true

	void Move(float dtAsSeconds);
};
