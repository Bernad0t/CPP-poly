#include "engine.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (update_flag) {
        board.update(dtAsSeconds, array_user_coursor);
        if (array_user_coursor.size() == 0)
            update_flag = false;
    }
}