#include "player.h"
#include "game/world.h"

Player::Player(float x, float y)
    : position_(0, 0, x, y)
    , rect_(Tile::width/2.0f, Tile::height/2.0f, {x, y}, core::graphics::blue())
    , health_(100)
{

}

void Player::move(World const & world, const core::math::vec2<float> direction)
{
    if (!collisionWithWall(world, direction))
    {
        position_.move(direction);
        rect_.moveTo(position_.tilePos());
    }
}

void Player::draw() const
{
    rect_.draw();
}

void Player::printPosition() const
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
WorldPosition Player::position() const
{
    return position_;
}

void Player::updateHealth(int delta)
{
    health_ += delta;
    if (health_ <= 0) {
        health_ = 0;
    }
    // should this return something if health is <= 0?
    if (health_ <= 75) {
        if (health_ <= 50) {
            if (health_ <= 25) {
                rect_.setColor(core::graphics::red());
            }
            else {
                rect_.setColor(core::graphics::orange());
            }
        }
        else {
            rect_.setColor(core::graphics::yellow());
        }
    }
    else {
        rect_.setColor(core::graphics::blue());
    }
}

bool Player::collisionWithWall(World const & world, core::math::vec2<float> direction)
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
