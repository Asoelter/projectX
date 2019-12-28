#include "hero.h"

    //Rectangle(float width, float height,
              //const math::Point<float>& pos,
              //std::unique_ptr<Texture>&& texture);

Hero::Hero(const core::math::Point<float>& pos)
    : head_(15.0f, 25.0f, pos, {"src/res/textures/test_hero_front_head.bmp"})
    , torso_(15.0f, 25.0f, pos, { "src/res/textures/test_hero_front_torso.bmp", 1 })
    , position_(0, 0, pos.x, pos.y)
{

}

void Hero::move(const core::math::vec2<float>& direction)
{
    head_.move(direction);
    torso_.move(direction);
}

void Hero::draw() const
{
    head_.draw();
    torso_.draw();
}
