#ifndef WALKANIMATION_HPP
#define WALKANIMATION_HPP

#include "Global.hpp"
#include "Entities/Entity.hpp"

class WalkAnimation {

public:
    WalkAnimation(sf::IntRect stand, sf::IntRect walk1, sf::IntRect walk2);
    
    // Return the rectangle defining the texture coordinates of the stand-still frame
    sf::IntRect getStandingFrame();
    
    // Set a referenced sprite to the correct animation frame for the entity.
    void adjustSprite(sf::Sprite& sprite, Entity* entity);
    
private:
    // Maximum delay between frame switches when moving (slowest)
    static const float MAX_TIME;
    // Minimum delay between frame switches when moving (fastest)
    static const float MIN_TIME;
    
    // Speed associated with minimum delay (0 associated with max)
    static const float FAST_VEL;
    
    enum Frame {
        STAND = 0,
        WALK1 = 1,
        WALK2 = 2,
    };
    
    // Tracks time elapsed between frame switches
    sf::Clock walk_timer_;
    
    Frame last_frame_ = Frame::STAND;
    
    // Duration (seconds) to wait before switching frames while moving.
    // When moving at higher velocity, this is lower (faster switches)
    float switch_time_;
    
    // Coordinates on the sprite sheet texture
    sf::IntRect standing_;
    sf::IntRect walk1_;
    sf::IntRect walk2_;
    
    void setFrame(sf::Sprite&, Frame);
    
    // Change the time between frame switches based on entity information
    // Return true if the entity is apparently moving
    bool adjustSwitchTime(Entity* entity);
    
};

#endif // WALKANIMATION_HPP
