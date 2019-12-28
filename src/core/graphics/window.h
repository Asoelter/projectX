#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "key.h"
#include "shader.h"

#include "../math/mat4.h"

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
    Window(const WindowDescriptor& descriptor);
    ~Window();

    [[nodiscard]] bool open() const;
    void update() const;
    void swap() const;
    void setBackgroundColor(float r, float g, float b);
    [[nodiscard]] bool isPressed(Key key);

    void setVsync(bool enabled);
    [[nodiscard]] bool isVsync() const;

    void zoomIn();
    void zoomOut();

    static void setScreenLimits(float xlim, float ylim);

private:
    friend class Shader;

    static void setActiveShader(Shader* shader);
    static Shader* activeShader_;
	static Window* activeWindow_;

private:
	void onShaderChange();

private:
    GLFWwindow*         window_;
    math::mat4<float>   zoom_;
    float               zoomScale_;
    int                 width_;
    int                 height_;
    int                 screenCoordWidth_;
    int                 screenCoordHeight_;
    bool                isVsync_;
};

}

#endif //WINDOW_H
