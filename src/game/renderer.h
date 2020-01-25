#ifndef RENDERER_H
#define RENDERER_H

#include "hero.h"
#include "player.h"
#include "roamer.h"
#include "world.h"

#include <vector>

class Renderer
{
public:
    using vec2f = core::math::vec2<float>;
    Renderer();

    void render(const vec2f& direction, float displacement);
private:
    void checkForCollisions();

    void checkForCollisionsWithRoamers();
    void checkForCollisionsWithWalls();

    bool playerRightOfObject(WorldPosition r);
    bool playerAboveObject(WorldPosition r);

    World world_;
    Player player_;
    Hero hero_;
    std::vector<Roamer> roamers_;
};

#endif //RENDERER_H
