//
// Created by Ruoying Hao on 11/12/17.
//

#include "TextureManager.hpp"

TextureManager::TextureManager() {
    
}

bool TextureManager::loadTexture(std::string name, std::string filename){
    if ( textures_.find(name) != textures_.end() ){
        std::cout << "TextureManager.cpp: already loaded texture "
                  << name << " from " << filename << std::endl;
        return true;
    }
    sf::Texture tex;
    if (tex.loadFromFile(filename)) {
        textures_[name] = tex;
        return true;
    }
    return false;
}

void TextureManager::addTexture(std::string name, sf::Texture tex) {
    textures_[name] = tex;
}

sf::Texture& TextureManager::getRef(std::string tex_name) {
    if ( textures_.find(tex_name) == textures_.end() ) {
        std::cout << "TextureManager.cpp: tried to get ref to non-loaded texture "
                  << tex_name << std::endl;
    }
    return textures_.at(tex_name);
}
