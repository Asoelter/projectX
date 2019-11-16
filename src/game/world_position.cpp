#include "world_position.h"

#include "settings.h"

WorldPosition::WorldPosition(unsigned tileMapX, 
                             unsigned tileMapY, 
                             float    tileX, 
                             float    tileY) noexcept
    : quad_(tileMapX, tileMapY)
    , tilePos_(tileX, tileY)
{

}

WorldPosition::WorldPosition(const core::math::Point<unsigned>& quad,
                             const core::math::Point<float>& tilePos) noexcept
    : quad_(quad)
    , tilePos_(tilePos)
{

}

[[nodiscard]] 
core::math::Point<unsigned> WorldPosition::quadrant() const
{
    return quad_;
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
    auto quad       = lhs.quad_;

    const auto screenWidth  = global::screenXLimit;
    const auto screenHeight = global::screenYLimit;

    if(tilePos.x > screenWidth)
    {
        tilePos.x    -= screenWidth;
        quad.x += 1;
    }
    else if(tilePos.x < 0)
    {
        tilePos.x    += screenWidth;
        quad.x -= 1;
    }

    if(tilePos.y > screenHeight)
    {
        quad.y -= 1;
        tilePos.y    -= screenHeight;
    }
    else if(tilePos.y < 0)
    {
        tilePos.y += screenHeight;
        quad.y += 1;
    }

    return {quad, tilePos};
}
