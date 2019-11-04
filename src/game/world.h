#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "tile_map.h"
#include "../core/math/point.h"
#include "../core/math/vec2.h"

//TODO(asoelter): get rid of world states
enum class WorldState
{
    ONSCREEN,
    OFFSCREEN,
    OFFSCREEN_UP,
    OFFSCREEN_RIGHT,
    OFFSCREEN_DOWN,
    OFFSCREEN_LEFT
};

[[nodiscard]]
std::string toString(const WorldState& state);

[[nodiscard]]
WorldState translateTileState(const TileState& state);

class WorldPosition;

class World
{
public:
	World();

	void draw() const;

	void drawAt(const WorldPosition& position) const;

	[[nodiscard]] 
    TileMap* activeMap() const;

    [[nodiscard]] 
    TileState tileStateAt(const WorldPosition& position);

    [[nodiscard]] 
    WorldState worldStateAt(const core::math::Point<float>& position);

private:
    [[nodiscard]] 
    bool isOnScreen(int xIndex, int yIndex) const;

    [[nodiscard]] 
    bool isInWorld(int mapX, int mapY) const;

	TileMap* activeMap_;
	std::vector<std::vector<TileMap>> tileMaps_;
    int activeMapX_;
    int activeMapY_;
};


#endif //WORLD_H
