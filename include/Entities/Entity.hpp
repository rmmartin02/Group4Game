#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Global.hpp"

// This class represents all game actors which move in
// continuous 2D space.
class Entity {

public:
  Entity();

  // Update the entity's game state according to time delta
  // and state of other objects in the logic
  virtual void update(float delta, int &logic);

  //Renders entity on window using sprite_
  void render (sf::RenderWindow *window);

  // Return the current position
  sf::Vector2f getPos();

  // Place this entity at a new position
  void setPos(sf::Vector2f pos);

  // Displace this entity relative to its current position
  void move(sf::Vector2f displacement);

  // Get the current velocity
  sf::Vector2f getVel();

  // Set the current velocity
  virtual void setVel(sf::Vector2f vel);

  void setSprite(sf::Sprite sprite);


protected:
  sf::Vector2f pos_;
  sf::Vector2f vel_;
  sf::Sprite sprite_;
};

#endif // ENTITY_HPP

