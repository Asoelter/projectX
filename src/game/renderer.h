#ifndef RENDERER_H
#define RENDERER_H

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

    World world_;
    Player player_;
    std::vector<Roamer> roamers_;
};

#endif //RENDERER_H
