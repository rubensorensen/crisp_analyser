#include "window.hpp"

#include <iostream>

int main(void)
{
    Window window({ "Crisp Solutions - Simulator", 1280, 720 });
    window.Init(true);
    while (!window.ShouldClose())
    {
        glClearColor(0.5f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.Update();
    }

    window.Terminate();

    return 0;
}