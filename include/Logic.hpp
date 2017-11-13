#ifndef ENTITY_DATA
#define ENTITY_DATA std::map<std::string, std::unique_ptr<Entity>>
#endif // ENTITY_DATA

#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Global.hpp"
#include <memory>

#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"

#include "Box2D/Box2D.h"


class Logic {
public:
    // Represents the size of a tile, in pixels on the tileset file,
    // and in SFML's drawing units. We may want to separate the two
    // in the future.
    // This is used when loading tiles and building box2d shapes for them.
    static const int TILE_SIZE = 32;
    
    enum Direction {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
    };
    
    Logic();
    void update(float delta);
    
    // Loads a level from a file
    void load(std::string filename);
    
    // Return the numbers of rows and columns in the loaded tile map
    std::pair<int, int> getMapSize();
    
    // Returns reference to 2D vector of tile data
    std::vector<std::vector<int>>& getTiles();
    
    // Add an entity
    void addEntity(std::string id, Entity* e);

    // Returns a reference to the entity matching the id
    Entity& getEntity(std::string id);

    // Returns reference to map containing entities
    ENTITY_DATA& getEntities();
    
    // Returns reference to the player character entity
    Character& getCharacter();
    
    // Return the current value of the countdown timer
    float getTimeLeft();

    // indicates characters needs to move up,down,left,right, or not move
    void registerMoveInput(Direction dir);

private:
    float time_left_;
    
    std::vector<std::vector<int>> tiles_;
    ENTITY_DATA entities_;
    
    std::vector<std::unique_ptr<b2Shape>> wall_shapes_;
    std::vector<b2Transform> wall_transforms_;

    // Clear data structures for tiles and entities
    void clearLevel();
    
    // Load tile data from a csv file
    void loadTiles(std::string filename);
    
    // Load entities from a file
    void loadEntities(std::string filename);
    
    // Build Box2D shapes for walls in the map tiles
    void buildWallShapes();
    
    // Returns true if the given tile value represents a wall
    // (should block line of sight and movement), false otherwise
    bool tileIsWall(int tile);
    
    // Returns true if the entity is colliding with any wall shape
    bool checkWallCollision(Entity&);
};

#endif // LOGIC_HPP

