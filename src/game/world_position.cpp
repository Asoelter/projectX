#include "world_position.h"


WorldPosition::WorldPosition(unsigned tileMapX, 
                             unsigned tileMapY, 
                             float    tileX, 
                             float    tileY) noexcept
    : tileMapPos_(tileMapX, tileMapY)
    , tilePos_(tileX, tileY)
{

}

WorldPosition::WorldPosition(const core::math::Point<unsigned>& tileMapPos,
                             const core::math::Point<float>& tilePos) noexcept
    : tileMapPos_(tileMapPos)
    , tilePos_(tilePos)
{

}

[[nodiscard]] 
core::math::Point<unsigned> WorldPosition::tileMapPos() const
{
    return tileMapPos_;
}

[[nodiscard]]
core::math::Point<float> WorldPosition::tilePos() const
{
    return tilePos_;
}

void WorldPosition::move(const core::math::vec2<float>& direction)
{
    *this = *this + direction;
}

WorldPosition operator+(const WorldPosition& rhs, 
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
