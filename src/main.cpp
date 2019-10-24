#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

#include "util/handmade_util.h"

#include "core/audio/speaker.h"

#include "core/graphics/shader.h"
#include "core/graphics/window.h"
#include "core/graphics/mesh.h"
#include "core/graphics/square.h"

#include "core/math/vec2.h"

#include "game/tile_map.h"
#include "game/world.h"

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    constexpr int width  = 720;
    constexpr int height = 480;
    bool running         = true;

    core::graphics::Window window(width, height, "projectX");
    core::audio::Speaker   speaker;

    Tile player({0.0f, 0.0f}, core::graphics::blue());

	World world;
	auto tilemap = world.activeMap();
    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.7f;

    while(running && window.open())
    {
        const auto begin = std::chrono::system_clock::now();

        if(window.isPressed(core::graphics::Key::Escape))
        {
            running = false;
        }

        auto direction = core::math::vec2<float>(0.0f, 0.0f);

        if(window.isPressed(core::graphics::Key::Up))
        {
            direction.y += frameTime * screenSpacePerSecond;
        }
        if(window.isPressed(core::graphics::Key::Right))
        {
            direction.x += frameTime * screenSpacePerSecond;
        }
        if(window.isPressed(core::graphics::Key::Down))
        {
            direction.y -= frameTime * screenSpacePerSecond;
        }
        if(window.isPressed(core::graphics::Key::Left))
        {
            direction.x -= frameTime * screenSpacePerSecond;
        }

        if(world.tileStateAt(player.position() + direction) != TileState::OCCUPIED)
        {
            player.move(direction);
        }

        std::cout << toString(world.tileStateAt(player.position() + direction)) << std::endl;

        window.setBackgroundColor(1.0f, 0.0f, 1.0f);
        window.update();

		world.draw();
        player.draw();
        window.swap();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 

