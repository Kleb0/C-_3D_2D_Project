#define SDL_MAIN_HANDLED
#include <QApplication>
#include "UI/GameWindow.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{

    SDL_SetMainReady();
    IMG_Init(IMG_INIT_PNG);
    QApplication app(argc, argv);
    GameWindow window;
    window.show();
    return app.exec();
    IMG_Quit();
}
