#include "../include/texture_manager.h"
#include <iostream>

bool TextureManager::loadTexture(const std::string& key, const std::string& filepath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "Erro ao carregar a textura: " << filepath << std::endl;
        return false;
    }
    textures[key] = texture;
    return true;
}

sf::Texture* TextureManager::getTexture(const std::string& key) {
    auto it = textures.find(key);
    if (it != textures.end()) {
        return &it->second;
    }
    return nullptr;
}