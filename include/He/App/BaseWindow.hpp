#ifndef HELIUM_APP_BASEWINDOW_HPP
#define HELIUM_APP_BASEWINDOW_HPP

#include <He/App/Input.hpp>
#include <He/Log.hpp>
namespace He::App {
    class BaseWindow {
        protected:
        int width;
        int height;
        const char* title;
        public:
        virtual ~BaseWindow() = default;

        BaseWindow(const char* title = "Helium Application", int width = 640, int height = 480);

        const char* Title();
        int Width() const;
        int Height() const;
        void SetWidth(int nw);
        void SetHeight(int nh);


        virtual void SetTitle(const char* t) {title = t;}
        virtual void Resize(){}
        virtual void Resize(int nw, int nh){this->width = nw; this->height = nh;}
        virtual void SwapBuffers(){}
        virtual void OnKeyDown(Input::Keys key, Input::KeyModifiers mods){DEBUG_ERROR("You couldn't see that");};
        virtual void OnKeyUp(Input::Keys key, Input::KeyModifiers mods){DEBUG_ERROR("You couldn't see that");};
        virtual void OnResize(int nw, int nh){}
    };
}

#endif