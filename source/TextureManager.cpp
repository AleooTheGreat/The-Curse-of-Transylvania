#include "../header/TextureManager.h"
#include <stdexcept>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

bool TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        textures[name] = texture;
        return true;
    }
    return false;
}

const sf::Texture& TextureManager::getTexture(const std::string& name) const {
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}
