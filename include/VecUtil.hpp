// This file contains declarations for helper utility functions, related
// to doing math / vector operations.

#ifndef VECUTIL_H
#define VECUTIL_H

#include <string>

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

namespace vecutil {

// Returns a float representing infinity
float infinity();
    
// Enforces lower and upper bounds on val.
float clamp(float val, float cmin, float cmax);

// Enforces bounds (defined by vectors min and max)
// on elements of vector val.
sf::Vector2f clampVec2(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);

// Returns true if any vector component is not zero; false otherwise.
// If this returns true, value returned by length must be nonzero, and
// vecutil::angle(v) must not fail.
bool nonZero(sf::Vector2f v);

// Returns a dot product of two vectors.
float dotProd(sf::Vector2f, sf::Vector2f);

// Returns the magnitude of the vector.
float length(sf::Vector2f);

// Returns the polar angle of this vector's direction, in radians.
// Can return nan or other error-y values for vectors whose angle is uncertain,
// such as zero.
float angle(sf::Vector2f);

// Converts angle in radians to angle in degrees.
float radToDeg(float rad);

// Returns an approximate value for pi.
float pi();

// Returns a normalized (1-length) vector in the direction of the provided,
// or a zero-vector if provided with a zero-vector.
sf::Vector2f normalize(sf::Vector2f);

// Returns a vector equivalent to a point at the given angle and distance.
sf::Vector2f fromPolar(float length, float angle);

// Returns string describing Box2D vector contents
std::string vecInfo(b2Vec2);

// Returns string describing SFML vector contents
std::string vecInfo(sf::Vector2f);

// Returns string describing Box2D transform contents
std::string transformInfo(b2Transform);

// Returns the identity transform
b2Transform iform();

// Converts SFML vector to Box2D vector
b2Vec2 toB2Vec(sf::Vector2f);

// Converts Box2D vector to SFML vector
sf::Vector2f toSFVec(b2Vec2);

// Draws a line in the window between the two points
void drawDebugLine(sf::Vector2f p1, sf::Vector2f p2, sf::Color color, sf::RenderWindow *window);

}

#endif // VECUTIL_H
