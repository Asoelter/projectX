#include <iostream>
#include <chrono>

#ifdef WIN32
#   include<Windows.h>
#endif //WIN32

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
        auto pos = renderer.playerPos();
        camera.follow(pos);

        window.swap();

        camera.update();

        const auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = end - begin;
        frameTime = static_cast<float>(delta.count());
    } 

    return 0;
} 

#ifdef WIN32
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    main(0, nullptr);
}
#endif //WIN32
