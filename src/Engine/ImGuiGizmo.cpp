#include "Engine/ImGuiGizmo.hpp"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void ImGuiGizmo::drawGizmo(const ThreeDObject *selectedObject)
{
    if (selectedObject)
    {
        ImGui::Begin("Gizmo");
        ImGui::Text("Selected Object");
        glm::vec3 pos = selectedObject->getPosition();
        ImGui::Text("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
        ImGui::End();
    }
}
