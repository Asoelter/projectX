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

    void pan(const core::math::vec3<float>& direction);
    void follow(const core::math::Point<float>& position);

private:
    math::mat4<float>   zoom_;
    math::mat4<float>   view_;
    math::mat4<float>   projection_;
    math::vec3<float>   eye_;
    math::vec3<float>   center_;
    math::vec3<float>   up_;
    float               zoomScale_;
    int                 width_;
    int                 height_;
};

}

#endif //CAMERA_H
