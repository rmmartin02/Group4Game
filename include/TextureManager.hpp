//
// Created by Ruoying Hao on 11/12/17.
//

#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Global.hpp"

class TextureManager {

public:
    TextureManager();
    
    // Loads a texture and assigns it to a name
    // Returns true if succeeded or already loaded, false if failed
    bool loadTexture(std::string name, std::string filename);
    
    // Return a reference to a named texture
    sf::Texture& getRef(std::string tex_name);
    
private:
    std::map<std::string, sf::Texture> textures_;

};
#endif // TEXTUREMANAGER_HPP
