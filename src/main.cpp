#include <iostream>
#include <chrono>

#include "util/file_reader.h"
#include "util/handmade_util.h"

#include "core/graphics/drawable.h"
#include "core/graphics/rectangle.h"
#include "core/graphics/window.h"

#include "core/math/vec2.h"

#include "game/renderer.h"
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
    window.setBackgroundColor(1.0f, 0.0f, 1.0f);

    core::graphics::Rectangle::setScreenLimits(global::screenXLimit, global::screenYLimit);
    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.5f * global::screenXLimit;

    Renderer renderer;
    
    try
    {
        FileReader reader("src/res/textures/loz3.png");
    }
    catch(std::invalid_argument e)
    {
        std::cout << e.what() << std::endl;
    }

    srand( time(NULL) );
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

        window.update();

        renderer.render(direction, displacement);

        window.swap();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 

