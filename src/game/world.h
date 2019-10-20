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
private:
	TileMap* activeMap_;
	std::vector<std::vector<TileMap>> tileMaps_;
};

#endif //WORLD_H
