#pragma once

#include <GLFW/glfw3.h>
#include "UI/GUIWindow.hpp"
#include "Engine/OpenGLContext.hpp"
#include "Engine/ThreeDObjectSelector.hpp"
#include <imgui.h>
#include <string>
#include <vector>

class ThreeDObject;

class ThreeDWindow : public GUIWindow
{
public:
    ImVec2 oglChildPos;
    ImVec2 oglChildSize;
    std::string title = "Hello Window";
    std::string text = "Bienvenue dans la fenêtre 3D !";

    ThreeDWindow();
    ThreeDWindow(const std::string &title, const std::string &text);

    ThreeDWindow &add(OpenGLContext &context);
    ThreeDWindow &add(ThreeDObject &object);
    ThreeDWindow &addObject(ThreeDObject &object);

    GLFWwindow *glfwWindow = nullptr;

    void render() override;

private:
    OpenGLContext *openGLContext = nullptr;
    ThreeDObjectSelector selector;
    std::vector<ThreeDObject *> objects;

    void handleClick();
    void updateGizmo();
};
