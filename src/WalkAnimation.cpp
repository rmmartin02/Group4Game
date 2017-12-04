#include "WalkAnimation.hpp"

#include "VecUtil.hpp"

// Maximum delay between frame switches when moving (slowest)
const float WalkAnimation::MAX_TIME = 1.0f;
// Minimum delay between frame switches when moving (fastest)
const float WalkAnimation::MIN_TIME = 0.1f;
// Speed associated with minimum delay (0 associated with max)
const float WalkAnimation::FAST_VEL = 10.0f;

WalkAnimation::WalkAnimation(sf::IntRect stand, sf::IntRect walk1, sf::IntRect walk2) {
    standing_ = stand;
    walk1_ = walk1;
    walk2_ = walk2;
}

void WalkAnimation::adjustSprite(sf::Sprite& sprite, Entity* entity) {
    
    bool moving = adjustSwitchTime(entity);
    if (walk_timer_.getElapsedTime().asSeconds() > switch_time_) {
        Frame next = Frame::STAND;
        switch (last_frame_) {
            case WALK1:
                switchSprite(sprite, Frame::WALK2);
                break;
            case WALK2:
                switchSprite(sprite, Frame::WALK1);
                break;
            case STAND:
            default:
                // only switch frame if will no longer be standing
                if (moving) {
                    switchSprite(sprite, Frame::WALK1);
                }
                break;
        }
    }
}

void WalkAnimation::switchSprite(sf::Sprite& sprite, WalkAnimation::Frame frame) {
    walk_timer_.restart();
    switch (frame) {
        case WALK1:
            // switch to walk1
            sprite.setTextureRect(walk1_);
            break;
        case WALK2:
            // switch to walk2
            sprite.setTextureRect(walk2_);
            break;
        case STAND:
        default:
            // switch to stand
            sprite.setTextureRect(standing_);
            break;
    }
}

bool WalkAnimation::adjustSwitchTime(Entity* entity) {
    float speed = vecutil::clamp(vecutil::length(entity->getVel()), 0, FAST_VEL) / FAST_VEL;
    if (speed == 0) {
        // if not moving, should switch immediately to standing frame
        switch_time_ = 0;
        return false;
    }
    switch_time_ = (MAX_TIME - MIN_TIME) * speed + MIN_TIME;
    return true;
}
