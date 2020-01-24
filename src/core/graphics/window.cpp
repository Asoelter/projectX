#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../util/handmade_util.h"

namespace core::graphics
{

Window::Window(int width, int height, const std::string& title)
    : width_(width)
    , height_(height)
    , isVsync_(true)
{
    if(!glfwInit())
    {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width_, height_, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    //glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    setVsync(true);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        exit(-1);
    }
}

Window::~Window()
{
    glfwDestroyWindow(window_);
}

bool Window::open() const
{
    return !glfwWindowShouldClose(window_);
}

void Window::update() const
{
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap() const
{
    glfwSwapBuffers(window_);
}

void Window::setBackgroundColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0f);
}

bool Window::isPressed(Key key)
{
    return glfwGetKey(window_, key);
}

void Window::setVsync(bool enabled)
{
    glfwSwapInterval(static_cast<int>(enabled));
}

bool Window::isVsync() const
{
    return isVsync_;
}

}
