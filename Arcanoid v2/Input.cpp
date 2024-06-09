#include "engine.h"

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			m_Window.close();
		if (event.type == Event::KeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
				carriage.isMoveLeft = true;
			if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
				carriage.isMoveRight = true;
		}
		else {
			carriage.isMoveRight = false;
			carriage.isMoveLeft = false;
		}
	}
}