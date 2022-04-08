#ifndef GUI_HPP
#define GUI_HPP

#include "analyser.hpp"
#include "frame_buffer.hpp"
#include "imgui.h"
#include "simulator.hpp"
#include "window.hpp"

class Gui
{
  public:

    static void Init(Window*, uint32_t);
    static void Terminate();
    static void Update(Framebuffer*, uint32_t, Simulator::Properties*, Analyser::Properties*);

  private:

    static Gui& Get();

    Gui(){};
    ~Gui(){};
    Gui(const Gui&) = delete;

    static void NewFrame();
    static void LoadStyle();

    static void ShowSimulationProps(uint32_t*, float*, float*);
    static void ShowAnalysisProps(Analyser::Properties*);
    static void ShowSimulationStats();
    static void ShowSimulation(Framebuffer*);
    static void ShowAnalysis(uint32_t);
    static void ShowAnalysisOutput(Analyser::Properties*, uint32_t);

  private:

    uint32_t m_MaxParticleCount;
    ImVec2 m_AnalysisWindowSize;
};

#endif  // GUI_HPP