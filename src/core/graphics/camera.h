#ifndef CAMERA_H
#define CAMERA_H

#include "../math/mat4.h"

namespace core::graphics
{

class Camera
{
public:
    Camera(int viewWidth, int viewHeight);

    void update();

    void zoomIn();
    void zoomOut();

private:
    math::mat4<float>   zoom_;
    float               zoomScale_;
    int                 width_;
    int                 height_;
    bool                needToSetLimits_;
    bool                needToSetScale_;
};

}

#endif //CAMERA_H
