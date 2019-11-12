#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <array>
#include <memory>

#include "graphics/drawable.h"
#include "graphics/rectangle.h"

#include "settings.h"

enum class TileState
{
    UNOCCUPIED,
    OCCUPIED,
};

std::string toString(TileState state);

class Tile
{
public:
    Tile(const core::math::Point<float>& pos, TileState state);

    void draw() const;
    void move(const core::math::vec2<float>& direction);

    [[nodiscard]] 
    core::math::Point<float> position() const;

    [[nodiscard]]
    TileState state() const;

    void setColor(const core::graphics::Color& color);

    static constexpr auto width  = (2.0f / 16.0f) * (global::screenXLimit / 2.0f);
    static constexpr auto height = (2.0f / 9.0f)  * (global::screenYLimit / 2.0f);
private:
    core::graphics::Rectangle tile_;
    TileState state_;
};

class TileMap
{
public:
    TileMap(unsigned mapInfo[9][16]);

    void draw() const;
    void move(const core::math::vec2<float>& direction);

    [[nodiscard]] 
    TileState tileStateAt(const core::math::Point<float>& position) const;

    static constexpr auto columns = 16;
    static constexpr auto rows = 9;
    static constexpr auto width = columns * Tile::width;
    static constexpr auto height = columns * Tile::height;

private:
    using RowType = std::array<std::unique_ptr<Tile>, 16>;
    using MapType = std::array<RowType, 9>;

    unsigned mapInfo_[9][16];
    MapType map_;
};

REGISTER_DRAWABLE(Tile);
REGISTER_DRAWABLE(TileMap);

#endif //TILE_MAP_H

