#include "field.h"

class Colour {
	char colours[6] = { 'b', 'r', 'g', 'y', 'p', 'w' };
public:
	char get_colour(int position) {
		return colours[position];
	}
};

Board::Board(int size_screen) {
	size_part = 60; //size_square + size_square / 2
	for (int row = 0; row < 13; row++) {
		for (int column = 0; column < 13; column++) {
			char colour = generate_random_colour(row, column);
			Square square((size_screen / 40) * (column + 2) + size_screen / 20 * column,
				(size_screen / 40) * (row + 2) + size_screen / 20 * row, size_screen / 20, colour);
			board[row][column] = square;
		}
	}
}

void Board::print_board(RenderWindow & window) {
	for (int row = 0; row < 13; row++) {
		for (int column = 0; column < 13; column++) {
			if (board[row][column].colour != 'w')
				window.draw(board[row][column].myQuads);
		}
	}
}

char Board::generate_random_colour(int row, int column) {
	int position_colour = rand() % 5;
	vector<char> banned_colours_for_this;
	Colour colours;
	if (row > 1 && board[row - 2][column].colour == board[row - 1][column].colour ||
		row > 0 && column > 0 && board[row - 1][column - 1].colour == board[row - 1][column].colour ||
		row > 0 && column > 0 && column < 12 && board[row - 1][column + 1].colour == board[row - 1][column].colour ||
		row > 0 && column < 12 && board[row - 1][column + 1].colour == board[row - 1][column].colour) {
		banned_colours_for_this.push_back(board[row - 1][column].colour);
	}
	if (column > 1 && board[row][column - 2].colour == board[row][column - 1].colour ||
		column > 0 && row > 0 && (board[row - 1][column - 1].colour == board[row][column - 1].colour ||
			board[row - 1][column].colour == board[row][column - 1].colour)) {
		int flag_identity = 0;
		for (int i = 0; i < banned_colours_for_this.size(); i++) {
			if (banned_colours_for_this[i] == board[row][column - 1].colour) {
				flag_identity = 1;
				break;
			}
		}
		if (flag_identity == 0) banned_colours_for_this.push_back(board[row][column - 1].colour);
	}
	while (banned_colours_for_this.size() > 0) {
		char colour = colours.get_colour(position_colour);
		for (int i = 0; i < banned_colours_for_this.size(); i++) {
			if (colour == banned_colours_for_this[i]) break;
			if (i == banned_colours_for_this.size() - 1) return colour;
		}
		position_colour = rand() % 5;
	}
	return colours.get_colour(position_colour);
}

void Board::process_mouse(vector<Vector2f>& array_user_coursor, bool & update_flag) {
	if (array_user_coursor.size() == 2) {
		Vector2f first = array_user_coursor[0];
		Vector2f second = array_user_coursor[1];
		board[(int)first.y / (size_part)][(int)first.x / (size_part)].myQuads.setRotation(0.f);
		if (pow((int)first.x / (size_part) - (int)second.x / (size_part), 2) + 
			pow((int)first.y / size_part - (int)second.y / size_part, 2) == 1 &&
			board[(int)first.y / size_part][(int)first.x / size_part].colour != 'w' &&
			board[(int)second.y / size_part][(int)second.x / size_part].colour != 'w') {
				board[(int)first.y / size_part][(int)first.x / size_part].is_move(board[(int)second.y / size_part][(int)second.x / size_part].position);
				board[(int)second.y / size_part][(int)second.x / size_part].is_move(board[(int)first.y / size_part][(int)first.x / size_part].position);
				update_flag = true;
		}
		else {
			array_user_coursor.clear();
		}
	}
	else {
		board[(int)array_user_coursor[0].y / size_part][(int)array_user_coursor[0].x / size_part].myQuads.setRotation(45.f);
	}
}

void Board::update(float elapsedTime, vector<Vector2f>& array_user_coursor) {
	if (array_user_coursor.size() >= 0) {
		board[(int)array_user_coursor[0].y / size_part][(int)array_user_coursor[0].x / size_part].myQuads.setRotation(0.f);
		int status_moving = 0;
		for (int i = 0; i < array_user_coursor.size(); i++) {
			if (board[(int)array_user_coursor[i].y / size_part][(int)array_user_coursor[i].x / size_part].get_moving()) {
				status_moving = 1;
				board[(int)array_user_coursor[i].y / size_part][(int)array_user_coursor[i].x / size_part].update(elapsedTime);
			}
		}
		if (status_moving == 0) {
			vector<Square> square_changed;
			for (int i = 0; i < array_user_coursor.size(); i++) {
				square_changed.push_back(board[(int)array_user_coursor[i].y / size_part][(int)array_user_coursor[i].x / size_part]);
			}
			for (int i = 0; i < square_changed.size(); i++) {
				// кубик должен сто€ть на новом месте
				board[(int)square_changed[i].position.y / size_part][(int)square_changed[i].position.x / size_part] = square_changed[i];
			}
			array_user_coursor.clear(); // 1 эл изъ€ли и проверим далее
			if (square_changed.size() > 1)
				array_user_coursor.push_back(square_changed[1].position);
			if (square_changed.size() > 0) {
				vector<Vector2f> x_changed;
				check_combination(Vector2f((int)square_changed[0].position.x / size_part, (int)square_changed[0].position.y / size_part), x_changed);
				if (x_changed.size() > 0) {
					delete_combinations(x_changed, array_user_coursor);
					choose_bonus(array_user_coursor, x_changed[rand() % x_changed.size()]);
				}
				for (int i = 1; i < square_changed.size(); i++) {
					int flag = 0;
					for (int j = 0; j < array_user_coursor.size(); j++) {
						if ((int)array_user_coursor[j].x / 60 == (int)square_changed[i].position.x / 60 &&
							(int)array_user_coursor[j].y / 60 == (int)square_changed[i].position.y / 60)
							flag = 1;
					}
					if (flag == 0)
						array_user_coursor.push_back(square_changed[i].position);
				}
				
			}
		}
	}
}

