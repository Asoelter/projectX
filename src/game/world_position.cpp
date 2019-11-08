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

WorldPosition operator+(const WorldPosition& lhs, 
                               const core::math::vec2<float>& rhs)
{
    auto tilePos    = lhs.tilePos_ + rhs;
    auto tileMapPos = lhs.tileMapPos_;

    const auto screenWidth  = 100.0;
    const auto screenHeight = 100.0;

    if(tilePos.x > screenWidth)
    {
        tilePos.x    -= screenWidth;
        tileMapPos.x += 1;
    }
    else if(tilePos.x < 0)
    {
        tilePos.x    += screenWidth;
        tileMapPos.x -= 1;
    }

    if(tilePos.y > screenHeight)
    {
        tileMapPos.y -= 1;
        tilePos.y    -= screenHeight;
    }
    else if(tilePos.y < 0)
    {
        tilePos.y += screenHeight;
        tileMapPos.y += 1;
    }

    return {tileMapPos, tilePos};
}
