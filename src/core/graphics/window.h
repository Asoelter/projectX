#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <string>

#include "key.h"
#include "shader.h"

struct GLFWwindow;

namespace core::graphics
{

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    [[nodiscard]] bool open() const;
    void update() const;
    void swap() const;
    void setBackgroundColor(float r, float g, float b);
    [[nodiscard]] bool isPressed(Key key);

    void setVsync(bool enabled);
    [[nodiscard]] bool isVsync() const;

private:
    GLFWwindow* window_;
    int         width_;
    int         height_;
    bool        isVsync_;
};

}

#endif //WINDOW_H
