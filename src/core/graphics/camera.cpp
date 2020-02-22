#include "camera.h"

#include <cmath>
#include <iostream>

#include "shader.h"

namespace core::graphics
{

Camera::Camera(int viewWidth, int viewHeight)
    : zoom_(math::mat4<float>::identity())
    , eye_({0.0f, 0.0f, -1.0f})
    , center_({0.0f, 0.0f,  1.0f})
    , up_({0.0f, 1.0f,  0.0f})
    , view_(math::mat4<float>::lookAt({0.0f, 0.0f, -1.0f}, {0.0, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}))
    , projection_(math::mat4<float>::perspective(1.57f, 16.0f / 9.0f, 
                                                -1.0f, 1.0f))
    , zoomScale_(1.0f)
    , width_(viewWidth)
    , height_(viewHeight)
{

}

void Camera::update()
{
    auto activeShader = Shader::activeShader();
    static auto count = 0.0f;

    if(activeShader)
    {
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

void Camera::pan(const core::math::vec3<float>& direction)
{
    for(int i = 0; i < core::math::vec3<float>::size; ++i)
    {
        eye_.data[i] += direction.data[i];
        center_.data[i] += direction.data[i];
    }

    view_ = math::mat4<float>::lookAt(eye_, center_, up_);
}

}
