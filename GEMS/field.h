#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "item.h"
#include "bonuses.h"
using namespace std;
using namespace sf;

class Board {
	Bonus* bonus;
	void for_check_combination(vector<Vector2f>& checked_elements, Vector2f arr_position, int& size_bomb_destroed,
		vector<Vector2f>& recolour_elements);
	void delete_combinations(vector<Vector2f>& x_changed, vector<Vector2f>& array_user_coursor);
	void process_combination_deleted(vector<Vector2f>& x_changed);
	Square board[13][13]; // 13 на 13 поле
	char generate_random_colour(int row, int column);
	int size_part;
	void check_combination(Vector2f in_arr_pos_changed_1, vector<Vector2f>& x_changed);
	void for_check_combination(vector<Vector2f>& checked_elements, Vector2f arr_position);
	void choose_bonus(vector<Vector2f>& array_user_coursor, Vector2f arr_position);
public:
	Board(int size_screen);

	void print_board(RenderWindow& window);

	void process_mouse(vector<Vector2f>& array_user_coursor, bool & update_flag);

	void update(float elapsedTime, vector<Vector2f>& array_user_coursor);
};
