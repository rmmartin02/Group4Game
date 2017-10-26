#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Global.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

class Logic {
public:
    Logic();
    void update(float delta);
    
    // Loads a level from a file
    void load(std::string filename);
    
    // Return the numbers of rows and columns in the loaded tile map
    std::pair<int, int> getMapSize();
    
    // Returns reference to 2D vector of tile data
    std::vector<std::vector<int>>& getTiles();
    
    // Returns reference to map containing entities
    std::map<std::string, Entity>& getEntities();
    
    // Returns copy of the player character entity
    Entity getCharacter();
    
    // Return the current value of the countdown timer
    float getTimeLeft();
    
    //indicates characters needs to move up,down,left,right
    //0,1,2,3 for now need to make it an enum
    void moveCharacter(int direction);

private:
    float time_left_;
    
    std::vector<std::vector<int>> tiles_;
    std::map<std::string, Entity> entities_;
    
    // Clear data structures for tiles and entities
    void clearLevel();
    
    // Load tile data from a csv file
    void loadTiles(std::string filename);
    
    // Load entities from a file
    void loadEntities(std::string filename);
};

#endif // LOGIC_HPP

