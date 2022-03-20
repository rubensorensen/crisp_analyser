#ifndef GUI_HPP
#define GUI_HPP

#include "frame_buffer.hpp"
#include "window.hpp"

class Gui
{
  public:

    static void Init(Window*);
    static void Terminate();
    static void Update(Framebuffer*, Framebuffer*);

  private:

    static Gui& Get();

    Gui(){};
    ~Gui(){};
    Gui(const Gui&) = delete;

    static void NewFrame();
    static void LoadStyle();

    static void ShowSimulationProps();
    static void ShowSimulationStats();
    static void ShowSimulation(Framebuffer*);
    static void ShowAnalysis(Framebuffer*);
    static void ShowLog();
};

#endif  // GUI_HPP