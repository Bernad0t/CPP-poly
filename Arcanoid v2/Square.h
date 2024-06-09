#pragma once

#include <SFML/Graphics.hpp>
#include "./Ball.h"

using namespace sf;

class Square {
protected:
	int hp;
	char colors[3] = { 'r', 'y', 'g' };
	void ChangeColor(char color);
public:
	bool ContainBonus;
	int size;
	Vector2f position;
	bool StatusLive;
	RectangleShape myQuads;

	Square(int size, Vector2f position, bool ContainBonus);

	virtual void ProcessSpecial(Ball& ball) = 0;

	void ProcessCollision(Ball& ball);
};

class DefaultSquare : public Square {
public:
	DefaultSquare(int size, Vector2f position, bool ContainBonus);
	void ProcessSpecial(Ball& ball) override;
};

class upSpeedSquare : public Square {
public:
	upSpeedSquare(int size, Vector2f position, bool ContainBonus);
	void ProcessSpecial(Ball& ball) override;
};

class UnIndestructibleSquare : public Square {
public:
	UnIndestructibleSquare(int size, Vector2f position, bool ContainBonus);
	void ProcessSpecial(Ball& ball) override;
};
