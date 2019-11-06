#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "tile_map.h"
#include "../core/math/point.h"
#include "../core/math/vec2.h"

class WorldPosition;

class World
{
public:
	World();

	void draw() const;

	void drawAt(const WorldPosition& position) const;

    [[nodiscard]] 
    TileState tileStateAt(const WorldPosition& position);

private:
    [[nodiscard]] 
    bool isOnScreen(int xIndex, int yIndex) const;

    [[nodiscard]] 
    bool isInWorld(int mapX, int mapY) const;

	std::vector<std::vector<TileMap>> tileMaps_;
};


#endif //WORLD_H
