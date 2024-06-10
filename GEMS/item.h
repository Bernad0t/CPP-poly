#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Square{
private:
    // Логические переменные для отслеживания направления движения
    bool moving;
    int size;
    float speed;
    vector<int> order_move;
    Vector2f move_to;
public:
    Vector2f position;
    char colour;
    RectangleShape myQuads;
    Square();
    Square(int x, int y, int size, char colour);
    void is_move(Vector2f to_position);
    void stop_move();
    // Эта функция будет вызываться на каждый кадр
    void update(float elapsedTime);
    bool get_moving();
    Vector2f get_move_to();
};
