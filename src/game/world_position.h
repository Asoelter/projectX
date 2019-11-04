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
                                   const core::math::vec2<float>& lhs)
    {
        auto tilePos    = rhs.tilePos_ + lhs;
        auto tileMapPos = rhs.tileMapPos_;

        tileMapPos.x += static_cast<int>(tilePos.x);
        tileMapPos.y -= static_cast<int>(tilePos.y);

        if(tilePos.x > 1)
        {
            tilePos.x -= 2;
        }
        else if(tilePos.x < -1)
        {
            tilePos.x += 2;
        }

        if(tilePos.y > 1)
        {
            tilePos.y -= 2;
        }
        else if(tilePos.y < -1)
        {
            tilePos.y += 2;
        }

        return {tileMapPos, tilePos};
    }
private:
    core::math::Point<unsigned> tileMapPos_;
    core::math::Point<float>    tilePos_;
};

#endif //WORLD_POSITION_H
