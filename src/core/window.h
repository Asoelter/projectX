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
    Escape = GLFW_KEY_ESCAPE
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
private:
    GLFWwindow* window_;
    int width_;
    int height_;
};

}

#endif //WINDOW_H
