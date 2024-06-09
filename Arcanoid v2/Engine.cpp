#include "engine.h"

Engine::Engine() : carriage(Vector2f(400, 790), 60, 640) {
    int width = 1000;
    int heigth = 800;
    resolution = Vector2f(width, heigth);
    originalSizeCarriage = 60;
    originalSpeedBall = 240;
    originalSizeSquare = 30;
    spaceBetweenSquares = 20;
    score = 0;
    defeats = 0;
    m_Window.create(VideoMode(width, heigth), "Arcanoid");
    balls.push_back(Ball(10, Vector2f(395, 780), originalSpeedBall));
    for (int i = 0; i < 6; i++) {
        vector<Square*> newSquares;
        for (int j = 0; j < 20; j++) {
            int chance = rand() % 100;
            if (chance < 5) {
                Square* square = new UnIndestructibleSquare(originalSizeSquare, Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * j,
                    spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * i), false);
                newSquares.push_back(square);
            }
            else if (chance < 20) {
                bool flag = false;
                GenerateBonus(flag, j, i);
                Square* square = new upSpeedSquare(originalSizeSquare, Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * j,
                    spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * i), false);
                newSquares.push_back(square);
            }
            else {
                bool flag = false;
                GenerateBonus(flag, j, i);
                Square* square = new DefaultSquare(originalSizeSquare, Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * j,
                    spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * i), flag);
                newSquares.push_back(square);
            }
        }
        squares.push_back(newSquares);
        font.loadFromFile("./arialmt.ttf");
    }
}

void Engine::GenerateBonus(bool& flag, int multiplyerPositionX, int multiplyerPositionY) {
    int chance = rand() % 100;
    if (chance < 5) {
        Bonus* bonus = new changeDirectionBall(Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionX,
            spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionY), this);
        bonuses.push_back(bonus);
        flag = true;
    }
    else if (chance < 10) {
        Bonus* bonus = new additionalBottom(Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionX,
            spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionY), this);
        bonuses.push_back(bonus);
        flag = true;
    }
    else if (chance < 20) {
        Bonus* bonus = new upSpeedBall(Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionX,
            spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionY), this);
        bonuses.push_back(bonus);
        flag = true;
    }
    else if (chance < 25) {
        Bonus* bonus = new extandCarriage(Vector2f(spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionX,
            spaceBetweenSquares / 2 + originalSizeSquare / 2 + (originalSizeSquare + spaceBetweenSquares) * multiplyerPositionY), this);
        bonuses.push_back(bonus);
        flag = true;
    }
}

vector<Ball>* Engine::getArrBalls() {
    return &balls;
}

Carriage* Engine::getCarriage() {
    return &carriage;
}

Vector2f Engine::getResolution() {
    return resolution;
}

Engine::~Engine() {
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < squares[i].size(); j++) {
            delete squares[i][j];
        }
    }
}

void Engine::start()
{
    // Расчет времени
    Clock clock;

    while (m_Window.isOpen())
    {
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}