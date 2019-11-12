#include "tile_map.h"

#include <iostream>

#include "graphics/color.h"
#include "../util/handmade_util.h"

std::string toString(TileState state)
{
    switch(state)
    {
        case TileState::UNOCCUPIED      :   return "UNOCCUPIED";
        case TileState::OCCUPIED        :   return "OCCUPIED";
    }
}

//-----------------------------------------------------Tile----------------------------------------------------

Tile::Tile(const core::math::Point<float>& pos, TileState state)
    : tile_(width, height, pos, state == TileState::UNOCCUPIED ? core::graphics::white()
                                                               : core ::graphics::grey())
    , state_(state)
{

}

void Tile::draw() const
{
    tile_.draw();
}

void Tile::move(const core::math::vec2<float>& direction)
{
    tile_.move(direction);
}

[[nodiscard]]
core::math::Point<float> Tile::position() const
{
    return tile_.position();
}

[[nodiscard]]
TileState Tile::state() const
{
    return state_;
}

void Tile::setColor(const core::graphics::Color& color) 
{
    tile_.setColor(color);
}

//-----------------------------------------------------Tile Map------------------------------------------------

TileMap::TileMap(unsigned mapInfo[9][16])
{
    auto xPos = Tile::width  / 2.0f;
    auto yPos = Tile::height / 2.0f;

    for(int i = 0; i < rows ; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            const auto position = core::math::Point<float>(xPos, yPos);

            if(mapInfo[i][j] == 1)
            {
                map_[i][j] = std::make_unique<Tile>(position, TileState::OCCUPIED);
            }
            else
            {
                map_[i][j] = std::make_unique<Tile>(position, TileState::UNOCCUPIED);
            }

            mapInfo_[i][j] = mapInfo[i][j];
            xPos += Tile::width;
        }

        xPos = Tile::width / 2.0f;
        yPos += Tile::height;
    }
}

void TileMap::draw() const
{
    for(const auto& row : map_)
    {
        for(const auto& tile : row)
        {
            tile->draw();
        }
    }
}

void TileMap::move(const core::math::vec2<float>& direction)
{
    for(const auto& row : map_)
    {
        for(const auto& tile : row)
        {
            tile->move(direction);
        }
    }
}

[[nodiscard]] 
TileState TileMap::tileStateAt(const core::math::Point<float>& position) const
{
    const auto x = static_cast<int>((position.x) / Tile::width);
    const auto y = static_cast<int>((position.y) / Tile::height);

    if(x < columns && y < rows && x >= 0 && y >= 0)
    {
        return map_[y][x]->state();
    }

    handmade_assert(false);
    return TileState::OCCUPIED;
}