void Board::check_combination(Vector2f in_arr_pos_changed_1, vector<Vector2f>& x_changed) {
	vector<Vector2f> checked_elements;
	for_check_combination(checked_elements, in_arr_pos_changed_1);
	int x_was_changed = 0;
	if (checked_elements.size() > 2) { 
		int group_recolour = 0;
		for (int i = 0; i < checked_elements.size(); i++) {
			board[(int)checked_elements[i].y][(int)checked_elements[i].x].colour = 'w';
			for (int j = 0; j < x_changed.size(); j++) {
				if (x_changed[j].x == checked_elements[i].x) {// самый низкий элемент внес наибольший вклад в изменение доски
					x_changed[j] = checked_elements[i].y > x_changed[j].y ? checked_elements[i] : x_changed[j];
					x_was_changed = 1;
				}
			}
			if (x_was_changed == 0) {
				x_changed.push_back(checked_elements[i]);
			}
			x_was_changed = 0;
		}
	}
}

void Board::for_check_combination(vector<Vector2f>& checked_elements, Vector2f arr_position) {
	if (arr_position.x > 12 || arr_position.y > 12 || arr_position.x < 0 || arr_position.y < 0 ||
		board[(int)arr_position.y][(int)arr_position.x].colour == 'w') return;
	for (int i = 0; i < checked_elements.size(); i++) {
		if (arr_position.x == checked_elements[i].x && arr_position.y == checked_elements[i].y) return;
	}
	checked_elements.push_back(arr_position);
	if (arr_position.y + 1 <= 12 && board[(int)arr_position.y + 1][(int)arr_position.x].colour == board[(int)arr_position.y][(int)arr_position.x].colour) {
		for_check_combination(checked_elements, Vector2f(arr_position.x, arr_position.y + 1));
	}
	if (arr_position.y - 1 >= 0 && board[(int)arr_position.y - 1][(int)arr_position.x].colour == board[(int)arr_position.y][(int)arr_position.x].colour) {
		for_check_combination(checked_elements, Vector2f(arr_position.x, arr_position.y - 1));
	}
	if (arr_position.x + 1 <= 12 &&
		board[(int)arr_position.y][(int)arr_position.x + 1].colour == board[(int)arr_position.y][(int)arr_position.x].colour) {
		for_check_combination(checked_elements, Vector2f(arr_position.x + 1, arr_position.y));
	}
	if (arr_position.x - 1 >= 0 && board[(int)arr_position.y][(int)arr_position.x - 1].colour == board[(int)arr_position.y][(int)arr_position.x].colour) {
		for_check_combination(checked_elements, Vector2f(arr_position.x - 1, arr_position.y));
	}
}

void Board::delete_combinations(vector<Vector2f>& x_changed, vector<Vector2f>& array_user_coursor) {
	for (int i = 0; i < x_changed.size(); i++) {
		int count_white = 0;
		for (int j = x_changed[i].y; j >= 0; j--) {
			if (board[j][(int)x_changed[i].x].colour == 'w') {
				board[j][(int)x_changed[i].x].is_move(Vector2f(x_changed[i].x * 60 + 40,count_white * 60 + 40));
				array_user_coursor.push_back(Vector2f((int)x_changed[i].x * 60 + 40, j * 60 + 40));
				count_white += 1;
			}
			else {
				board[j][(int)x_changed[i].x].is_move(Vector2f(x_changed[i].x * 60 + 40, (j + count_white) * 60 + 40));
				array_user_coursor.push_back(Vector2f(board[j][(int)x_changed[i].x].position.x, board[j][(int)x_changed[i].x].position.y));
				
			}
		}
	}
}

void Board::choose_bonus(vector<Vector2f>& array_user_coursor, Vector2f arr_position) {
	int chance = rand() % 100;
	if (chance < 100) {
		bonus = new Bomb;
		bonus->process_bonus(array_user_coursor, board, arr_position);
		delete bonus;
	}
	if (chance < 0) {
		bonus = new Recolour;
		bonus->process_bonus(array_user_coursor, board, arr_position);
		delete bonus;
	}
}