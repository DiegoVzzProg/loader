#include <ImGui/byte.h>
#include "ui.h"

#pragma region load
void ui::load() {
    HWND main_hwnd = nullptr;

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ABC", NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, L"ABC", WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

    if (!main_hwnd) {
        DWORD error = GetLastError();
        wchar_t buffer[256];
        swprintf(buffer, 256, L"CreateWindow failed with error %d", error);
        MessageBox(nullptr, buffer, L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF, // Cyrillic Extended-A
        0xA640, 0xA69F, // Cyrillic Extended-B
        0xE000, 0xE226, // icons
        0,
    };

    font_config.GlyphRanges = ranges;

    medium = io.Fonts->AddFontFromMemoryTTF(InterMedium, sizeof(InterMedium), 15.0f, &font_config, ranges);
    semibold = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 17.0f, &font_config, ranges);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (!ui::close)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            render();
            ImGui::PopStyleVar();
        }
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);
}
#pragma endregion

#pragma region Colors
void ui::colors() {
    const auto style = &ImGui::GetStyle();
    const auto colors = style->Colors;

    style->WindowBorderSize = 0.f;
    style->WindowRounding = 2.f;
    style->WindowTitleAlign = ImVec2(0.0, 0.0);
    style->FrameRounding = 2.f;
    style->GrabRounding = 2.f;
    style->ChildRounding = 2.f;
    style->ItemSpacing = ImVec2(5, 10);
    style->FramePadding = ImVec2(0, 0);
    style->PopupRounding = 3.f;

    colors[ImGuiCol_Border] = ImColor(51, 51, 51);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    #pragma region Titulo
    ImVec4 ColorTitle = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

    colors[ImGuiCol_TitleBg] = ColorTitle;
    colors[ImGuiCol_TitleBgActive] = ColorTitle;
    colors[ImGuiCol_TitleBgCollapsed] = ColorTitle;
    #pragma endregion

    colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.10f, 0.10f, 0.15f, 0.00f);

    colors[ImGuiCol_Button] = ImColor(24, 24, 24);
    colors[ImGuiCol_ButtonHovered] = ImColor(24, 24, 24);
    colors[ImGuiCol_ButtonActive] = ImColor(24, 24, 24);

    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

    colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.40f, 0.12f, 0.99f, 0.90f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);

    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.05f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);

    colors[ImGuiCol_WindowBg] = ImColor(28, 28, 28);
    colors[ImGuiCol_TitleBgActive] = ImColor(28, 28, 28);
    colors[ImGuiCol_FrameBg] = ImColor(45, 45, 45);
    colors[ImGuiCol_FrameBgHovered] = ImColor(45, 45, 45);
    colors[ImGuiCol_FrameBgActive] = ImColor(45, 45, 45);
    colors[ImGuiCol_ChildBg] = ImColor(28, 28, 28);

}
#pragma endregion

#pragma region render
void ui::render() {
    ui::colors();

    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(445, 570));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin("##main", NULL, ImGuiWindowFlags_NoDecoration);
    {
        #pragma region header
        {
            header_ui::render();
        }
        #pragma endregion

        #pragma region clicker
        {
            clicker_ui::render();
            clicker_ui::render_conditions();
        }
        #pragma endregion

    }
    ImGui::End();
}
#pragma endregion

