// This file contains declarations for helper utility functions, related
// to doing math / vector operations.

#ifndef VECUTIL_H
#define VECUTIL_H

#include <SFML/Graphics.hpp>

namespace vecutil {

// Enforces lower and upper bounds on val.
float clamp(float val, float cmin, float cmax);

// Enforces bounds (defined by vectors min and max)
// on elements of vector val.
sf::Vector2f clampVec2(sf::Vector2f val, sf::Vector2f min, sf::Vector2f max);

// Returns a dot product of two vectors.
float dotProd(sf::Vector2f, sf::Vector2f);

// Returns the magnitude of the vector.
float length(sf::Vector2f);

// Returns the polar angle of this vector's direction.
// Can return nan or other error-y values for vectors whose angle is uncertain,
// such as zero.
float angle(sf::Vector2f);

// Returns a normalized (1-length) vector in the direction of the provided,
// or a zero-vector if provided with a zero-vector.
sf::Vector2f normalize(sf::Vector2f);

// Returns a vector equivalent to a point at the given angle and distance.
sf::Vector2f fromPolar(float length, float angle);

}

#endif // VECUTIL_H
