#include "engine.h"

void Engine::draw()
{
    // ������� ���������� ����
    m_Window.clear(Color::Black);

    board.print_board(m_Window);

    // ���������� ���, ��� ����������
    m_Window.display();
}