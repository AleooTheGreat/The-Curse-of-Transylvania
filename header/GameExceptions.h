#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

class FileLoadException : public GameException {
public:
    explicit FileLoadException(const std::string& message) : GameException(message) {}
};

class TextureLoadException : public GameException {
public:
    explicit TextureLoadException(const std::string& message) : GameException(message) {}
};

class InvalidEnemyTypeException : public GameException {
public:
    explicit InvalidEnemyTypeException(const std::string& message) : GameException(message) {}
};

#endif // GAME_EXCEPTIONS_H
