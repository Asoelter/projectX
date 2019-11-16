#include <iostream>
#include <chrono>

#include "util/handmade_util.h"

#include "core/graphics/drawable.h"
#include "core/graphics/rectangle.h"
#include "core/graphics/window.h"

#include "core/math/vec2.h"

#include "game/tile_map.h"
#include "game/player.h"
#include "game/roamer.h"
#include "game/world.h"
#include "game/world_position.h"
#include "game/settings.h"

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    constexpr int width  = 720;
    constexpr int height = 480;
    bool running         = true;

    core::graphics::Window window(width, height, "projectX");

    core::graphics::Rectangle::setScreenLimits(global::screenXLimit, global::screenYLimit);
    Player player(25.0f, 25.0f);
    Roamer roamer(34.0f, 34.0f);
    
	World world;
    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.5f * global::screenXLimit;

    while(running && window.open())
    {
        const auto begin = std::chrono::system_clock::now();

        if(window.isPressed(core::graphics::Key::Escape))
        {
            running = false;
        }

        auto direction = core::math::vec2<float>(0.0f, 0.0f);
        const auto displacement = frameTime * screenSpacePerSecond;

        if(window.isPressed(core::graphics::Key::Up))
        {
            direction.y += displacement;
        }
        if(window.isPressed(core::graphics::Key::Right))
        {
            direction.x += displacement;
        }
        if(window.isPressed(core::graphics::Key::Down))
        {
            direction.y -= displacement;
        }
        if(window.isPressed(core::graphics::Key::Left))
        {
            direction.x -= displacement;
        }

        if(world.positionOpen(player.position() + direction))
        {
            player.move(direction);
        }

        // will internally decide to move or not
        roamer.move(world, displacement);

        window.setBackgroundColor(1.0f, 0.0f, 1.0f);
        window.update();

        world.drawAt(player.position());

        // I don't really like the idea of having to call 'draw'
        // for each new character we create, it would be cool if we could add
        // each character to a vector, loop over it, and call draw on each
        // character.
        player.draw();

        // only draw the roamer if he is active on this tile
        if (world.contains(roamer.position())) {
            roamer.draw();
        }

        window.swap();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 

