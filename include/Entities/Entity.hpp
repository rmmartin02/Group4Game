#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Global.hpp"
//#include <memory>
#include "Box2D/Box2D.h"

// This class represents all game actors which move in
// continuous 2D space.
class Entity {

public:
  Entity();
  //Entity(const Entity&);
  //Entity& operator=(const Entity&);
  //~Entity() = default;

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
  void setVel(sf::Vector2f vel);

  void setSprite(sf::Sprite sprite);

  // Attach a Box2D shape to this object
  void attachShape(b2Shape* shape);

  // Return the attached Box2D shape
  b2Shape* getShape();

  // Get a b2Transform representing this object's position
  b2Transform getTransform();

  // Returns true if this entity should be prevented from passing through
  // walls; false if it can ignore walls (and not trigger onWallTouch)
  bool wallCollision();

  // Called when this entity collides with a wall
  virtual void onTouchWall();

protected:
  sf::Vector2f pos_;
  sf::Vector2f vel_;
  sf::Sprite sprite_;

  // Box2D shape object used for collision calculations  
  std::unique_ptr<b2Shape> coll_shape_;
};

#endif // ENTITY_HPP

