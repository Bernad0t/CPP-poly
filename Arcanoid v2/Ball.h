#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
public:
	Ball(int size, Vector2f position, int speed);

	int size;
	CircleShape myBall;
	Vector2f position;
	Vector2f direction; // ���������� �����. �� ������ ������ ���� 1. X value = �������� �� �, Y ���������� 
	int speed;
	bool status; // dead = false; live = true

	void Move(float dtAsSeconds);
};
