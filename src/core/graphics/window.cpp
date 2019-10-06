#include "window.h"

#include "../../util/handmade_util.h"

namespace core::graphics
{

Window::Window(int width, int height, const std::string& title)
{
    if(!glfwInit())
    {
        handmade_assert("could not initialize glfw" && false);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, "Handmade Hero", nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        handmade_assert("could not initialize glad" && false);
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
    glClear(GL_COLOR_BUFFER_BIT);
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

}
