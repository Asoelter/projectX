#include "hero.h"

Hero::Hero(const core::math::Point<float>& pos)
    : head_(15.0f, 25.0f, pos, 
            {{"src/res/textures/test_hero_front_head.bmp" , 0}, 
             {"src/res/textures/test_hero_front_cape.bmp", 1},
             {"src/res/textures/test_hero_front_torso.bmp" , 2}})
    , position_(0, 0, pos.x, pos.y)
{

}

void Hero::move(const core::math::vec2<float>& direction)
{
    head_.move(direction);
}

void Hero::draw() const
{
    head_.draw();
}
