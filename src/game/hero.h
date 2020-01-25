#ifndef HERO_H
#define HERO_H

#include "world_position.h"

#include "core/graphics/rectangle.h"

#include "core/math/point.h"
#include "core/math/vec2.h"

enum class Orientation
{
    Back,
    Right,
    Front,
    Left
};

class Hero
{
public:
    Hero(const core::math::Point<float>& pos);

    void move(const core::math::vec2<float>& direction);
    void moveTo(const core::math::Point<float>& pos, const core::math::vec2<float>& direction);
    void draw() const;

private:
    core::graphics::Rectangle back_;
    core::graphics::Rectangle right_;
    core::graphics::Rectangle front_;
    core::graphics::Rectangle left_;
    WorldPosition             position_;
    Orientation               orientation_;
};

#endif //HERO_H
