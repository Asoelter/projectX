#include <iostream>
#include <iomanip>
#include <cmath>
//#include <time.h>

#include "util/handmade_util.h"

#include "core/graphics/shader.h"
#include "core/graphics/window.h"
#include "core/graphics/mesh.h"
#include "core/graphics/square.h"

#include "core/audio/speaker.h"

#include "core/math/vec2.h"

//double getTime();

int main(int argc, char** argv)
{
    HANDMADE_UNUSED(argc); 
    HANDMADE_UNUSED(argv);

    constexpr int width  = 720;
    constexpr int height = 480;
    bool running         = true;

    core::graphics::Window window(width, height, "Custom window");
    core::graphics::Shader shader("src/res/shaders/grad.vs", "src/res/shaders/grad.fs");
    core::audio::Speaker   speaker;

    std::vector<float> vSquare = 
    {
        -1.0f, -1.0f, //bottom left
         1.0f, -1.0f, //bottom right
         1.0f,  1.0f, //top right
        -1.0f,  1.0f  //top left
    };

    std::vector<unsigned> vIndices = 
    {
        0, 1, 2, //bottom left triangle
        2, 3, 0  //bottom right triangle
    };

    core::graphics::MeshDescriptor descriptor;
    descriptor.valuesPerIndex = 2;
    descriptor.offsets = {0};
    descriptor.elementBuffer = vIndices;
    core::graphics::Mesh<float> mesh(vSquare, descriptor);
    core::graphics::Square square(0.5, core::math::Point<float>(0.0f, 0.0f));

    while(running && window.open())
    {
		if(window.isPressed(core::graphics::Key::Escape))
        {
            running = false;
        }

        if(window.isPressed(core::graphics::Key::Up))
        {
            square.move({0.00f, 0.01f});
        }
        if(window.isPressed(core::graphics::Key::Right))
        {
            square.move({0.01f, 0.00f});
        }
        if(window.isPressed(core::graphics::Key::Down))
        {
            square.move({0.00f, -0.01f});
        }
        if(window.isPressed(core::graphics::Key::Left))
        {
            square.move({-0.01f, 0.00f});
        }

        window.setBackgroundColor(0.0f, 0.6f, 0.8f);
        window.update();
        shader.bind();

        mesh.draw();
        square.draw();
        window.swap();

#ifndef WIN32
        const auto audioBuffer = speaker.tone(256);

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
