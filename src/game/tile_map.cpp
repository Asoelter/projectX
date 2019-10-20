#include "tile_map.h"

#include <iostream>

#include "graphics/color.h"

//-----------------------------------------------------Tile----------------------------------------------------
Tile::Tile(const core::math::Point<float>& pos, const core::graphics::Color& color)
    : tile_(width, height, pos, color)
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

core::math::Point<float> Tile::position() const
{
    return tile_.position();
}

void Tile::setColor(const core::graphics::Color& color) 
{
    tile_.setColor(color);
}

//-----------------------------------------------------Tile Map------------------------------------------------

TileMap::TileMap(unsigned mapInfo[9][16])
{
    auto xPos = -1.0f + (Tile::width / 2.0f);
    auto yPos = -1.0f + (Tile::height / 2.0f);

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            const auto position = core::math::Point<float>(xPos, yPos);

            if(mapInfo[i][j] == 1)
            {
                const auto color = core::graphics::grey();
                map_[i][j] = std::make_unique<Tile>(position, color);
            }
            else
            {
                const auto color = core::graphics::white();
                map_[i][j] = std::make_unique<Tile>(position, color);
            }

            mapInfo_[i][j] = mapInfo[i][j];
            xPos += Tile::width;
        }

        xPos = -1.0f + (Tile::width/ 2.0f);
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

bool TileMap::isValidPosition(const core::math::Point<float>& position)
{
    const auto xIndex = (int)((position.x + 1.0f)/ Tile::width);
    const auto yIndex = (int)((position.y + 1.0f) / Tile::height);

    if(xIndex < width && yIndex < height)
    {
        return mapInfo_[yIndex][xIndex] == 0;
    }

    return false;
}
