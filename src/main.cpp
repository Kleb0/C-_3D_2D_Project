#define SDL_MAIN_HANDLED
#include "UI/GameWindow.hpp"

int main()
{
    GameWindow window(1280, 720, "Game Window !!!");
    window.run();
    return 0;
}
