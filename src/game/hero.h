#ifndef HERO_H
#define HERO_H

#include "world_position.h"

#include "core/graphics/rectangle.h"

#include "core/math/point.h"
#include "core/math/vec2.h"

class Hero
{
public:
    Hero(const core::math::Point<float>& pos);

    void move(const core::math::vec2<float>& direction);
    void draw() const;
private:
    core::graphics::Rectangle head_;
    WorldPosition             position_;
};

#endif //HERO_H
