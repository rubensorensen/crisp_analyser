#ifndef GUI_HPP
#define GUI_HPP

#include "frame_buffer.hpp"
#include "window.hpp"

class Gui
{
  public:

    static void Init(Window*, int32_t);
    static void Terminate();
    static void Update(Framebuffer*, Framebuffer*, int32_t*);

  private:

    static Gui& Get();

    Gui(){};
    ~Gui(){};
    Gui(const Gui&) = delete;

    static void NewFrame();
    static void LoadStyle();

    static void ShowSimulationProps(int32_t*);
    static void ShowSimulationStats();
    static void ShowSimulation(Framebuffer*);
    static void ShowAnalysis(Framebuffer*);
    static void ShowLog();

  private:

    int32_t m_MaxParticleCount;
};

#endif  // GUI_HPP