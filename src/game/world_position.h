#ifndef WORLD_POSITION_H
#define WORLD_POSITION_H

#include "world.h"

class WorldPosition
{
public:
    WorldPosition(unsigned tileMapX, 
                  unsigned tileMapY, 
                  float    tileX, 
                  float    tileY) noexcept;

    WorldPosition(const core::math::Point<unsigned>& tileMapPos,
                  const core::math::Point<float>& tilePos) noexcept;

    [[nodiscard]] 
    core::math::Point<unsigned> tileMapPos() const;

    [[nodiscard]]
    core::math::Point<float> tilePos() const;

    void move(const core::math::vec2<float>& direction);

    friend WorldPosition operator+(const WorldPosition& rhs, 
                                   const core::math::vec2<float>& lhs);
private:
    core::math::Point<unsigned> tileMapPos_;
    core::math::Point<float>    tilePos_;
};

#endif //WORLD_POSITION_H
