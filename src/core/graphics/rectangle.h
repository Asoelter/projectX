#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <memory>

#include "../math/point.h"
#include "../math/vec2.h"

#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/color.h"

namespace core::graphics
{
class Rectangle
{
public:
    Rectangle(float width, float height,
              const math::Point<float>& pos, 
              const Color& color);

    ~Rectangle();

    void draw() const;
    void move(const math::vec2<float>& direction);

private:
    static std::unique_ptr<Shader> shader_;

private:
    float dimension_;
    math::vec2<float> offset_;
    std::unique_ptr<Mesh<float>> mesh_;
    Color color_;

};
}

#endif //RECTANGLE_H
