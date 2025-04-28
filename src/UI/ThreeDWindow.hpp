#pragma once

#include "UI/GUIWindow.hpp"
#include "Engine/OpenGLContext.hpp"
#include "imgui.h"
#include <string>

class ThreeDWindow : public GUIWindow
{
public:
    std::string title = "Hello Window";
    std::string text = "Bienvenue dans la première fenêtre !";

    OpenGLContext *openGLContext = nullptr;
    ThreeDWindow() = default;

    ThreeDWindow(const std::string &title, const std::string &text)
        : title(title), text(text)
    {
    }

    ThreeDWindow &add(OpenGLContext &context)
    {
        openGLContext = &context;
        return *this;
    }

    void render() override
    {
        ImGui::Begin(title.c_str());
        ImGui::Text("%s", text.c_str());

        if (openGLContext)
        {
            ImGui::Text("Contenu OpenGL attaché !");

            ImGui::BeginChild("OpenGLChildWindow", ImVec2(0, 0), true, ImGuiWindowFlags_None);
            ImVec2 availableSize = ImGui::GetContentRegionAvail();

            int newWidth = static_cast<int>(availableSize.x);
            int newHeight = static_cast<int>(availableSize.y);

            if (newWidth > 0 && newHeight > 0 &&
                (newWidth != openGLContext->getWidth() || newHeight != openGLContext->getHeight()))
            {
                openGLContext->resize(newWidth, newHeight);
            }

            openGLContext->render();

            ImGui::Image((ImTextureID)(intptr_t)openGLContext->getTexture(),
                         availableSize,
                         ImVec2(0, 1), ImVec2(1, 0),
                         ImVec4(1, 1, 1, 1),
                         ImVec4(0, 0, 0, 0));

            ImGui::EndChild();
        }
        else
        {
            ImGui::Text("Contenu OpenGL non attaché !");
        }

        ImGui::End();
    }
};
