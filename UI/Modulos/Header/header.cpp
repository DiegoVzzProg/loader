#include "header.h"

void header_ui::render() {
    auto draw = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetWindowPos();
    auto size = ImGui::GetWindowSize();

    draw->AddRectFilled(
        pos
        , ImVec2(pos.x + size.x, pos.y + 51)
        , ImColor(24, 24, 24)
        , 0.0f
        , ImDrawFlags_RoundCornersTop
    );

    draw->AddText(ui::semibold, 17.0f, ImVec2(pos.x + 25, pos.y + 18), ImColor(235, 245, 251), "xanax client");
    draw->AddText(ui::semibold, 12.0f, ImVec2(pos.x + 109, pos.y + 22), ImColor(235, 245, 251, 150), "v0.0.3");

    ImGui::SameLine(405);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);

    ui::close = ImGui::Button("X", ImVec2(20,20));
}