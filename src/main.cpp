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

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    constexpr int width  = 720;
    constexpr int height = 480;
    bool running         = true;

    core::graphics::Window window(width, height, "projectX");
    core::graphics::Shader shader("src/res/shaders/grad.vs", "src/res/shaders/grad.fs");
    core::audio::Speaker   speaker;

    Tile player({0.0f, 0.0f}, core::graphics::blue());

    unsigned mapInfo[9][16] = {
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
        1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };

    TileMap tilemap(mapInfo);
    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.7f;

    while(running && window.open())
    {
        const auto begin = std::chrono::system_clock::now();

        if(window.isPressed(core::graphics::Key::Escape))
        {
            running = false;
        }

        if(window.isPressed(core::graphics::Key::Up))
        {
            player.move({0.00f, frameTime * screenSpacePerSecond});
        }
        if(window.isPressed(core::graphics::Key::Right))
        {
            player.move({frameTime * screenSpacePerSecond, 0.00f});
        }
        if(window.isPressed(core::graphics::Key::Down))
        {
            player.move({0.00f, frameTime * -screenSpacePerSecond});
        }
        if(window.isPressed(core::graphics::Key::Left))
        {
            player.move({frameTime * -screenSpacePerSecond, 0.00f});
        }

        window.setBackgroundColor(1.0f, 0.0f, 1.0f);
        window.update();
        shader.bind();

        tilemap.draw();
        player.draw();
        window.swap();

#ifndef WIN32
        auto const audioBuffer = speaker.tone(256);

        if(!speaker.playing())
        {
            speaker.play(audioBuffer);
        }
#endif 
    } 

    return 0;
} 

//double getTime()
//{
    //timespec now;
    //clock_gettime(CLOCK_MONOTONIC, &now);
    //return now.tv_sec + now.tv_nsec / 100000000.0;
//}
=======

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 
>>>>>>> 32cae73290f278bdb301e685adae8c3a31c5f220
