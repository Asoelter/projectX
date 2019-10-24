#include "world.h"

World::World() 
	: activeMap_(nullptr)
    , activeMapX_(0)
    , activeMapY_(0)
{
    unsigned mapInfo1[9][16] = {
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

    unsigned mapInfo2[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

    unsigned mapInfo3[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

    unsigned mapInfo4[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

	tileMaps_.push_back(std::vector<TileMap>());
	tileMaps_[0].emplace_back(mapInfo1);
	tileMaps_[0].emplace_back(mapInfo2);

	tileMaps_.push_back(std::vector<TileMap>());
	tileMaps_[1].emplace_back(mapInfo3);
	tileMaps_[1].emplace_back(mapInfo4);

	activeMap_ = &tileMaps_[0][0];
}

void World::draw() const
{
	activeMap_->draw();
}

TileMap* World::activeMap() const
{
	return activeMap_;
}

bool World::isOnScreen(int xIndex, int yIndex) const
{
    return xIndex < TileMap::width && yIndex < TileMap::height && xIndex > -1 && yIndex > -1;
}

bool World::isInWorld(int mapX, int mapY) const
{
    return mapX < tileMaps_[0].size() && mapY < tileMaps_.size() && mapX >= 0 && mapY >= 0;
}

TileState World::tileStateAt(const core::math::Point<float>& position)
{
    auto tileX = (int)((position.x + 1.0f) / Tile::width);
    auto tileY = (int)((position.y + 1.0f) / Tile::height);

    if(isOnScreen(tileX, tileY))
    {
        return activeMap_->isValidPosition(position) ? TileState::UNOCCUPIED : TileState::OCCUPIED;
    }
    else
    {
        auto mapX = activeMapX_;
        auto mapY = activeMapY_;

        if(tileX >= TileMap::width)
        {
            ++mapX;
            tileX = tileX % TileMap::width;
        }
        else if(tileX < 0)
        {
            --mapX;
            tileX = TileMap::width + tileX;
        }
        else if(tileY >= TileMap::height)
        {
            --mapY;
            tileY = tileY % TileMap::height;
        }
        else if(tileY < 0)
        {
            ++mapY;
            tileY = TileMap::height + tileY;
        }

        if(isInWorld(mapX, mapY))
        {
            const auto& testMap = tileMaps_[mapY][mapX];
            const auto result = testMap.isValidPosition(tileX, tileY) ? TileState::OFFSCREEN_UNOCCUPIED 
                                                                      : TileState::OCCUPIED;

            if(result == TileState::OCCUPIED) 
            {
                //TODO(asoelter): Log?
            }

            return result;
        }
        else
        {
            return TileState::OCCUPIED;
        }
    }
}
