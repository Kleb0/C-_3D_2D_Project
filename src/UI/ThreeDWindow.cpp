
#include <glad/glad.h>
#include "UI/ThreeDWindow.hpp"
#include "WorldObjects/ThreeDObject.hpp"
#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/ImGuiGizmo.hpp"
#include <iostream>

ThreeDWindow::ThreeDWindow() {}

ThreeDWindow::ThreeDWindow(const std::string &title, const std::string &text)
    : title(title), text(text)
{
}

ThreeDWindow &ThreeDWindow::add(OpenGLContext &context)
{
    openGLContext = &context;
    return *this;
}

ThreeDWindow &ThreeDWindow::addObject(ThreeDObject &object)
{
    objects.push_back(&object);
    return *this;
}

ThreeDWindow &ThreeDWindow::add(ThreeDObject &object)
{
    return addObject(object);
}

void ThreeDWindow::render()
{
    ImGui::Begin(title.c_str());
    ImGui::Text("%s", text.c_str());

    if (openGLContext)
    {
        ImGui::Text("Contenu OpenGL attaché !");
        ImGui::BeginChild("OpenGLChildWindow", ImVec2(0, 0), true, ImGuiWindowFlags_None);

        oglChildPos = ImGui::GetWindowPos();
        oglChildSize = ImGui::GetContentRegionAvail();

        int newWidth = static_cast<int>(oglChildSize.x);
        int newHeight = static_cast<int>(oglChildSize.y);

        if (newWidth > 0 && newHeight > 0 &&
            (newWidth != openGLContext->getWidth() || newHeight != openGLContext->getHeight()))
        {
            openGLContext->resize(newWidth, newHeight);
        }

        openGLContext->render();

        ImTextureID textureID = (ImTextureID)(intptr_t)openGLContext->getTexture();

        if (ImGui::ImageButton("OpenGLTextureButton",
                               textureID,
                               oglChildSize,
                               ImVec2(0, 1), ImVec2(1, 0),
                               ImVec4(0, 0, 0, 0),
                               ImVec4(1, 1, 1, 1)))
        {
            handleClick();
        }

        updateGizmo();

        if (selector.getSelectedObject())
        {
            gizmo.render(view, proj);
        }

        ImGui::EndChild();
    }

    ImGui::End();
}

void ThreeDWindow::handleClick()
{
    double mouseX, mouseY;
    glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);

    std::cout << "Mouse Detected ! [DEBUG] Mouse position: " << mouseX << ", " << mouseY << std::endl;

    float relativeMouseX = mouseX - oglChildPos.x;

    float relativeMouseY = mouseY - oglChildPos.y;
    relativeMouseY = oglChildSize.y - relativeMouseY;

    for (auto *obj : objects)
    {
        std::cout << "OBJ POS: " << obj->getPosition().x << " " << obj->getPosition().y << " " << obj->getPosition().z << std::endl;
    }

    if (relativeMouseX >= 0 && relativeMouseX <= oglChildSize.x &&
        relativeMouseY >= 0 && relativeMouseY <= oglChildSize.y)
    {
        int windowWidth = openGLContext->getWidth();
        int windowHeight = openGLContext->getHeight();

        view = glm::lookAt(
            glm::vec3(5.0f, 10.0f, 10.0f),
            glm::vec3(2.5f, 0.0f, 2.5f),
            glm::vec3(0.0f, 1.0f, 0.0f));

        proj = glm::perspective(glm::radians(45.0f),
                                (float)windowWidth / (float)windowHeight,
                                0.1f, 100.0f);

        selector.update((int)relativeMouseX, (int)relativeMouseY, windowWidth, windowHeight, view, proj, objects);

        if (selector.getSelectedObject())
        {
            std::cout << "[DEBUG] Object selected !" << std::endl;
            gizmo.setTarget(selector.getSelectedObject());
            gizmo.render(view, proj);
        }
    }
}

void ThreeDWindow::updateGizmo()
{
    ImGuiGizmo::drawGizmo(selector.getSelectedObject());
    if (selector.getSelectedObject())
    {
        ImGui::Text("Objet sélectionné à la position : %.2f, %.2f, %.2f",
                    selector.getSelectedObject()->getPosition().x,
                    selector.getSelectedObject()->getPosition().y,
                    selector.getSelectedObject()->getPosition().z);
    }
}
