#ifndef ENTITY_DATA
#define ENTITY_DATA std::map<std::string, std::unique_ptr<Entity>>
#endif // ENTITY_DATA

#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Global.hpp"
#include <memory>
#include <cmath>
#include <deque>

#include "Entities/Entity.hpp"
#include "Entities/Character.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Laser.hpp"

#include "Box2D/Box2D.h"
struct Node{
    int row;
    int col;
    int g;
    int h;
    int f;
    Node* parent;
};

class Logic {
public:
    // Possible gameplay states. 
    enum PlayState {
        PLAYING     = 0, // normal gameplay
        MINIGAME    = 1, // mini-game in progress; paused here, should be switched away from GameScreen
        LOST        = 2, // should switch screens to reflect failure
        WON         = 3, // should switch screens to reflect success (and load the next level?)
    };

    // Represents the size of a tile, in pixels on the tileset file,
    // and in SFML's drawing units. We may want to separate the two
    // in the future.
    // This is used when loading tiles and building box2d shapes for them.
    static const int TILE_SIZE = 32;

    Logic(float time_limit);
    void update(float delta);
    
    // Return the current state of play. See PlayState enum above.
    PlayState getPlayState();
    
    // Loads a level from a file
    void load(std::string mapfilename,std::string enemyfilename);
    
    // Return the numbers of rows and columns in the loaded tile map
    std::pair<int, int> getMapSize();
    
    // Returns reference to 2D vector of tile data
    std::vector<std::vector<int>>& getTiles();
    
    // Returns the ID number of a tile at a row,col coordinate in the map
    // If coordinate is not valid / out of bounds, returns -1
    int getTileAt(std::pair<int,int>);
    
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

    // indicates character needs to move in the inputted direction
    void registerMoveInput(sf::Vector2f direction);
    
    // retreives debug information to be rendered in GameScreen
    // returns true if valid info was retreived
    bool getDebugInfo(sf::Vector2f& p1, sf::Vector2f& p2);
    
    // Returns false if no walls come between the points `src` and `target`
    // Returns true if there is an obstruction: sets `hit` to the point
    // at which an obstruction is encountered
    bool sightObstructed(sf::Vector2f src, sf::Vector2f target, sf::Vector2f& hit);

private:
    float time_left_;
    PlayState state_ = PlayState::PLAYING;
    
    std::vector<std::vector<int>> tiles_;

    ENTITY_DATA entities_;
    
    std::vector<std::unique_ptr<b2Shape>> wall_shapes_;

    // Clear data structures for tiles and entities
    void clearLevel();
    
    // Load tile data from a csv file
    void loadTiles(std::string filename);
    
    // Load entities from a file
    void loadEntities(std::string filename);
    
    // Build Box2D shapes for walls in the map tiles
    void buildWallShapes();
    
    // Build Box2D wall shapes out of 1-wide rectangles
    // Returns number of shapes created
    int buildAxisWalls(bool vertical);
    
    // Return the grid coordinates of a world position
    std::pair<int,int> getGridCoords(sf::Vector2f position);
    
    // Checks if grid coordinates lie within space covered by our tile data
    bool coordsInBounds(std::pair<int,int>);
    
    // Returns true if the given tile value represents a wall
    // (should block line of sight and movement), false otherwise
    bool tileIsWall(int tile);
    
    // Returns true if the given tile value represents a level exit
    // (level is beaten when the character reaches the tile)
    bool tileIsExit(int tile);
    
    // Checks if an entity is colliding with any wall shape and deals with effects
    bool handleWallCollisions(Entity& e); 
    
    // Handle an entity's collision with a wall shape
    void onWallCollision(Entity& e, b2Vec2 point, b2Vec2 normal);
    
    // Handle an enemy landing an attack on the player (enter mini-game?)
    void onEnemyAttack(Enemy*);
    
    // Handle time running out (lose!)
    void onTimeExpired();
    
    // Handle the level being beaten (win!)
    void onExitReached();

    //pathfinding var and methods
    //pathFinder:
    //param: startPos: starting position of the entity or, current position of entity(when chasing)
    //param: destPos: destination of entity, or character position(when chasing)
    //return: a DEQUE of vector2f(location) from the start to the destination position,
    //          the Vector2f location is the CENTER of the tile
    std::deque<sf::Vector2f> pathFinder(sf::Vector2f startPos, sf::Vector2f destPos);
    std::vector<std::deque<sf::Vector2f>> multiPathFinder(std::vector<sf::Vector2f> positions);
    std::vector<std::vector<Node>> tileNodeMap_;

    std::set< std::pair<int,int>> closedSet_;
    std::set< std::pair<int,int>> openSet_;
    std::set<std::pair<int,int>> surroundSet_;
    int computeG(std::pair<int,int> curPair);
    int computeH(std::pair<int,int> curPair,std::pair<int,int> goalPair);
    std::deque<std::pair<int,int>> path_; //deque of tile x and y, for your reference
    std::deque<sf::Vector2f> enemyPath_;
};

#endif // LOGIC_HPP

