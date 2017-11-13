#include "VecUtil.hpp"

#include <cmath>
#include <sstream>

float vecutil::clamp(float val, float cmin, float cmax) {
    return std::max(cmin, std::min(cmax, val));
}

sf::Vector2f vecutil::clampVec2(sf::Vector2f val, sf::Vector2f min,
                                sf::Vector2f max) {
    return sf::Vector2f(clamp(val.x, min.x, max.x), clamp(val.y, min.y, max.y));
}

float vecutil::dotProd(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

float vecutil::length(sf::Vector2f vec) { return sqrt(dotProd(vec, vec)); }

float vecutil::angle(sf::Vector2f vec) { return atan2(vec.y, vec.x); }

sf::Vector2f vecutil::normalize(sf::Vector2f vec) {
    if (vec.x == 0 && vec.y == 0) {
        return sf::Vector2f(0, 0);
    }
    return vec / vecutil::length(vec);
}

sf::Vector2f vecutil::fromPolar(float length, float angle) {
    return sf::Vector2f(length * cos(angle), length * sin(angle));
}

std::string vecutil::vecInfo(b2Vec2 bv) {
    std::stringstream ss;
    ss << "<" << bv.x << "," << bv.y << ">";
    return ss.str();
}

std::string vecutil::vecInfo(sf::Vector2f sv) {
    std::stringstream ss;
    ss << "<" << sv.x << "," << sv.y << ">";
    return ss.str();
}

std::string vecutil::transformInfo(b2Transform bt) {
    std::stringstream ss;
    ss << "[pos:<" << bt.p.x << "," << bt.p.y << "> rad:" << bt.q.GetAngle() << "]";
    return ss.str();
}
