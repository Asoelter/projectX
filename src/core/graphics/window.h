#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "key.h"
#include "shader.h"

struct GLFWwindow;

namespace core::graphics
{

struct WindowDescriptor
{
    int widthInPixels;
    int heightInPixels;
    int widthInScreenCoords;
    int heightInScreenCoords;
    std::string title;
};

class Window
{
public:
    Window(int width, int height, const std::string& title);
    Window(const WindowDescriptor& descriptor);
    ~Window();

    [[nodiscard]] bool open() const;
    void update() const;
    void swap() const;
    void setBackgroundColor(float r, float g, float b);
    [[nodiscard]] bool isPressed(Key key);

    void setVsync(bool enabled);
    [[nodiscard]] bool isVsync() const;

    void zoom(float factor);
    void zoomInAt(const core::math::vec2<float>& position);
    void zoomOutAt(const core::math::vec2<float>& position);

    static void setScreenLimits(float xlim, float ylim);

private:
    friend class Shader;

    static void setActiveShader(Shader* shader);
    static Shader* activeShader_;

private:
    GLFWwindow* window_;
    int width_;
    int height_;
    int screenCoordWidth_;
    int screenCoordHeight_;
    bool isVsync_;
};

}

#endif //WINDOW_H
