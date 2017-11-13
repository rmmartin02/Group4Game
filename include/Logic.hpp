#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Global.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

class Logic {
public:
    Logic();
    void update(float delta);
    
    // temp, not sure if this should be implemented here or not
    void load(std::string filename);
    
    // TODO: determine if these should be returning by reference
    std::vector<std::vector<int>> getTiles();
    std::map<std::string, Entity> getEntities();
    Entity getCharacter();
    float getTimeLeft();

    //indicates characters needs to move up,down,left,right
    //0,1,2,3 for now need to make it an enum
    void moveCharacter(int direction);

private:
    std::vector<std::vector<int>> tiles_;
    std::map<std::string, Entity> entities_;
    //Character character_;
    float time_left_;
};

#endif // LOGIC_HPP

