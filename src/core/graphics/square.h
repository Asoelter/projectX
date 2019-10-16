#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

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
private:
    Rectangle rectangle_;
};
}

#endif //SQUARE_H
