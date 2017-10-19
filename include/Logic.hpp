#ifndef ENTITY_MAP
#define ENTITY_MAP std::map<std::string, std::unique_ptr<Entity>>
#endif

#ifndef TILE_GRID
#define TILE_GRID std::vector<std::vector<int>>
#endif

#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Entity.hpp"

class Logic {
public:
    Logic();
    void update(float delta);
    
    // temp, not sure if this should be implemented here or not
    void load(std::string filename);

    TILE_GRID getTiles();
    ENTITY_MAP getEntities();
    float getTimeLeft();

private:
    TILE_GRID tiles_;
    ENTITY_MAP entities_;
    float time_left_;
}

#endif // LOGIC_HPP

