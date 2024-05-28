//
// Created by aleoo on 5/29/24.
//

#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class FileLoadException : public GameException {
public:
    explicit FileLoadException(const std::string& msg) : GameException("File Load Error: " + msg) {}
};

class TextureLoadException : public GameException {
public:
    explicit TextureLoadException(const std::string& msg) : GameException("Texture Load Error: " + msg) {}
};

class InvalidStateException : public GameException {
public:
    explicit InvalidStateException(const std::string& msg) : GameException("Invalid State Error: " + msg) {}
};

#endif // GAME_EXCEPTIONS_H

