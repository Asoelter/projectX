#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <array>
#include <memory>

#include "graphics/rectangle.h"

class Tile
{
public:
    Tile(const core::math::Point<float>& pos, const core::graphics::Color& color);

    void draw() const;
    void move(const core::math::vec2<float>& direction);

    static constexpr auto width  = 2.0f / 16.0f;
    static constexpr auto height = 2.0f / 9.0f;
private:
    core::graphics::Rectangle tile_;
};

class TileMap
{
public:
    TileMap(unsigned mapInfo[9][16]);

    void draw() const;

    static constexpr auto width = 16;
    static constexpr auto height = 9;

private:
    using RowType = std::array<std::unique_ptr<Tile>, 16>;
    using MapType = std::array<RowType, 9>;

    unsigned mapInfo_[9][16];
    MapType map_;
};

#endif //TILE_MAP_H
