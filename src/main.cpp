#include <iostream>
#include <chrono>

#include "util/handmade_util.h"

#include "core/graphics/camera.h"
#include "core/graphics/window.h"

#include "core/math/vec2.h"
#include "core/math/operations.h"

#include "game/renderer.h"
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

    auto frameTime = 0.0f;
    const auto screenSpacePerSecond = 0.5f * global::screenXLimit;

    Renderer renderer;

    core::graphics::Camera camera(global::screenXLimit, global::screenYLimit);

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
            camera.zoomIn();
        }
        if(window.isPressed(core::graphics::Key::J))
        {
            camera.zoomOut();
        }

        window.update();

        renderer.render(direction, displacement);
        camera.pan(-1 * core::math::vec3<float>(direction, 0.0f));

        window.swap();

        camera.update();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = delta.count();
    } 

    return 0;
} 

