#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//This is for roughing in screen limit
//code. Should eventually be removed
#include "rectangle.h"

#include "../math/mat4.h"

#include "../../util/handmade_util.h"

namespace core::graphics
{

core::graphics::Shader* Window::activeShader_ = nullptr;
core::graphics::Window* Window::activeWindow_ = nullptr;

Window::Window(const WindowDescriptor& descriptor)
    : width_(descriptor.widthInPixels)
    , zoom_(core::math::mat4<float>::identity())
    , zoomScale_(1.0f)
    , height_(descriptor.heightInPixels)
    , screenCoordWidth_(descriptor.widthInScreenCoords)
    , screenCoordHeight_(descriptor.heightInScreenCoords)
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

    const auto& title = descriptor.title;
    window_ = glfwCreateWindow(width_, height_, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);

    setVsync(true);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        exit(-1);
    }

	activeWindow_ = this;
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

    activeShader_->setUniformMat4f("scale", zoom_);
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

void Window::zoomIn()
{
    zoomScale_ -= 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;
}

void Window::zoomOut()
{
    zoomScale_ += 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;
}

void Window::setScreenLimits(float xlim, float ylim)
{
    if(!activeShader_)
    {
        //This is for roughing in screen limit
        //code. Should eventually be removed
        Rectangle::createShaders(); 
    }

    activeShader_->setUniform1f("xLimit", xlim);
    activeShader_->setUniform1f("yLimit", ylim);
}

void Window::setActiveShader(Shader* shader)
{
    activeShader_ = shader;

	activeWindow_->onShaderChange();
}

void Window::onShaderChange()
{
    setScreenLimits(screenCoordWidth_, screenCoordHeight_);
}

}
