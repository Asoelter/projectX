#include <iostream>
#include <chrono>
#include <unordered_map>

#include "util/image_reader.h"
#include "util/handmade_util.h"

#include "core/graphics/drawable.h"
#include "core/graphics/rectangle.h"
#include "core/graphics/texture.h"
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

    core::graphics::Window::setScreenLimits(global::screenXLimit, global::screenYLimit);
    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.5f * global::screenXLimit;

    auto tex = std::make_unique<core::graphics::Texture>("src/res/textures/test_hero_front_head.bmp");
    core::graphics::Rectangle hero(30.0f, 50.0f, {50.0f,50.0f}, std::move(tex));

    Renderer renderer;

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
        if(window.isPressed(core::graphics::Key::K))
        {
            static float zoomInLevel = 1.0f;
            window.zoom(zoomInLevel);
            zoomInLevel *= 0.985f;
        }
        if(window.isPressed(core::graphics::Key::J))
        {
            static float zoomInLevel = 1.0f;
            window.zoom(zoomInLevel);
            zoomInLevel += 0.01f;
        }

        window.update();

        renderer.render(direction, displacement);
        hero.move(direction);
        hero.draw();

        window.swap();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 

