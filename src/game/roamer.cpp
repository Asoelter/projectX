#include "roamer.h"

#include <random>

Roamer::Roamer(float x, float y)
    : position_(0, 0, x, y)
    , rect_(Tile::width / 2.0, Tile::height / 2.0, {x, y}, core::graphics::black())
{

}

Roamer::Roamer(Roamer&& r)
    : position_(r.position_)
    , rect_(Tile::width / 2.0, Tile::height / 2.0, r.rect_.position(), core::graphics::black())
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

    if (!collisionWithWall(world, direction))
    {
        position_.move(direction);
        rect_.moveTo(position_.tilePos());
    }
}

bool Roamer::collisionWithWall(World const & world, core::math::vec2<float> direction)
{
    auto newPosition = position() + direction;
    auto const & quadrantMap = world.quadrant(newPosition);

    int rowIndex = 0;
    for (auto const & row : quadrantMap.map()) {
        for (auto const & tile : row) {
            if (tile->state() == TileState::UNOCCUPIED) { continue; }
            bool sameX = false;
            bool sameY = false;
            auto const & tilePos = tile->position();
            if (newPosition.tilePos().x  >= tilePos.x)
            {
                if ((newPosition.tilePos().x - (shape().width()  / 2.0f)) < (tilePos.x + (tile->shape().width() / 2.0f)))
                {
                    sameX = true;
                }
            }
            else
            {
                if ((newPosition.tilePos().x + (shape().width()  / 2.0f)) > (tilePos.x - (tile->shape().width() / 2.0f)))
                {
                    sameX = true;
                }

            }
            if (newPosition.tilePos().y  >= tilePos.y)
            {
                if ((newPosition.tilePos().y - (shape().height()  / 2.0f)) < (tilePos.y + (tile->shape().height() / 2.0f)))
                {
                    sameY = true;
                }
            }
            else
            {
                if ((newPosition.tilePos().y + (shape().height()  / 2.0f)) > (tilePos.y - (tile->shape().height() / 2.0f)))
                {
                    sameY = true;
                }
            }

            if (sameX && sameY) {
                return true;
            }
        }
        ++rowIndex;
    }

    return false;
}

void Roamer::draw() const
{
    rect_.draw();
}

void Roamer::printPosition() const
{
    const auto worldPos = position_.quadrant();
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
