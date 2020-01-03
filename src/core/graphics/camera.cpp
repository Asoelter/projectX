#include "camera.h"

#include <iostream>

#include "shader.h"

namespace core::graphics
{

Camera::Camera(int viewWidth, int viewHeight)
    : zoom_(core::math::mat4<float>::identity())
    , zoomScale_(1.0f)
    , width_(viewWidth)
    , height_(viewHeight)
    , needToSetLimits_(true)
    , needToSetScale_(false)
{

}

void Camera::update()
{
    auto activeShader = Shader::activeShader();

    if(needToSetScale_ && activeShader)
    {
        activeShader->setUniformMat4f("scale", zoom_);
        needToSetScale_ = false;
    }

    if(needToSetLimits_ && activeShader)
    {
        activeShader->setUniform1f("xLimit", width_);
        activeShader->setUniform1f("yLimit", height_);
        needToSetLimits_ = false;
    }

    if(!activeShader)
    {
        //TODO(asoelter): Log this
    }
}

void Camera::zoomIn()
{
    zoomScale_ -= 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;

    needToSetScale_ = true;
}

void Camera::zoomOut()
{
    zoomScale_ += 0.01f;

    zoom_[0][0] = zoomScale_;
    zoom_[1][1] = zoomScale_;
    zoom_[2][2] = zoomScale_;

    needToSetScale_ = true;
}

}
