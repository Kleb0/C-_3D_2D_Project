#define SDL_MAIN_HANDLED
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "UI/MainSoftwareGUI.hpp"
#include "UI/InfoWindow.hpp"
#include "UI/ThreeDWindow.hpp"
#include "WorldObjects/ThreedObject.hpp"
#include "InternalLogic/AssemblerLogic.hpp"
#include "Engine/OpenGLContext.hpp"

int main()
{
    MainSoftwareGUI gui(1280, 720, "Main GUI");
    InfoWindow myInfoWindow;
    ThreeDWindow myThreeDWindow;
    OpenGLContext Renderer;
    ThreeDObject myCube;

    myInfoWindow.title = "Hello Window 1";
    myInfoWindow.text = "Bienvenue dans la première fenêtre ! C'est une belle fenêtre !";
    myThreeDWindow.title = "Hello Window 2";
    myThreeDWindow.text = "Bienvenue dans la deuxième fenêtre ! Celle-ci contient un contexte OpenGL !";

    add(gui, myInfoWindow);
    add(gui, myThreeDWindow);
    add(myThreeDWindow, Renderer);
    add(Renderer, myCube);

    gui.run();
}
