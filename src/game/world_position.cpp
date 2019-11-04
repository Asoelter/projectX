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

