#include "renderer.h"


Renderer::Renderer()
    : world_()
    , player_(25.0f, 25.0f)
    , roamers_()
{

    roamers_.emplace_back(Roamer(34.0f, 34.0f));
}

void Renderer::render(const vec2f& direction, int displacement)
{
    std::cout << displacement << std::endl;
    world_.drawAt(player_.position());

    if(world_.positionOpen(player_.position() + direction))
    {
        player_.move(direction);
    }

    player_.draw();

    for(auto& roamer : roamers_)
    {
        roamer.move(world_, displacement);

        if(world_.contains(roamer.position()))
        {
            roamer.draw();
        }
    }
}
