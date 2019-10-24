#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "tile_map.h"

class World
{
public:
	World();

	void draw() const;
	TileMap* activeMap() const;
    TileState tileStateAt(const core::math::Point<float>& position);
private:
    bool isOnScreen(int xIndex, int yIndex) const;
    bool isInWorld(int mapX, int mapY) const;

	TileMap* activeMap_;
	std::vector<std::vector<TileMap>> tileMaps_;
    int activeMapX_;
    int activeMapY_;
};

#endif //WORLD_H
