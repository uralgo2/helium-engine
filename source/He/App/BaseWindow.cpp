#include <He/App/BaseWindow.hpp>

namespace He::App {
    BaseWindow::BaseWindow(const char* title, int width, int height){
        this->title = title;
        this->width = width;
        this->height = height;
    }

    const char* BaseWindow::Title(){
        return this->title;
    }
    
    int BaseWindow::Width() const{
        return this->width;
    }
    
    int BaseWindow::Height() const{
        return this->height;
    }

    void BaseWindow::SetWidth(int nw){
        this->width = nw;
        this->Resize();
    }
    void BaseWindow::SetHeight(int nh){
        this->height = nh;
        this->Resize();
    }
}