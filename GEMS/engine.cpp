#include "engine.h"

Engine::Engine():board(800) {
    // �������� ���������� ������, ������� ���� SFML � View
    Vector2f resolution;
    resolution.x = 1200;
    resolution.y = 800;
    update_flag = false;
    m_Window.create(VideoMode(resolution.x, resolution.y), "GEMS");

}

void Engine::start()
{
    // ������ �������
    Clock clock;

    while (m_Window.isOpen())
    {
        // ������������� ������ � ���������� ���������� ����� � dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}