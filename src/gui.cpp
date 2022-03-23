#include "gui.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

Gui& Gui::Get()
{
    static Gui instance;
    return instance;
}

void Gui::Init(Window* window, uint32_t maxParticleCount)
{
    Get().m_MaxParticleCount = maxParticleCount;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking

    ImGui::StyleColorsDark();
    LoadStyle();

    io.Fonts->AddFontFromFileTTF("res/Ubuntu-Regular.ttf", 16.0f);

    window->InitGui();
}

void Gui::Terminate()
{
    ImGui::DestroyContext();
}

void Gui::Update(Framebuffer* simulationBuffer,
                 uint32_t analysisTexture,
                 Simulator::Properties* simProps,
                 Analyser::Properties* analysisProps)
{
    NewFrame();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;  // | ImGuiWindowFlags_MenuBar;

    ImGui::SetNextWindowPos({ 0.0f, 0.0f }, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });

    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    bool isOpen = true;
    ImGui::Begin("Root Window", &isOpen, windowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("Dockspace");
    ImGui::DockSpace(dockSpaceId, { 0.0f, 0.0f });

    ShowSimulationProps(&simProps->ParticleCount, &simProps->ParticleSize);
    ShowAnalysisProps(analysisProps);
    ShowSimulationStats();
    ShowSimulation(simulationBuffer);
    ShowAnalysis(analysisTexture);
    ShowAnalysisOutput(analysisProps, analysisTexture);

    ImGui::End();

    ImGui::Render();
}

void Gui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::LoadStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding     = { 15, 15 };
    style.WindowRounding    = 0.0f;
    style.FramePadding      = { 5, 5 };
    style.FrameRounding     = 0.0f;
    style.ItemSpacing       = { 12, 8 };
    style.ItemInnerSpacing  = { 8, 6 };
    style.IndentSpacing     = 25.0f;
    style.ScrollbarSize     = 15.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize       = 5.0f;
    style.GrabRounding      = 3.0f;

    style.Colors[ImGuiCol_Text]               = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]       = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_FrameBg]            = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]     = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive]      = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]         = ImVec4(0.80f, 0.80f, 0.80f, 0.30f);
    style.Colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.90f, 0.90f, 0.90f, 0.75f);
    style.Colors[ImGuiCol_TitleBg]            = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]      = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TabActive]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_Tab]                = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TabHovered]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]       = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_Separator]          = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_SeparatorHovered]   = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]    = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
}

void Gui::ShowSimulationProps(uint32_t* particleCount, float* particleSize)
{
    ImGui::Begin("Simulation Properties");
    ImGui::Text("Particle Data");
    ImGui::SliderInt("Count", reinterpret_cast<int32_t*>(particleCount), 0,
                     Get().m_MaxParticleCount);
    ImGui::SliderFloat("Particle Size", particleSize, 0.0f, 0.2f);
    ImGui::End();
}

void Gui::ShowAnalysisProps(Analyser::Properties* props)
{
    ImGui::Begin("Analysis Properties");
    ImGui::Checkbox("Analysis", &props->ShowBoundingBoxes);
    ImGui::Text("Bounding boxes");
    ImGui::SliderFloat("r", &props->BoundingBoxColor.Value.x, 0, 1);
    ImGui::SliderFloat("g", &props->BoundingBoxColor.Value.y, 0, 1);
    ImGui::SliderFloat("b", &props->BoundingBoxColor.Value.z, 0, 1);
    ImGui::End();
}

void Gui::ShowSimulationStats()
{
    ImGui::Begin("Simulation Statistics");
    ImGui::Text("Average ms/frame: %.3f ", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Average FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Text("OpenGL Renderer:");
    ImGui::Text("%s", glGetString(GL_RENDERER));
    ImGui::Separator();
    ImGui::Text("OpenGL Version:");
    ImGui::Text("%s", glGetString(GL_VERSION));
    ImGui::End();
}

void Gui::ShowSimulation(Framebuffer* framebuffer)
{
    ImGui::Begin("Simulation Viewport");
    ImGui::BeginChild("Simulation");

    ImVec2 maxSize = ImGui::GetWindowSize();
    Get().m_AnalysisWindowSize =
        ImVec2(std::min(maxSize.x, maxSize.y), std::min(maxSize.x, maxSize.y));
    ImVec2 cursorPos = ImGui::GetCursorPos();
    ImVec2 offset((maxSize.x - Get().m_AnalysisWindowSize.x) / 2.0f,
                  (maxSize.y - Get().m_AnalysisWindowSize.y) / 2.0f);

    ImGui::SetCursorPosX(cursorPos.x + offset.x);
    ImGui::SetCursorPosY(cursorPos.y + offset.y);

    ImGui::Image(reinterpret_cast<void*>(framebuffer->GetColorAttachment()),
                 Get().m_AnalysisWindowSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
    ImGui::End();
}

void Gui::ShowAnalysis(uint32_t analysisTexture)
{
    ImGui::Begin("Analysis Viewport");
    ImGui::BeginChild("Analysis");

    ImVec2 maxSize = ImGui::GetWindowSize();
    ImVec2 size(std::min(maxSize.x, maxSize.y), std::min(maxSize.x, maxSize.y));
    ImVec2 cursorPos = ImGui::GetCursorPos();
    ImVec2 offset((maxSize.x - size.x) / 2.0f, (maxSize.y - size.y) / 2.0f);

    ImGui::SetCursorPosX(cursorPos.x + offset.x);
    ImGui::SetCursorPosY(cursorPos.y + offset.y);

    ImGui::Image(reinterpret_cast<void*>(analysisTexture), size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
    ImGui::End();
}

void Gui::ShowAnalysisOutput(Analyser::Properties* props, uint32_t texture)
{
    ImGui::Begin("Analysis Output");
    ImGui::Text("Area of bounding boxes: %d", props->AreaOfBoxes);
    ImGui::Text("Area of sample image: %d", props->AreaOfAnalysisWindow);
    ImGui::Text("Est. amount of particles (percent): %f",
                static_cast<float>(props->AreaOfBoxes) /
                    static_cast<float>(props->AreaOfAnalysisWindow));
    ImGui::End();
}