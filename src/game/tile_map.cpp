#include "tile_map.h"

#include <iostream>

#include "graphics/color.h"

TileMap::TileMap(unsigned mapInfo[9][16])
{
    const auto width = 2.0 / 16.0;
    const auto height = 2.0 / 9.0;

    auto xPos = -1.0f + (width / 2.0f);
    auto yPos = -1.0f + (height / 2.0f);

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 16; ++j)
        {
            const auto position = core::math::Point<float>(xPos, yPos);

            if(mapInfo[i][j] == 1)
            {
                const auto color = core::graphics::grey();
                map_[i][j] = std::make_unique<core::graphics::Rectangle>(width, height, position, color);
            }
            else
            {
                const auto color = core::graphics::white();
                map_[i][j] = std::make_unique<core::graphics::Rectangle>(width, height, position, color);
            }

            mapInfo_[i][j] = mapInfo[i][j];
            xPos += width;
        }

        xPos = -1 + (width / 2.0f);
        yPos += height;
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
