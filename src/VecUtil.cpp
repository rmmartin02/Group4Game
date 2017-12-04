#include "VecUtil.hpp"

#include <limits>
#include <cmath>
#include <sstream>

float vecutil::infinity() {
    return std::numeric_limits<float>::infinity();
}

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

float vecutil::crossProd(sf::Vector2f a, sf::Vector2f b){
    return a.x*b.y - a.y*b.x;
}

float vecutil::distance(sf::Vector2f a, sf::Vector2f b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

bool vecutil::nonZero(sf::Vector2f v) {
    return v.x != 0 || v.y != 0;
}

float vecutil::length(sf::Vector2f vec) { return sqrt(dotProd(vec, vec)); }

float vecutil::angle(sf::Vector2f vec) { return atan2(vec.y, vec.x); }

float vecutil::radToDeg(float rad) { return rad * 180.0f / pi(); }

float vecutil::degToRad(float deg){return deg*pi()/180.0f;}

float vecutil::pi() { return 4 * atan(1); }

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

b2Transform vecutil::iform() {
    b2Transform t;
    t.SetIdentity();
    return t;
}

b2Vec2 vecutil::toB2Vec(sf::Vector2f sv) {
    return b2Vec2(sv.x, sv.y);
}

sf::Vector2f vecutil::toSFVec(b2Vec2 bv) {
    return sf::Vector2f(bv.x, bv.y);
}

void vecutil::drawDebugLine(sf::Vector2f p1, sf::Vector2f p2, 
                            sf::Color color, sf::RenderWindow *window) {
    sf::Vertex line[2];
    line[0].position = p1;
    line[1].position = p2;
    line[0].color = color;
    line[1].color = color;
    window->draw(line, 2, sf::Lines);
}
