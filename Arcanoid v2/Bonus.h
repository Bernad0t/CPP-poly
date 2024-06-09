#pragma once

#include <SFML/Graphics.hpp>
#include "./Engine.h"

using namespace sf;

class Bonus {
protected:
	int size;
	int speed;
	Engine* engine;
public:
	CircleShape myBonus;
	Bonus(Vector2f position, Engine* engine);

	virtual void ProcessBonus() = 0;
	virtual void DropBonus() = 0;
	Vector2f position;
	bool start;
	bool moving;
	void update(float dtAsSeconds);
};

class upSpeedBall : public Bonus {
public:
	upSpeedBall(Vector2f position, Engine* engine);

	void ProcessBonus() override;
	void DropBonus() override;
};

class extandCarriage : public Bonus {
public:
	extandCarriage(Vector2f position, Engine* engine);

	void ProcessBonus() override;
	void DropBonus() override;
};

class additionalBottom : public Bonus {
public:
	additionalBottom(Vector2f position, Engine* engine);

	void ProcessBonus() override;
	void DropBonus() override;
};