#include <He/App/GLFW3Window.hpp>
#include <exception>
#include <fmt/core.h>
#include <He/Log.hpp>
namespace He::App {
    void GLFW3Window::_glfw3KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto _mods = *(Input::KeyModifiers*)&mods;
        const auto _key = Input::GLFW3KeyMap(key);
        auto _this = static_cast<GLFW3Window*>(glfwGetWindowUserPointer(window));
        if (action != GLFW_RELEASE) {
            if (action == GLFW_REPEAT) {
                _mods.Repeat = true;
            }
            _this->OnKeyDown(_key, _mods);
        }
        else {
            _this->OnKeyUp(_key, _mods);
        }
    }

    GLFW3Window::GLFW3Window(const char* title, int width, int height) : BaseWindow(title, width, height) {
        DEBUG_INFO("Attempt to create GLFW3 window");

        this->_windowHandler = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if(!this->_windowHandler){
            const char* desc ;
            glfwGetError(&desc);

            throw std::runtime_error(fmt::format("Couldn't create GLFW3 window: {}", desc ? desc : "Unknown error"));
        }

        glfwSetWindowUserPointer(this->_windowHandler, this);
        glfwSetKeyCallback(this->_windowHandler, GLFW3Window::_glfw3KeyCallback);

        DEBUG_INFO("GLFW3 window created successful");
    }
    GLFW3Window::~GLFW3Window(){
        DEBUG_INFO("Destroying GLFW3 window");
        glfwDestroyWindow(this->_windowHandler);
    }
    void GLFW3Window::SetTitle(const char* t) {
        this->title = t;
        glfwSetWindowTitle(this->_windowHandler, t);
    }
    void GLFW3Window::Resize(){
        glfwSetWindowSize(this->_windowHandler, this->width, this->height);
    }
    bool GLFW3Window::ShouldClose(){
        return !!glfwWindowShouldClose(this->_windowHandler);
    }
    void GLFW3Window::MakeContextCurrent(){
        glfwMakeContextCurrent(this->_windowHandler);
    }
    void GLFW3Window::SwapBuffers(){
        glfwSwapBuffers(this->_windowHandler);
    }

    void GLFW3Window::OnKeyDown(Input::Keys key, Input::KeyModifiers mods) {
        DEBUG_INFO("KEY DOWN {} SHIFT={} CONTROL={} ALT={} SUPER={} CAPSLOCK={} NUMLOCK={} REPEAT={}",
            Input::GetKeyName(key),
            (bool)mods.Shift, (bool)mods.Control, (bool)mods.Alt, (bool)mods.Super, (bool)mods.CapsLock, (bool)mods.NumLock, (bool)mods.Repeat);
    }

    void GLFW3Window::OnKeyUp(Input::Keys key, Input::KeyModifiers mods) {
        DEBUG_INFO("KEY UP {} SHIFT={} CONTROL={} ALT={} SUPER={} CAPSLOCK={} NUMLOCK={} REPEAT={}",
            Input::GetKeyName(key),
            (bool)mods.Shift, (bool)mods.Control, (bool)mods.Alt, (bool)mods.Super, (bool)mods.CapsLock, (bool)mods.NumLock, (bool)mods.Repeat);
    }
}
