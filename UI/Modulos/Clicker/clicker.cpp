#include "clicker.h"

void clicker_ui::render() {
    ImGui::SetCursorPos({ 24, 70 });
    ImGui::BeginChild(("##Clicker"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar);
    {
        {
            auto draw = ImGui::GetWindowDrawList();
            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();
            draw->AddRectFilled(
                pos
                , ImVec2(pos.x + size.x - 6, pos.y + 24)
                , ImColor(35, 36, 38)
                , 2.0f
                , ImDrawFlags_RoundCornersTop
            );

            draw->AddText(ui::semibold, 15.0f, ImVec2(pos.x + 4, pos.y + 4), ImColor(235, 245, 251), "Clicker");
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 25);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "Enabled");
            ImGui::SameLine(167);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);
            ImGui::Checkbox("##enabled", &cg_clicker::enabled);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
            ImGui::SliderFloat("cps:", &cg_clicker::cps, 1, 24, "%.1f", ImGuiSliderFlags_NoInput);
        }
    }
    ImGui::EndChild();
}

void clicker_ui::render_conditions() {
    ImGui::SetCursorPos({ 230, 70 });
    ImGui::BeginChild(("##Clicker_Options"), ImVec2(190, 275), false, ImGuiWindowFlags_NoScrollbar);
    {
        {
            auto draw = ImGui::GetWindowDrawList();
            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();
            draw->AddRectFilled(
                pos
                , ImVec2(pos.x + size.x - 6, pos.y + 24)
                , ImColor(35, 36, 38)
                , 2.0f
                , ImDrawFlags_RoundCornersTop
            );

            draw->AddText(ui::semibold, 15.0f, ImVec2(pos.x + 4, pos.y + 4), ImColor(235, 245, 251), "Conditions");
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 25);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
        {
            ImGui::TextColored(ImColor(235, 245, 251, 200), "block hit");
            ImGui::SameLine(167);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            ImGui::Checkbox("##block_hit", &cg_clicker::block_hit);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7);
            ImGui::TextColored(ImColor(235, 245, 251, 200), "auto block hit");
            ImGui::SameLine(167);
            ImGui::Checkbox("##auto_block_hit", &cg_clicker::auto_block_hit);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7);
            ImGui::TextColored(ImColor(235, 245, 251, 200), "only one hit");
            ImGui::SameLine(167);
            ImGui::Checkbox("##only_one_hit", &cg_clicker::only_one_hit);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7);
            ImGui::TextColored(ImColor(235, 245, 251, 200), "auto");
            ImGui::SameLine(167);
            ImGui::Checkbox("##auto_click", &cg_clicker::auto_click);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7);
            ImGui::TextColored(ImColor(235, 245, 251, 200), "break blocks");
            ImGui::SameLine(167);
            ImGui::Checkbox("##break_blocks", &cg_clicker::break_blocks);
        }
        {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 7);
            ImGui::TextColored(ImColor(235, 245, 251, 200), "shift disabled click");
            ImGui::SameLine(167);
            ImGui::Checkbox("##shift_disabled_click", &cg_clicker::shift_disabled_click);
        }
    }
    ImGui::EndChild();
}