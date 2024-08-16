#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    bool loadTexture(const std::string& key, const std::string& filepath);
    sf::Texture* getTexture(const std::string& key);

private:
    std::map<std::string, sf::Texture> textures;
};

#endif // TEXTURE_MANAGER_H