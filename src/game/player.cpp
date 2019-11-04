#include "player.h"

Player::Player(float x, float y)
    : position_(0, 0, x, y)
    , rect_(Tile::width, Tile::height, {x, y}, core::graphics::blue())
{

}

void Player::move(const core::math::vec2<float> direction)
{
    position_.move(direction);
    rect_.moveTo(position_.tilePos());
}

void Player::draw() const
{
    rect_.draw();
}

void Player::printPosition() const
{
    const auto worldPos = position_.tileMapPos();
    const auto tilePos = position_.tilePos();
    const auto worldX = worldPos.x;
    const auto worldY = worldPos.y;
    const auto tileX = tilePos.x;
    const auto tileY = tilePos.y;
    std::cout << "World x: " << worldX << " World y: " << worldY 
              << " tile x: " << tileX << " tile y: " << tileY << std::endl;
}

[[nodiscard]] 
WorldPosition Player::position() const
{
    return position_;
}
