#include "engine.h"

void Engine::draw()
{
    // Стираем предыдущий кадр
    m_Window.clear(Color::Black);

    board.print_board(m_Window);

    // Отображаем все, что нарисовали
    m_Window.display();
}