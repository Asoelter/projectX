#include "square.h"

#include <vector>
#include "../graphics/shader.h"

namespace core::graphics
{

Square::Square(float dimension, const math::Point<float>& pos, const Color& color)
    : rectangle_(dimension, dimension, pos, color)
{
}

void Square::draw() const
{
    rectangle_.draw();
}

void Square::move(const math::vec2<float>& direction)
{
    rectangle_.move(direction);
}

void Square::setColor(const Color& color)
{
    rectangle_.setColor(color);
}

}
