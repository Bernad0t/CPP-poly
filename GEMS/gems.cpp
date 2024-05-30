//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//#include "windows.h"
//#include <sstream>
//
//using namespace sf;
//using namespace std;
//
//void drow_text(RenderWindow& window, int point);
//
//class Point {
//public:
//	int x;
//	int y;
//
//	Point() {
//
//	}
//
//	Point(int x, int y) {
//		this->x = x;
//		this->y = y;
//	}
//};
//
//class Colour {
//	char colours[6] = { 'b', 'r', 'g', 'y', 'p', 'w' };
//public:
//	char get_colour(int position) {
//		return colours[position];
//	}
//};
//
//class Square {
//
//	int size;
//public:
//	Point position;
//	char colour;
//	RectangleShape myQuads;
//
//	Square() {
//
//	}
//
//	Square(int x, int y, int size, char colour) : position(x, y), myQuads(Vector2f(size, size)) {//(x, y) - центр квадратика
//		this->size = size;
//		this->colour = colour;
//	}
//
//	void drow(RenderWindow& window) {
//		myQuads.setOrigin(Vector2f(size / 2, size / 2));
//		myQuads.setPosition(Vector2f(position.x, position.y));
//		switch (colour) {
//		case 'b':
//			myQuads.setFillColor(Color{ 0, 0, 255, 255 });
//			break;
//		case 'r':
//			myQuads.setFillColor(Color::Red);
//			break;
//		case 'g':
//			myQuads.setFillColor(Color{ 0, 255, 0, 127 });
//			break;
//		case 'y':
//			myQuads.setFillColor(Color::Yellow);
//			break;
//		case 'p':
//			myQuads.setFillColor(Color::Magenta);
//			break;
//
//		case 'w':
//			//myQuads.setFillColor(Color{ 255, 255, 255, 255 });
//			return;
//			break;
//		}
//		window.draw(myQuads);
//	}
//};
//
//class Board {
//	void for_check_combination(vector<Point>& checked_elements, Point arr_position, int& size_bomb_destroed,
//		vector<Point>& recolour_elements);
//	void delete_combinations(vector<Point>& x_changed);
//	void process_combination_deleted(vector<Point>& x_changed);
//	void bonus_bomb(vector<Point>& checked_elements, Point arr_position, int& size_bomb_destroed);
//	void bonus_recolour(vector<Point>& recolour_elements, Point arr_position);
//	void drow_text(RenderWindow& window, int points);
//	int size_screen;
//	Square board[13][13]; // 13 на 13 поле
//	char generate_random_colour(int row, int column);
//	RenderWindow* window;
//	float speed = 4;
//	int score;
//public:
//	Board(int size_screen, RenderWindow* window) {
//		this->size_screen = size_screen;
//		this->window = window;
//		this->score = 0;
//		for (int row = 0; row < 13; row++) {
//			for (int column = 0; column < 13; column++) {
//				char colour = generate_random_colour(row, column);
//				Square square((size_screen / 40) * (column + 2) + size_screen / 20 * column,
//					(size_screen / 40) * (row + 2) + size_screen / 20 * row, size_screen / 20, colour);
//				board[row][column] = square;
//			}
//		}
//	}
//
//	void process_mouse(vector<Point>& array_user_coursor);
//
//	void check_combination(Point in_arr_pos_changed_1, vector<Point>& x_changed);
//
//	void print_board() {
//		window->clear(Color::Black);
//		for (int row = 0; row < 13; row++) {
//			for (int column = 0; column < 13; column++) {
//				board[row][column].drow(*window);
//			}
//		}
//		drow_text(*window, score);
//		window->display();
//	}
//
//	void move(Point first, Point second) {
//		double count_pos_changed = 0;
//		while (count_pos_changed != 16) {
//			board[first.y / 60][first.x / 60].position = Point(first.x + speed * count_pos_changed * (second.x - first.x) / 60,
//				first.y + speed * count_pos_changed * (second.y - first.y) / 60);
//			board[second.y / 60][second.x / 60].position = Point(second.x + speed * count_pos_changed * (first.x - second.x) / 60,
//				second.y + speed * count_pos_changed * (first.y - second.y) / 60);
//			print_board();
//			count_pos_changed++;
//		}
//		Square tmp_square = board[first.y / 60][first.x / 60];
//		board[first.y / 60][first.x / 60] = board[second.y / 60][second.x / 60];
//		board[second.y / 60][second.x / 60] = tmp_square;
//	}
//};
//
//void Board::process_combination_deleted(vector<Point>& x_changed) {
//	int coursor = 0;
//	vector <vector<Point>> arr_x_change;
//	arr_x_change.push_back(x_changed);
//	while (coursor < arr_x_change.size()) {
//		delete_combinations(arr_x_change[coursor]);
//		print_board();
//		for (int i = 0; i < arr_x_change[coursor].size(); i++) {
//			for (int j = arr_x_change[coursor][i].y; j >= 0; j--) {
//				vector<Point> new_x_change;
//				check_combination(Point(arr_x_change[coursor][i].x, j), new_x_change);
//				arr_x_change.push_back(new_x_change);
//			}
//		}
//		coursor++;
//	}
//}
//
//void Board::process_mouse(vector<Point>& array_user_coursor) {
//	if (array_user_coursor.size() == 2) {
//		Point first = array_user_coursor[0];
//		Point second = array_user_coursor[1];
//		board[first.y / 60][first.x / 60].myQuads.setRotation(0.f);
//		if (pow(first.x / 60 - second.x / 60, 2) + pow(first.y / 60 - second.y / 60, 2) == 1 &&
//			board[first.y / 60][first.x / 60].colour != 'w' && board[second.y / 60][second.x / 60].colour != 'w') {
//			move(board[first.y / 60][first.x / 60].position, board[second.y / 60][second.x / 60].position);
//			vector<Point> x_changed;
//			check_combination(Point(first.x / 60, first.y / 60), x_changed);
//			if (board[first.y / 60][first.x / 60].colour != board[second.y / 60][second.x / 60].colour)
//				// если один и тот же цвет, то уже удалилось/не изменилось
//				check_combination(Point(second.x / 60, second.y / 60), x_changed);
//			if (x_changed.size() > 0) {//если 0, то ничего не удалилось
//				process_combination_deleted(x_changed);
//			}
//		}
//		array_user_coursor.clear();
//	}
//	else {
//		board[array_user_coursor[0].y / 60][array_user_coursor[0].x / 60].myQuads.setRotation(45.f);
//	}
//}
//
//char Board::generate_random_colour(int row, int column) {
//	int position_colour = rand() % 5;
//	vector<char> banned_colours_for_this;
//	Colour colours;
//	if (row > 1 && board[row - 2][column].colour == board[row - 1][column].colour ||
//		row > 0 && column > 0 && board[row - 1][column - 1].colour == board[row - 1][column].colour ||
//		row > 0 && column > 0 && column < 12 && board[row - 1][column + 1].colour == board[row - 1][column].colour ||
//		row > 0 && column < 12 && board[row - 1][column + 1].colour == board[row - 1][column].colour) {
//		banned_colours_for_this.push_back(board[row - 1][column].colour);
//	}
//	if (column > 1 && board[row][column - 2].colour == board[row][column - 1].colour ||
//		column > 0 && row > 0 && (board[row - 1][column - 1].colour == board[row][column - 1].colour ||
//			board[row - 1][column].colour == board[row][column - 1].colour)) {
//		int flag_identity = 0;
//		for (int i = 0; i < banned_colours_for_this.size(); i++) {
//			if (banned_colours_for_this[i] == board[row][column - 1].colour) {
//				flag_identity = 1;
//				break;
//			}
//		}
//		if (flag_identity == 0) banned_colours_for_this.push_back(board[row][column - 1].colour);
//	}
//	while (banned_colours_for_this.size() > 0) {
//		char colour = colours.get_colour(position_colour);
//		for (int i = 0; i < banned_colours_for_this.size(); i++) {
//			if (colour == banned_colours_for_this[i]) break;
//			if (i == banned_colours_for_this.size() - 1) return colour;
//		}
//		position_colour = rand() % 5;
//	}
//	return colours.get_colour(position_colour);
//}
//
//void Board::for_check_combination(vector<Point>& checked_elements, Point arr_position, int& size_bomb_destroed,
//	vector<Point>& recolour_elements) {
//	if (arr_position.x > 12 || arr_position.y > 12 || arr_position.x < 0 || arr_position.y < 0 ||
//		board[arr_position.y][arr_position.x].colour == 'w') return;
//	for (int i = 0; i < checked_elements.size(); i++) {
//		if (arr_position.x == checked_elements[i].x && arr_position.y == checked_elements[i].y) return;
//	}
//	checked_elements.push_back(arr_position);
//	int chance_bomb = rand() % 100;
//	if (chance_bomb < 1)
//		bonus_bomb(checked_elements, arr_position, size_bomb_destroed);
//	int chance_recolour = rand() % 100;
//	if (chance_recolour < 3)
//		bonus_recolour(recolour_elements, arr_position);
//	if (arr_position.y + 1 <= 12 && board[arr_position.y + 1][arr_position.x].colour == board[arr_position.y][arr_position.x].colour) {
//		for_check_combination(checked_elements, Point(arr_position.x, arr_position.y + 1), size_bomb_destroed, recolour_elements);
//	}
//	if (arr_position.y - 1 >= 0 && board[arr_position.y - 1][arr_position.x].colour == board[arr_position.y][arr_position.x].colour) {
//		for_check_combination(checked_elements, Point(arr_position.x, arr_position.y - 1), size_bomb_destroed, recolour_elements);
//	}
//	if (arr_position.x + 1 <= 12 &&
//		board[arr_position.y][arr_position.x + 1].colour == board[arr_position.y][arr_position.x].colour) {
//		for_check_combination(checked_elements, Point(arr_position.x + 1, arr_position.y), size_bomb_destroed, recolour_elements);
//	}
//	if (arr_position.x - 1 >= 0 && board[arr_position.y][arr_position.x - 1].colour == board[arr_position.y][arr_position.x].colour) {
//		for_check_combination(checked_elements, Point(arr_position.x - 1, arr_position.y), size_bomb_destroed, recolour_elements);
//	}
//}
//
//void Board::delete_combinations(vector<Point>& x_changed) {
//	for (int i = 0; i < x_changed.size(); i++) {
//		int count_white = 0;
//		for (int j = x_changed[i].y; j >= 0; j--) {
//			if (board[j][x_changed[i].x].colour == 'w') {
//				count_white += 1;
//			}
//			else {
//				move(Point(x_changed[i].x * 60 + 40, (j + count_white) * 60 + 40), Point(x_changed[i].x * 60 + 40, j * 60 + 40));
//			}
//		}
//	}
//}
//
//void Board::check_combination(Point in_arr_pos_changed_1, vector<Point>& x_changed) {
//	vector<Point> checked_elements;
//	int size_bomb_destroed = 0;
//	vector<Point> recolour_elements;
//	for_check_combination(checked_elements, in_arr_pos_changed_1, size_bomb_destroed, recolour_elements);
//	int x_was_changed = 0;
//	if (checked_elements.size() - size_bomb_destroed > 2) { // -size_bomb_destroed, т к от бомбы уничтожится лишь при условии, что были уничтожены гемы
//		int group_recolour = 0;
//		score += checked_elements.size() * 10 + size_bomb_destroed * 10;
//		for (int recolour = 1; recolour < recolour_elements.size(); recolour++) {
//			if (recolour % 3 == 0)
//				group_recolour++;
//			board[recolour_elements[recolour].y][recolour_elements[recolour].x].colour =
//				board[recolour_elements[3 * group_recolour].y][recolour_elements[3 * group_recolour].x].colour;
//		}
//		for (int i = 0; i < checked_elements.size(); i++) {
//			board[checked_elements[i].y][checked_elements[i].x].colour = 'w';
//			for (int j = 0; j < x_changed.size(); j++) {
//				if (x_changed[j].x == checked_elements[i].x) {// самый низкий элемент внес наибольший вклад в изменение доски
//					x_changed[j] = checked_elements[i].y > x_changed[j].y ? checked_elements[i] : x_changed[j];
//					x_was_changed = 1;
//				}
//			}
//			if (x_was_changed == 0) {
//				x_changed.push_back(checked_elements[i]);
//			}
//			x_was_changed = 0;
//		}
//	}
//}
//
//void Board::drow_text(RenderWindow& window, int points) {
//	ostringstream ss;
//	ss << points;
//	Text text;
//	Text points_text;
//	Font font;
//	if (font.loadFromFile("./arialmt.ttf")) {
//		// select the font
//		text.setFont(font); // font is a sf::Font
//		points_text.setFont(font);
//
//		// set the string to display
//		text.setString("SCORE");
//		points_text.setString(ss.str().c_str());
//
//		// set the character size
//		text.setCharacterSize(48 * 2); // in pixels, not points!
//		points_text.setCharacterSize(48);
//
//		text.setPosition(850, 50);
//		points_text.setPosition(1000, 200);
//
//		// set the color
//		text.setFillColor(sf::Color::White);
//		points_text.setFillColor(sf::Color::White);
//
//		// set the text style
//		text.setStyle(Text::Bold);
//		points_text.setStyle(Text::Bold);
//
//		window.draw(text);
//		window.draw(points_text);
//	}
//}
//
//void Board::bonus_bomb(vector<Point>& checked_elements, Point arr_position, int& size_bomb_destroed) {
//	int sign_vertical = rand() % 2;
//	int sign_horizont = rand() % 2;
//	int delta_vertical = rand() % 3 + 1;
//	int delta_horizont = rand() % 3 + 1;
//	// бомба выпала в окрестности
//	Point position(arr_position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
//		arr_position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? arr_position.x + pow(-1, sign_horizont) * delta_horizont : 12,
//		arr_position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : arr_position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
//		arr_position.y + pow(-1, sign_vertical) * delta_vertical : 12);
//	if (board[position.y][position.x].colour != 'w') {
//		checked_elements.push_back(position);
//		size_bomb_destroed++;
//	}
//	// 4 рандомные клетки уничтожаются
//	for (int i = 0; i < 4; i++) {
//		Point bomb(rand() % 13, rand() % 13);
//		if (board[bomb.y][bomb.x].colour == 'w')
//			continue;
//		checked_elements.push_back(Point(rand() % 13, rand() % 13));
//		size_bomb_destroed++;
//	}
//}
//
//void Board::bonus_recolour(vector<Point>& recolour_elements, Point arr_position) {
//	vector<Point> new_recolour_elements;
//	int sign_vertical = rand() % 2;
//	int sign_horizont = rand() % 2;
//	int delta_vertical = rand() % 3;
//	int delta_horizont = rand() % 3;
//	Point position(arr_position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
//		arr_position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? arr_position.x + pow(-1, sign_horizont) * delta_horizont : 12,
//		arr_position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : arr_position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
//		arr_position.y + pow(-1, sign_vertical) * delta_vertical : 12);
//	if (board[position.y][position.x].colour != 'w') {
//		vector<Point> banned_position;
//		banned_position.push_back(position);
//		new_recolour_elements.push_back(position);
//		while (new_recolour_elements.size() != 3) {
//			int flag_adding = 1;
//			int sign_vertical = rand() % 2;
//			int sign_horizont = rand() % 2;
//			int delta_vertical = rand() % 2;
//			int delta_horizont = rand() % 2;
//			Point new_position(position.x + pow(-1, sign_horizont) * delta_horizont < 0 ? 0 :
//				position.x + pow(-1, sign_horizont) * delta_horizont < 13 ? position.x + pow(-1, sign_horizont) * delta_horizont : 12,
//				position.y + pow(-1, sign_vertical) * delta_vertical < 0 ? 0 : position.y + pow(-1, sign_vertical) * delta_vertical < 13 ?
//				position.y + pow(-1, sign_vertical) * delta_vertical : 12);
//			for (int i = 0; i < banned_position.size(); i++) {
//				if (banned_position[i].x == new_position.x && banned_position[i].y == new_position.y) {
//					flag_adding = 0;
//					break;
//				}
//			}
//			if (flag_adding == 1) {
//				banned_position.push_back(new_position);
//				if (board[new_position.y][new_position.x].colour != 'w') {
//					new_recolour_elements.push_back(new_position);
//					banned_position.push_back(Point(new_position.x + 1 < 13 ? new_position.x + 1 : 12, new_position.y));
//					banned_position.push_back(Point(new_position.x - 1 > -1 ? new_position.x - 1 : 0, new_position.y));
//					banned_position.push_back(Point(new_position.x, new_position.y + 1 < 13 ? new_position.y + 1 : 12));
//					banned_position.push_back(Point(new_position.x, new_position.y - 1 > -1 ? new_position.y - 1 : 0));
//				}
//			}
//			/*if (banned_position.size() >= 9) {
//			new_recolour_elements.clear();
//			break;
//			}*/
//		}
//		for (int i = 0; i < new_recolour_elements.size(); i++) {
//			recolour_elements.push_back(new_recolour_elements[i]);
//		}
//	}
//
//}
//
////int main()
////{
////	RenderWindow window(VideoMode(1200, 800), "My window");
////	window.setKeyRepeatEnabled(false);
////	window.setVerticalSyncEnabled(true);
////	vector<Point> array_user_coursor;
////	Board board(800, &window);
////	while (window.isOpen()) {
////		Event event;
////		while (window.pollEvent(event))
////		{
////			if (event.type == Event::Closed)
////				window.close();
////			if (event.type == Event::MouseButtonPressed) {
////				if (event.mouseButton.button == Mouse::Left) {
////					Point point(event.mouseButton.x, event.mouseButton.y);
////					array_user_coursor.push_back(point);
////					board.process_mouse(array_user_coursor);
////					break;
////				}
////			}
////		}
////		board.print_board();
////	}
////	return 0;
////}