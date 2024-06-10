#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

using namespace sf;
using namespace std;

class Bonus {
protected:
	void check_square_in_array(vector<Vector2f>& array_user_coursor, Vector2f arr_position);
public:
	virtual void process_bonus(vector<Vector2f>& array_user_coursor, Square board[13][13], Vector2f arr_position)=0;
};

class Bomb : public Bonus {
public:
	void process_bonus(vector<Vector2f>& array_user_coursor, Square board[13][13], Vector2f arr_position) override;
};

class Recolour : public Bonus {
public:
	void process_bonus(vector<Vector2f>& array_user_coursor, Square board[13][13], Vector2f arr_position) override;
};