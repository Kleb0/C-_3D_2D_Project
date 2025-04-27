#define SDL_MAIN_HANDLED
#include "UI/MainSoftwareGUI.hpp"
#include "UI/NewWindow.hpp"
#include "InternalLogic/AssemblerLogic.hpp"

int main()
{
    MainSoftwareGUI gui(1280, 720, "Main GUI");
    NewWindow myWindow;

    NewWindow myWindow2;

    myWindow.title = "Hello Window 1";
    myWindow.text = "Bienvenue dans la première fenêtre ! C'est une belle fenêtre !";
    myWindow2.title = "Hello Window 2";
    myWindow2.text = "Bienvenue dans la deuxième fenêtre !";

    add(gui, myWindow);

    gui.run();
}
