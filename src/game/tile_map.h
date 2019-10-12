#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <array>
#include <memory>

#include "graphics/rectangle.h"


class TileMap
{
public:
    TileMap(unsigned mapInfo[9][16]);

    void draw() const;

private:
    using RowType = std::array<std::unique_ptr<core::graphics::Rectangle>, 16>;
    using MapType = std::array<RowType ,9>;

    unsigned mapInfo_[9][16];
    MapType map_;
};

#endif //TILE_MAP_H
