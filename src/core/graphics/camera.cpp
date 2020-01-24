#include "camera.h"

#include <cmath>
#include <iostream>

#include "shader.h"

namespace core::graphics
{

Camera::Camera(int viewWidth, int viewHeight)
    : zoom_(math::mat4<float>::identity())
    , view_(math::mat4<float>::lookAt({0.0f, 0.0f, -15.0f}, {0.0f, 0.0f, 3.0f}, {0.0f, 1.0f, 0.0f}))
    , projection_(math::mat4<float>::perspective(2.0f, 16.0f / 9.0f, -5.0f, 6.0f))
    , zoomScale_(1.0f)
    , width_(viewWidth)
    , height_(viewHeight)
{

}

void Camera::update()
{
    constexpr math::vec3<float> center = {0.0f, 0.0f, 0.0f};
    constexpr math::vec3<float> up = {0.0f, 1.0f, 0.0f};

    auto activeShader = Shader::activeShader();
    static auto count = 0.0f;

    if(activeShader)
    {
        const auto x = static_cast<float>(std::cos(count));
        const auto z = static_cast<float>(std::sin(count));
        view_ = math::mat4<float>::lookAt({x, 0.0f, z}, center, up);

        activeShader->setUniformMat4f("scale", zoom_);
        activeShader->setUniform1f("xLimit", width_);
        activeShader->setUniform1f("yLimit", height_);
        activeShader->setUniformMat4f("view", view_);
        activeShader->setUniformMat4f("projection", projection_);
    }
    else
    {
        //TODO(asoelter): Log this
    }

    count += 0.05f;
}

void Camera::zoomIn()
{
    zoomScale_ -= 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;
}

void Camera::zoomOut()
{
    zoomScale_ += 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;
}

}
