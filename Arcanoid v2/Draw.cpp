#include "./Engine.h"
#include <sstream>

void Engine::draw() {
    // Стираем предыдущий кадр
    m_Window.clear(Color::Black);

    for (auto& ball : balls) {
        if (ball.status != false)
            m_Window.draw(ball.myBall);
    }
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < squares[i].size(); j++) {
            if (squares[i][j]->StatusLive != false)
                m_Window.draw(squares[i][j]->myQuads);
        }
    }
    for (auto& bonus : bonuses) {
        if (bonus->moving != false)
            m_Window.draw(bonus->myBonus);
    }
    m_Window.draw(carriage.myCarriage);

    ostringstream ss;
    ss << "Score: " << score << endl;
    ss << "Defeats: " << defeats;
    //set up text properties
    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(Text::Bold);
    text.setFillColor(Color::White);
    text.setPosition(30, resolution.y - 50);

    text.setString(ss.str());
    m_Window.draw(text);

    // Отображаем все, что нарисовали
    m_Window.display();
}