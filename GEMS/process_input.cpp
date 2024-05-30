#include "engine.h"
#include "field.h"

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			m_Window.close();
		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left) {
				Vector2f point(event.mouseButton.x, event.mouseButton.y);
				array_user_coursor.push_back(point);
				board.process_mouse(array_user_coursor, update_flag);
				break;
			}
		}
	}
}