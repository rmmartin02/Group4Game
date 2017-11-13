//
// Created by Ruoying Hao on 11/12/17.
//

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "../../Group4Game-device/include/Global.hpp"
#include <string>
#include <map>

class TextureManager{
private:
    std::map<std::string, sf::Texture> textures;
public:
    void loadTexture(const std::string& name, const std::string &filename);
    sf::Texture& getRef(const std::string& texture);

    TextureManager(){

    }
};
#endif //TEXTUREMANAGER_HPP
