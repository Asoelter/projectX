#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "../core/graphics/drawable.h"
#include "tile_map.h"
#include "world_position.h"

class Player
{
public:
    Player(float x, float y);

    void move(const core::math::vec2<float> direction);
    void draw() const;
    void printPosition() const;

    [[nodiscard]] 
    WorldPosition position() const;

    core::graphics::Rectangle const & shape() const{
        return rect_;
    }

private:
    WorldPosition position_;
    core::graphics::Rectangle rect_;
};

REGISTER_DRAWABLE(Player);

#endif //PLAYER_H
