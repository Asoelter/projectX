#ifndef ROAMER_H
#define ROAMER_H

#include <iostream>

#include "../core/graphics/drawable.h"
#include "tile_map.h"
#include "world_position.h"
#include "world.h"

// Obviously the fast majority of this code is shared
// with Player, I would like to refactor it but I know
// you wanted to avoid inheritance right?
class Roamer
{
public:
    Roamer(float x, float y);
    Roamer(Roamer&& r);

    void move(World const & world, float const displacement);
    void draw() const;
    void printPosition() const;

    [[nodiscard]]
    WorldPosition position() const;

private:
    WorldPosition position_;
    core::graphics::Rectangle rect_;
};

REGISTER_DRAWABLE(Roamer);

#endif //ROAMER_H
