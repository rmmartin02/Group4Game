#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Entities/Entity.hpp"

class Logic {
public:
    Logic();
    void update(float delta);
    
    // temp, not sure if this should be implemented here or not
    void load(std::string filename);
    
    // TODO: determine if these should be returning by reference
    std::vector<std::vector<int>> getTiles();
    std::map<std::string, Entity> getEntities();
    float getTimeLeft();

private:
    std::vector<std::vector<int>> tiles_;
    std::map<std::string, Entity> entities_;
    float time_left_;
};

#endif // LOGIC_HPP

