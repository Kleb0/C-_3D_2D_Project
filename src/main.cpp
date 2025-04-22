#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <QApplication>
#include "UI/FirstWindow.h"

int main(int argc, char *argv[])
{
    SDL_SetMainReady();
    QApplication app(argc, argv);

    FirstWindow window;
    window.setWindowTitle("test - Qt + OpenGL +SDL2");

    window.show();

    return app.exec();
}
