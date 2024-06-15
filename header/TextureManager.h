#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance();
    bool loadTexture(const std::string& name, const std::string& filename);
    const sf::Texture& getTexture(const std::string& name) const;

private:
    TextureManager() = default;
    std::unordered_map<std::string, sf::Texture> textures;
};

#endif // TEXTUREMANAGER_H
