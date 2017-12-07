#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "Global.hpp"

class LevelManager {

public:
    LevelManager();
    
    // Register a level and its associated files
    void addLevel(std::string name, std::string tile_file, std::string entity_file);
    
    // Return the number of the current level
    int getCurrentLevelNumber();
    // Return the name of the current level
    std::string getCurrentLevelName();
    // Return the name of the tile file for the current level
    std::string getCurrentTileFilename();
    // Return the name of the enemy file for the current level
    std::string getCurrentEntityFilename();

    // Increments current level by 1. If there are no more levels, return false.
    // If there are still levels to play, return true.
    bool nextLevel();
    
    // Sets current level to a given number. Returns true if successful, false if no such level exists.
    bool setLevel(int level);

private:
    int current_level_;
    int total_levels_;
    
    std::map<int, std::string> level_names_;
    std::map<int, std::string> tile_files_;
    std::map<int, std::string> entity_files_;
    
};

#endif // LEVELMANAGER_HPP
