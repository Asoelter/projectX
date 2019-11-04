#include "world.h"

#include "world_position.h"

[[nodiscard]]
std::string toString(const WorldState& state)
{
    switch(state)
    {
        case WorldState::ONSCREEN        : return "ONSCREEN";
        case WorldState::OFFSCREEN       : return "OFFSCREEN";
        case WorldState::OFFSCREEN_UP    : return "OFFSCREEN_UP";
        case WorldState::OFFSCREEN_RIGHT : return "OFFSCREEN_RIGHT";
        case WorldState::OFFSCREEN_DOWN  : return "OFFSCREEN_DOWN";
        case WorldState::OFFSCREEN_LEFT  : return "OFFSCREEN_LEFT";
    }
}

[[nodiscard]]
WorldState translateTileState(const TileState& state)
{
    switch(state)
    {
        case TileState::UNOCCUPIED      : return WorldState::ONSCREEN;
        case TileState::OCCUPIED        : return WorldState::ONSCREEN;
        case TileState::OFFSCREEN_UP    : return WorldState::OFFSCREEN_UP;
        case TileState::OFFSCREEN_RIGHT : return WorldState::OFFSCREEN_RIGHT;
        case TileState::OFFSCREEN_DOWN  : return WorldState::OFFSCREEN_DOWN;
        case TileState::OFFSCREEN_LEFT  : return WorldState::OFFSCREEN_LEFT;
    }
}

//-----------------------------------------------------World State----------------------------------------------

World::World() 
	: activeMap_(nullptr)
    , activeMapX_(0)
    , activeMapY_(0)
{
    unsigned topLeft[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    unsigned topRight[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    unsigned bottomLeft[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

    unsigned bottomRight[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

	tileMaps_.push_back(std::vector<TileMap>());
	tileMaps_[0].emplace_back(topLeft);
	tileMaps_[0].emplace_back(topRight);

	tileMaps_.push_back(std::vector<TileMap>());
	tileMaps_[1].emplace_back(bottomLeft);
	tileMaps_[1].emplace_back(bottomRight);

	activeMap_ = &tileMaps_[0][0];
}

void World::draw() const
{
	activeMap_->draw();
}

void World::drawAt(const WorldPosition& position) const
{
    const auto worldPos = position.tileMapPos();
    const auto xWorldIndex = worldPos.x;
    const auto yWorldIndex = worldPos.y;

    tileMaps_[yWorldIndex][xWorldIndex].draw();
}

TileMap* World::activeMap() const
{
	return activeMap_;
}

[[nodiscard]]
bool World::isOnScreen(int xIndex, int yIndex) const
{
    return xIndex < TileMap::width && yIndex < TileMap::height && xIndex > -1 && yIndex > -1;
}

[[nodiscard]]
bool World::isInWorld(int mapX, int mapY) const
{
    return mapX < tileMaps_[0].size() && mapY < tileMaps_.size() && mapX >= 0 && mapY >= 0;
}

[[nodiscard]] 
TileState World::tileStateAt(const WorldPosition& position)
{
    const auto xMapPos  = position.tileMapPos().x;
    const auto yMapPos  = position.tileMapPos().y;
    const auto xPos     = position.tilePos().x;
    const auto yPos     = position.tilePos().y;
    const auto vPos     = core::math::Point<float>(xPos, yPos);

    return tileMaps_[yMapPos][xMapPos].tileStateAt(vPos);
}

[[nodiscard]] 
WorldState World::worldStateAt(const core::math::Point<float>& position)
{
    return translateTileState(activeMap_->tileStateAt(position));
}

