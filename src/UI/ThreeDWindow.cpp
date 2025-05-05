
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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, selected->getPosition());

    static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;

    if (ImGui::IsKeyPressed(ImGuiKey_W))
        currentGizmoOperation = ImGuizmo::TRANSLATE;

    bool isManipulating = ImGuizmo::Manipulate(
        glm::value_ptr(view),
        glm::value_ptr(proj),
        currentGizmoOperation,
        ImGuizmo::WORLD,
        glm::value_ptr(model));

    if (ImGuizmo::IsUsing())
    {
        std::cout << "[DEBUG] Manipulation in progress!" << std::endl;

        glm::vec3 translation, rotation, scale;
        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(model),
                                              glm::value_ptr(translation),
                                              glm::value_ptr(rotation),
                                              glm::value_ptr(scale));

        selected->setPosition(translation);

        std::cout << "[DEBUG] New position: " << translation.x << ", " << translation.y << ", " << translation.z << std::endl;

        wasUsingGizmoLastFrame = ImGuizmo::IsUsing();
    }
}

void ThreeDWindow::render()
{

    bool isGizmoActive = ImGuizmo::IsUsing() || wasUsingGizmoLastFrame;
    ImGuiWindowFlags flags = isGizmoActive ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None;
    ImGui::Begin(title.c_str(), nullptr, flags);

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

        ImGui::Image(textureID, oglChildSize, ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            handleClick();
        }

        updateGizmo();

        ImGui::EndChild();
    }

    ImGui::End();
}