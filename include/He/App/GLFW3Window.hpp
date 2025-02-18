#ifndef HELIUM_APP_GLFW3WINDOW_HPP
#define HELIUM_APP_GLFW3WINDOW_HPP

#include <He/App/BaseWindow.hpp>
#include <GLFW/glfw3.h>

namespace He::App {
    class GLFW3Window : public BaseWindow {
        protected:
        GLFWwindow* _windowHandler;
        static void _glfw3KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void _glfw3ResizeCallback(GLFWwindow* window, int width, int height);
        public:
        GLFW3Window(const char* title = "Helium Application", int width = 640, int height = 480);
        ~GLFW3Window() override;
        
        void SetTitle(const char* t) override;
        void Resize() override;
        void SwapBuffers() override;
        void OnKeyDown(Input::Keys key, Input::KeyModifiers mods) override;
        void OnKeyUp(Input::Keys key, Input::KeyModifiers mods) override;

        bool ShouldClose();
        void MakeContextCurrent();

    };
}

#endif