#include "hero.h"

namespace
{

constexpr float pi             = (1.0f / 1.0f) * M_PI;
constexpr float threeFourthsPi = (3.0f / 4.0f) * M_PI;
constexpr float oneFourthsPi   = (1.0f / 4.0f) * M_PI;

bool facesUp(float angle)
{
    return threeFourthsPi >= angle && angle >= oneFourthsPi;
}

bool facesRight(float angle)
{
    return oneFourthsPi >= angle && angle >= (-1.0f * oneFourthsPi);
}

bool facesDown(float angle)
{
    return (-1.0f * oneFourthsPi) >= angle && angle >= (-1.0f * threeFourthsPi);
}

bool facesLeft(float angle)
{
    const auto isPositiveLeft = pi >= angle && angle >= threeFourthsPi;
    const auto isNegativeLeft = (-1.0f * threeFourthsPi) >= angle && angle >= (-1.0f * pi);

    return isPositiveLeft || isNegativeLeft;
}

Orientation calculateOrientation(const core::math::vec2<float>& direction)
{
    if(direction.x == 0.0f && direction.y == 0.0f)
    {
        return Orientation::Front;
    }

    const auto angle = atan2f(direction.y, direction.x);

    if(facesUp(angle))
    {
        return Orientation::Back;
    }
    else if(facesRight(angle))
    {
        return Orientation::Right;
    }
    else if(facesDown(angle))
    {
        return Orientation::Front;
    }
    else
    {
        return Orientation::Left;
    }
}

}

Hero::Hero(const core::math::Point<float>& pos)
    : back_(15.0f, 25.0f, pos, 
            {{"src/res/textures/test_hero_back_head.bmp", 
             "src/res/textures/test_hero_back_cape.bmp",
             "src/res/textures/test_hero_back_torso.bmp"}})
    , right_(15.0f, 25.0f, pos, 
            {{"src/res/textures/test_hero_right_head.bmp", 
             "src/res/textures/test_hero_right_cape.bmp",
             "src/res/textures/test_hero_right_torso.bmp"}})
    , front_(15.0f, 25.0f, pos, 
            {{"src/res/textures/test_hero_front_head.bmp", 
             "src/res/textures/test_hero_front_cape.bmp",
             "src/res/textures/test_hero_front_torso.bmp"}})
    , left_(15.0f, 25.0f, pos, 
            {{"src/res/textures/test_hero_left_head.bmp", 
             "src/res/textures/test_hero_left_cape.bmp",
             "src/res/textures/test_hero_left_torso.bmp"}})
    , position_(0, 0, pos.x, pos.y)
    , orientation_(Orientation::Right)
{

}

void Hero::move(const core::math::vec2<float>& direction)
{
    back_.move(direction);
    right_.move(direction);
    front_.move(direction);
    left_.move(direction);

    orientation_ = calculateOrientation(direction);
}

void Hero::draw() const
{
    switch(orientation_)
    {
        case Orientation::Back:
            back_.draw();
        break;
        case Orientation::Right:
            right_.draw();
        break;
        case Orientation::Front:
            front_.draw();
        break;
        case Orientation::Left:
            left_.draw();
        break;
    }
}
