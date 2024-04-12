#include "Utils.h"


std::string generateRandomString(size_t length) {
    const std::string characters = "0123456789ABCDEF";
    const int charactersCount = characters.length();
    std::string randomString;


    for (int i = 0; i < length; ++i) {
        int randomIndex = std::rand() % charactersCount;
        randomString += characters[randomIndex];
    }

    return randomString;
}