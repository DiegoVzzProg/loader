#include "clicker.h"

void clicker_ui::render() {
    ImGui::SetCursorPos({ 24, 70 });
    ImGui::BeginChild(("##Clicker"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar);
    {
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "clicker");
            ImGui::SameLine(167);
            ImGui::Checkbox("##enabled", &cg_clicker::enabled);
        }
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            ImGui::SliderFloat("cps:", &cg_clicker::cps, 1, 24, "%.1f", ImGuiSliderFlags_NoInput);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "block hit");
            ImGui::SameLine(167);
            ImGui::Checkbox("##block_hit", &cg_clicker::block_hit);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "auto block hit");
            ImGui::SameLine(167);
            ImGui::Checkbox("##auto_block_hit", &cg_clicker::auto_block_hit);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "only one hit");
            ImGui::SameLine(167);
            ImGui::Checkbox("##only_one_hit", &cg_clicker::only_one_hit);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "auto");
            ImGui::SameLine(167);
            ImGui::Checkbox("##auto_click", &cg_clicker::auto_click);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "break blocks");
            ImGui::SameLine(167);
            ImGui::Checkbox("##break_blocks", &cg_clicker::break_blocks);
        }
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "shift disabled click");
            ImGui::SameLine(167);
            ImGui::Checkbox("##shift_disabled_click", &cg_clicker::shift_disabled_click);
        }
    }
    ImGui::EndChild();
}