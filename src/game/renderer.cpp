#include "renderer.h"

Renderer::Renderer()
    : world_()
    , player_(25.0f, 25.0f)
    , roamers_()
{

    roamers_.emplace_back(Roamer(34.0f, 34.0f));
}

void Renderer::render(const vec2f& direction, int displacement)
{
    std::cout << displacement << std::endl;
    world_.drawAt(player_.position());

    if(world_.positionOpen(player_.position() + direction))
    {
        player_.move(direction);
    }

    player_.draw();

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
    // We need to check every object and see if there are collisions,
    // I am going to first do roamers and player, eventually I will
    // add in the tile walls into this I think.
    auto playerPos = player_.position();

    auto playerRightOfRoamer = [playerPos](WorldPosition r) {
        return (playerPos.tilePos().x >= r.tilePos().x);
    };

    auto playerAboveRoamer = [playerPos](WorldPosition r) {
        return (playerPos.tilePos().y >= r.tilePos().y);
    };

    for (auto & roamer: roamers_) {
        auto currRoamerPos = roamer.position();
        if (currRoamerPos.quadrant() == playerPos.quadrant()) {
            auto & playerShape = player_.shape();
            auto & roamShape = roamer.shape();
            // deduce where the roamer is compared
            // to the player
            bool sameX = false;
            bool sameY = false;
            if (playerRightOfRoamer(currRoamerPos)) {
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
            if (playerAboveRoamer(currRoamerPos)) {
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
                std::cout << "HIT!\n";
            }
        }
    }
}
