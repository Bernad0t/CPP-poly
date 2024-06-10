#pragma once
#include <SFML/Graphics.hpp>
#include "field.h";
#include <vector>

using namespace sf;
using namespace std;

class Engine{
private:

    RenderWindow m_Window;

    vector<Vector2f> array_user_coursor;
    Board board;

    bool update_flag;
    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Engine();

    // Функция старт вызовет все приватные функции
    void start();

};
