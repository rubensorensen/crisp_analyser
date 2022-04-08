#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "window.hpp"

#include <memory>

class Application
{
  public:

    Application(const char* name, uint32_t width, uint32_t height);
    ~Application();

    void Run();

  private:

    std::unique_ptr<Window> m_Window;
};

#endif  // APPLICATION_HPP