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

void Gui::Init(Window* window, int32_t maxParticleCount)
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

void Gui::Update(Framebuffer* simulationBuffer, Framebuffer* analysisBuffer, int32_t* particleCount)
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

    ShowSimulationProps(particleCount);
    ShowSimulationStats();
    ShowSimulation(simulationBuffer);
    ShowAnalysis(analysisBuffer);
    ShowLog();

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

void Gui::ShowSimulationProps(int32_t* particleCount)
{
    static float particleSpread = 0.5f;
    ImGui::Begin("Simulation Properties");
    ImGui::Text("Particle Data");
    ImGui::SliderInt("Count", particleCount, 0, Get().m_MaxParticleCount);
    ImGui::SliderFloat("Spread", &particleSpread, 0.0f, 1.0f);
    ImGui::End();
}

void Gui::ShowSimulationStats()
{
    ImGui::Begin("Simulation Statistics");
    ImGui::Text("Average ms/frame: %.3f ", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Average FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void Gui::ShowSimulation(Framebuffer* framebuffer)
{
    ImGui::Begin("Simulation Viewport");
    ImGui::BeginChild("Simulation");

    ImGui::Image(reinterpret_cast<void*>(framebuffer->GetColorAttachment()), ImGui::GetWindowSize(),
                 ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
    ImGui::End();
}

void Gui::ShowAnalysis(Framebuffer* framebuffer)
{
    ImGui::Begin("Analysis Viewport");
    ImGui::BeginChild("Analysis");

    ImGui::Image(reinterpret_cast<void*>(framebuffer->GetColorAttachment()), ImGui::GetWindowSize(),
                 ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
    ImGui::End();
}

void Gui::ShowLog()
{
    ImGui::Begin("Log");
    ImGui::End();
}