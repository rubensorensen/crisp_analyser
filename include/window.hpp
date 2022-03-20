#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <memory>
#include <stdint.h>
#include <string>

class Window
{
  public:

    struct Properties
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
    };

    Window(const Properties&);
    void Init(bool);
    void Update();
    void Terminate();

    void InitGui();

    inline bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
    inline const Properties& GetProperties() const { return m_Properties; }

    inline void SetProperties(const Properties& props) { m_Properties = props; }

  private:

    GLFWwindow* m_Window;
    Properties m_Properties;
};

#endif  // WINDOW_HPP