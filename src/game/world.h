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

	void drawAt(const WorldPosition& position);

    [[nodiscard]] 
    TileState tileStateAt(const WorldPosition& position) const;

    [[nodiscard]]
    bool positionOpen(const WorldPosition& position) const;

    [[nodiscard]]
    bool contains(const WorldPosition& position) const;

    TileMap const & quadrant(const WorldPosition& position) const;

private:
	std::vector<std::vector<TileMap>> tileMaps_;
    unsigned activeY_ = 0;
    unsigned activeX_ = 0;
};


#endif //WORLD_H
