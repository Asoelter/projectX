#include "renderer.h"

Renderer::Renderer()
    : world_()
    , player_(25.0f, 25.0f)
    , hero_({25.0f, 25.0f})
    , roamers_()
{
    roamers_.emplace_back(Roamer(34.0f, 34.0f));
}

void Renderer::render(const vec2f& direction, float displacement)
{
    world_.drawAt(player_.position());

    player_.move(world_, direction);
    hero_.moveTo(player_.position().tilePos(), direction);

    player_.draw();
    hero_.draw();

    for(auto& roamer : roamers_)
    {
        roamer.move(world_, displacement);

        if(world_.contains(roamer.position()))
        {
            roamer.draw();
        }
    }

    // should be the last thing called I think
    checkForCollisions();
}

void Renderer::checkForCollisions()
{
    checkForCollisionsWithRoamers();
}

void Renderer::checkForCollisionsWithRoamers()
{
    auto playerPos = player_.position();

    for (auto & roamer: roamers_) {
        auto currRoamerPos = roamer.position();
        if (currRoamerPos.quadrant() == playerPos.quadrant()) {
            auto & playerShape = player_.shape();
            auto & roamShape = roamer.shape();
            // deduce where the roamer is compared
            // to the player
            bool sameX = false;
            bool sameY = false;
            if (playerRightOfObject(currRoamerPos)) {
                // If I am right of the roamer, check left side
                if ((playerPos.tilePos().x - (playerShape.width() / 2.0f)) < (currRoamerPos.tilePos().x + (roamShape.width() / 2.0f))) {
                    sameX = true;
                }
            }
            else {
                if ((playerPos.tilePos().x + (playerShape.width() / 2.0f)) > (currRoamerPos.tilePos().x - (roamShape.width() / 2.0f))) {
                    sameX = true;
                }
            }
            if (playerAboveObject(currRoamerPos)) {
                // If I am above of the roamer, check bellow
                if ((playerPos.tilePos().y - (playerShape.height() / 2.0f)) < (currRoamerPos.tilePos().y + (roamShape.height() / 2.0f))) {
                    sameY = true;
                }
            }
            else {
                // If I am below the roamer, check above
                if ((playerPos.tilePos().y + (playerShape.height() / 2.0f)) > (currRoamerPos.tilePos().y - (roamShape.height() / 2.0f))) {
                    sameY = true;
                }
            }

            if (sameX && sameY) {
                player_.updateHealth(-1);
            }
        }
    }
}

bool Renderer::playerRightOfObject(WorldPosition r)
{
    return (player_.position().tilePos().x >= r.tilePos().x);
}

bool Renderer::playerAboveObject(WorldPosition r)
{
    return (player_.position().tilePos().y >= r.tilePos().x);
}
