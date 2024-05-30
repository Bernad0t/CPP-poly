#include "bonuses.h"

void Bomb::process_bonus(vector<Vector2f>& array_user_coursor, Square board[13][13], Vector2f arr_position) {
	int sign_vertical = rand() % 2;
	int sign_horizont = rand() % 2;
	int delta_vertical = rand() % 3 + 1;
	int delta_horizont = rand() % 3 + 1;
	vector<Vector2f> lowest_deleted_block;

	// бомба выпала в окрестности
	Vector2f position(arr_position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
		arr_position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? arr_position.x + pow(-1, sign_horizont) * delta_horizont : 12,
		arr_position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : arr_position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
		arr_position.y + pow(-1, sign_vertical) * delta_vertical : 12);
	// 4 рандомные клетки уничтожаются
	for (int i = 0; i < 5; i++) {
		sign_vertical = rand() % 2;
		sign_horizont = rand() % 2;
		delta_vertical = rand() % 3 + 1;
		delta_horizont = rand() % 3 + 1;
		Vector2f bomb(position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
			position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? position.x + pow(-1, sign_horizont) * delta_horizont : 12,
			position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
			position.y + pow(-1, sign_vertical) * delta_vertical : 12);
		int flag_block = 0;
		for (int j = 0; j < lowest_deleted_block.size(); j++) {
			if (bomb.x == lowest_deleted_block[j].x) {
				board[(int)bomb.y][(int)bomb.x].colour = 'w';
				flag_block = 1;
				lowest_deleted_block[j] = bomb.y > lowest_deleted_block[j].y ? bomb : lowest_deleted_block[j];
				bomb = lowest_deleted_block[j];
			}
		}
		if (flag_block == 0)
			lowest_deleted_block.push_back(bomb);
		int flag = 0;
		board[(int)bomb.y][(int)bomb.x].colour = 'w';
		int count_white = 0;
		for (int j = (int)board[(int)bomb.y][(int)bomb.x].position.y / 60; j >= 0; j--) {
			if (board[j][(int)bomb.x].colour == 'w') {
				board[j][(int)bomb.x].is_move(Vector2f(bomb.x * 60 + 40, count_white * 60 + 40 ));
				check_square_in_array(array_user_coursor, Vector2f(bomb.x * 60 + 40, j * 60 + 40));
				count_white += 1;
			}
			else {
				board[j][(int)bomb.x].is_move(Vector2f(bomb.x * 60 + 40, (j + count_white) * 60 + 40 > board[j][(int)bomb.x].get_move_to().y ?
					(j + count_white) * 60 + 40 : board[j][(int)bomb.x].get_move_to().y));
				check_square_in_array(array_user_coursor, Vector2f(board[j][(int)bomb.x].position.x, board[j][(int)bomb.x].position.y));
			}
		}
	}
}

void Bonus::check_square_in_array(vector<Vector2f>& array_user_coursor, Vector2f arr_position) {
	int flag = 0;
	for (int i = 0; i < array_user_coursor.size(); i++) {
		if ((int)array_user_coursor[i].x / 60 == (int)arr_position.x && (int)array_user_coursor[i].y / 60 == (int)arr_position.y) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		array_user_coursor.push_back(arr_position);
	}
}


void Recolour::process_bonus(vector<Vector2f>& array_user_coursor, Square board[13][13], Vector2f arr_position) {
	vector<Vector2f> new_recolour_elements;
	int sign_vertical = rand() % 2;
	int sign_horizont = rand() % 2;
	int delta_vertical = rand() % 3;
	int delta_horizont = rand() % 3;
	Vector2f position(arr_position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
		arr_position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? arr_position.x + pow(-1, sign_horizont) * delta_horizont : 12,
		arr_position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : arr_position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
		arr_position.y + pow(-1, sign_vertical) * delta_vertical : 12);
	if (board[(int)position.y][(int)position.x].colour != 'w') {
		vector<Vector2f> banned_position;
		banned_position.push_back(position);
		new_recolour_elements.push_back(position);
		for (int i = 0; i < 3; i++) {
			int flag_adding = 1;
			int sign_vertical = rand() % 2;
			int sign_horizont = rand() % 2;
			int delta_vertical = rand() % 2;
			int delta_horizont = rand() % 2;
			Vector2f new_position(position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
				position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? position.x + pow(-1, sign_horizont) * delta_horizont : 12,
				position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
				position.y + pow(-1, sign_vertical) * delta_vertical : 12);
			for (int i = 0; i < banned_position.size(); i++) {
				if (banned_position[i].x == new_position.x && banned_position[i].y == new_position.y) {
					flag_adding = 0;
					break;
				}
			}
			if (flag_adding == 1) {
				banned_position.push_back(new_position);
				if (board[(int)new_position.y][(int)new_position.x].colour != 'w') {
					new_recolour_elements.push_back(new_position);
					banned_position.push_back(Vector2f(new_position.x + 1 < 13 ? new_position.x + 1 : 12, new_position.y));
					banned_position.push_back(Vector2f(new_position.x - 1 > -1 ? new_position.x - 1 : 0, new_position.y));
					banned_position.push_back(Vector2f(new_position.x, new_position.y + 1 < 13 ? new_position.y + 1 : 12));
					banned_position.push_back(Vector2f(new_position.x, new_position.y - 1 > -1 ? new_position.y - 1 : 0));
				}
			}
		}
		for (int i = 0; i < new_recolour_elements.size(); i++) {
			board[(int)new_recolour_elements[i].y][(int)new_recolour_elements[i].x].colour = board[(int)position.y][(int)position.x].colour;
			board[(int)new_recolour_elements[i].y][(int)new_recolour_elements[i].x].myQuads.setFillColor(board[(int)position.y][(int)position.x].myQuads.getFillColor());
			array_user_coursor.push_back(Vector2f(new_recolour_elements[i].x * 60 + 40, new_recolour_elements[i].y * 60 + 40));
		}
	}

}