#include "LevelManager.hpp"

LevelManager::LevelManager() {
    current_level_ = 0;
    total_levels_ = 0;
}

void LevelManager::addLevel(std::string name, std::string tile_file, std::string entity_file) {
    level_names_[total_levels_]     = name;
    tile_files_[total_levels_]      = tile_file;
    entity_files_[total_levels_]    = entity_file;
    total_levels_++;
}

int LevelManager::getCurrentLevelNumber() {
    return current_level_;
}

std::string LevelManager::getCurrentLevelName() {
    return level_names_[current_level_];
}

std::string LevelManager::getCurrentTileFilename() {
    return tile_files_[current_level_];
}

std::string LevelManager::getCurrentEntityFilename() {
    return entity_files_[current_level_];
}

bool LevelManager::nextLevel() {
    if (current_level_ >= total_levels_-1) {
        return false;
    }
    current_level_++;
    return true;
}

bool LevelManager::setLevel(int level) {
    if (level < 0 || level >= total_levels_) {
        return false;
    }
    current_level_ = level;
    return true;
}
