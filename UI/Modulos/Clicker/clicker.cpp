#include "clicker.h"

void clicker_ui::render() {
    ImGui::SetCursorPos({ 24, 70 });
    ImGui::BeginChild(("##Clicker"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar);
    {
        {
            ImGui::TextColored(ImColor(1.0f, 1.0f, 1.0f, 0.6f), "clicker");
            ImGui::SameLine(173);
            ImGui::Checkbox(" ", &cg_clicker::enabled);
        }
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            ImGui::SliderFloat("cps:", &cg_clicker::cps, 1, 24, "%.1f", ImGuiSliderFlags_NoInput);
        }
    }
    ImGui::EndChild();
}