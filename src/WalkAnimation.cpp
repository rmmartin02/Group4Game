#include "WalkAnimation.hpp"

#include "VecUtil.hpp"

// Maximum delay between frame switches when moving (slowest)
const float WalkAnimation::MAX_TIME = 0.2f;
// Minimum delay between frame switches when moving (fastest)
const float WalkAnimation::MIN_TIME = 0.1f;
// Speed associated with minimum delay (0 associated with max)
// Maybe instead the character's max speed should be used?
const float WalkAnimation::FAST_VEL = 10.0f;

WalkAnimation::WalkAnimation(sf::IntRect stand, sf::IntRect walk1, sf::IntRect walk2) {
    standing_ = stand;
    walk1_ = walk1;
    walk2_ = walk2;
}

sf::IntRect WalkAnimation::getStandingFrame() {
    return standing_;
}

void WalkAnimation::adjustSprite(sf::Sprite& sprite, Entity* entity) {
    
    bool moving = adjustSwitchTime(entity);
    if (walk_timer_.getElapsedTime().asSeconds() < switch_time_) {
        return;
    }
    if (!moving) {
        setFrame(sprite, Frame::STAND);
        return;
    }
    Frame next = Frame::STAND;
    switch (last_frame_) {
        case WALK1:
            setFrame(sprite, Frame::WALK2);
            break;
        case WALK2:
            setFrame(sprite, Frame::WALK1);
            break;
        case STAND:
        default:
            setFrame(sprite, Frame::WALK1);
            break;
    }
}

void WalkAnimation::setFrame(sf::Sprite& sprite, Frame frame) {
    walk_timer_.restart();
    last_frame_ = frame;
    switch (frame) {
        case WALK1:
            sprite.setTextureRect(walk1_);
            break;
        case WALK2:
            sprite.setTextureRect(walk2_);
            break;
        case STAND:
        default:
            sprite.setTextureRect(standing_);
            break;
    }
}

bool WalkAnimation::adjustSwitchTime(Entity* entity) {
    float speed = vecutil::clamp(vecutil::length(entity->getVel()), 0, FAST_VEL) / FAST_VEL;
    if (speed == 0) {
        // if not moving, should switch immediately to standing frame
        switch_time_ = MIN_TIME;
        return false;
    }
    switch_time_ = (MAX_TIME - MIN_TIME) * (1-speed) + MIN_TIME;
    return true;
}
