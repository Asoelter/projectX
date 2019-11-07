#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "drawable.h"

#include "../graphics/rectangle.h"

namespace core::graphics
{
class Square
{
public:
    Square(float dimension, 
           const math::Point<float>& pos, 
           const Color& color);

    void draw() const;
    void move(const math::vec2<float>& direction);
    void setColor(const Color& color);
private:
    Rectangle rectangle_;
};
}

REGISTER_DRAWABLE(core::graphics::Square);

#endif //SQUARE_H
