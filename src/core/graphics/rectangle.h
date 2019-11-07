#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <memory>

#include "drawable.h"

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
    void moveTo(const math::Point<float>& position);
    void setColor(const Color& color);
    math::Point<float> position() const;

private:
    static std::unique_ptr<Shader> shader_;

private:
    float dimension_;
    math::vec2<float> offset_;
    const math::Point<float> initialPosition_;
    std::unique_ptr<Mesh<float>> mesh_;
    Color color_;

};
}

REGISTER_DRAWABLE(core::graphics::Rectangle);

#endif //RECTANGLE_H
