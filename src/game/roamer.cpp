#include "roamer.h"

#include <random>

Roamer::Roamer(float x, float y)
    : position_(0, 0, x, y)
    , rect_(Tile::width, Tile::height, {x, y}, core::graphics::red())
{

}

Roamer::Roamer(Roamer&& r)
    : position_(r.position_)
    , rect_(Tile::width, Tile::height, r.rect_.position(), core::graphics::red())
{

}

void Roamer::move(World const & world, float const displacement)
{
    srand( time(NULL) );
    auto randomMove = [displacement] (float & input) {
        int randNum = rand() % 3;
        if (randNum == 0) {
            input += displacement;
        }
        else if (randNum == 1) {
            input -= displacement;
        }
    };

    core::math::vec2<float> direction(0.0f, 0.0f);
    randomMove(direction.x);
    randomMove(direction.y);

    if(world.positionOpen(position() + direction))
    {
        position_.move(direction);
        rect_.moveTo(position_.tilePos());
    }
}

void Roamer::draw() const
{
    rect_.draw();
}

void Roamer::printPosition() const
{
    const auto worldPos = position_.tileMapPos();
    const auto tilePos  = position_.tilePos();
    const auto worldX   = worldPos.x;
    const auto worldY   = worldPos.y;
    const auto tileX    = tilePos.x;
    const auto tileY    = tilePos.y;

    std::cout << "World x: " << worldX << " World y: " << worldY
              << " tile x: " << tileX << " tile y: " << tileY << std::endl;
}

[[nodiscard]]
WorldPosition Roamer::position() const
{
    return position_;
}
