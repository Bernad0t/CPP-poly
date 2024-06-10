#include "engine.h"

Engine::Engine():board(800) {
    // Получаем разрешение экрана, создаем окно SFML и View
    Vector2f resolution;
    resolution.x = 1200;
    resolution.y = 800;
    update_flag = false;
    m_Window.create(VideoMode(resolution.x, resolution.y), "GEMS");

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