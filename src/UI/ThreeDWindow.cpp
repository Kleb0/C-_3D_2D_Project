
#include <glad/glad.h>
#include <imgui_internal.h>
#include <ImGuizmo.h>
#include "UI/ThreeDWindow.hpp"
#include "WorldObjects/ThreeDObject.hpp"
#include <SDL2/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

void ThreeDWindow::handleClick()
{
    double mouseX, mouseY;
    glfwGetCursorPos(glfwWindow, &mouseX, &mouseY);

    float relativeMouseX = mouseX - oglChildPos.x;
    float relativeMouseY = mouseY - oglChildPos.y;
    relativeMouseY = oglChildSize.y - relativeMouseY;

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

        bool preventSelection = Similigizmo.hasTarget() && ImGuizmo::IsOver();

        if (!preventSelection)
        {
            selector.update((int)relativeMouseX, (int)relativeMouseY, windowWidth, windowHeight, view, proj, objects);
        }
        else
        {
            std::cout << "[INFO] Gizmo is active and has a target, selection is disabled." << std::endl;
        }

        ThreeDObject *selected = selector.getSelectedObject();

        for (auto *obj : objects)
        {
            obj->setSelected(false);
        }
        if (selected)
        {
            selected->setSelected(true);
            Similigizmo.setTarget(selected);
        }
        else
        {
            Similigizmo.disable();
        }
    }
}

void ThreeDWindow::updateGizmo()
{
    ThreeDObject *selected = selector.getSelectedObject();

    if (!selected)
        return;

    ImGuizmo::BeginFrame();
    ImGuizmo::Enable(true);
    ImGuizmo::SetImGuiContext(ImGui::GetCurrentContext());
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(oglChildPos.x, oglChildPos.y, oglChildSize.x, oglChildSize.y);
    ImGuizmo::SetGizmoSizeClipSpace(0.2f);

    glm::mat4 model = selected->getModelMatrix();
    glm::vec3 posBefore = selected->getPosition();

    static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
    if (ImGui::IsKeyPressed(ImGuiKey_W))
        currentGizmoOperation = ImGuizmo::TRANSLATE;

    ImGuizmo::Manipulate(glm::value_ptr(view), glm::value_ptr(proj),
                         currentGizmoOperation, ImGuizmo::WORLD,
                         glm::value_ptr(model));

    if (ImGuizmo::IsUsing())
    {
        glm::vec3 translation;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model),
                                              glm::value_ptr(translation),
                                              nullptr, nullptr);

        selected->setPosition(translation);

        glm::vec3 delta = translation - posBefore;

        if (fabs(delta.x) > fabs(delta.y) && fabs(delta.x) > fabs(delta.z))
            std::cout << "[GIZMO] X axis clicked." << std::endl;
        else if (fabs(delta.y) > fabs(delta.x) && fabs(delta.y) > fabs(delta.z))
            std::cout << "[GIZMO] Y axis clicked." << std::endl;
        else if (fabs(delta.z) > fabs(delta.x) && fabs(delta.z) > fabs(delta.y))
            std::cout << "[GIZMO] Z axis clicked." << std::endl;
    }
}

void ThreeDWindow::render()
{
    ImGui::Begin(title.c_str());
    ImGui::Text("%s", text.c_str());

    if (openGLContext)
    {
        ImGui::Text("Contenu OpenGL attaché !");
        ImGui::BeginChild("OpenGLChildWindow", ImVec2(0, 0), true, ImGuiWindowFlags_None);

        oglChildPos = ImGui::GetCursorScreenPos();
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

        ImGui::EndChild();
    }

    ImGui::End();
}
