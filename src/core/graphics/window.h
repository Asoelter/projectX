#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace core::graphics
{

enum Key
{
    Escape  = GLFW_KEY_ESCAPE,
    Up      = GLFW_KEY_UP,
    Right   = GLFW_KEY_RIGHT,
    Down    = GLFW_KEY_DOWN,
    Left    = GLFW_KEY_LEFT
};

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool open() const;
    void update() const;
    void swap() const;
    void setBackgroundColor(float r, float g, float b);
    bool isPressed(Key key);

    void setVsync(bool enabled);
    bool isVsync() const;
private:
    GLFWwindow* window_;
    int width_;
    int height_;
    bool isVsync_;
};

}

#endif //WINDOW_H
