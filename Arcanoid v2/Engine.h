#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./Ball.h"
#include "./Carriage.h"
#include "./Square.h"
//#include "./Bonus.h"

using namespace sf;
using namespace std;

class Engine {
private:
    class Bonus {
    protected:
        int size;
        int speed;
        Engine* engine;
    public:
        CircleShape myBonus;
        Bonus(Vector2f position, Engine* engine);

        void ProcessCoallision();

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

    class changeDirectionBall : public Bonus {
    public:
        changeDirectionBall(Vector2f position, Engine* engine);

        void ProcessBonus() override;
        void DropBonus() override;
    };

    Vector2f resolution;
    RenderWindow m_Window;

    void GenerateBonus(bool& flag, int multiplyerPositionX, int multiplyerPositionY);

    int originalSizeCarriage;
    int originalSpeedBall;
    int spaceBetweenSquares;
    int originalSizeSquare;

    void ProcessBoardScreen(Ball& ball);
    void ProcessBallSquare(Ball& ball);
    //void ProcessBallCarriage(Ball& ball);

    void input();
    void update(float dtAsSeconds);
    void draw();

    Font font;

    vector<Bonus*> bonuses;
    vector<Ball> balls;
    vector<vector<Square*>> squares; // 20 на 6
    Carriage carriage;
    int defeats;
    int score;

    /*friend void upSpeedBall::ProcessBonus();
    friend void extandCarriage::ProcessBonus();
    friend void additionalBottom::ProcessBonus();*/
public:

    Engine();

    vector<Ball>* getArrBalls();
    Carriage* getCarriage();
    Vector2f getResolution();

    // Функция старт вызовет все приватные функции
    void start();

    ~Engine();

};
