#include "exceptions.h"

LevelLoadFail::LevelLoadFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelLoadFail::what() const noexcept {
    return std::runtime_error::what();
}

LevelIdentifierFail::LevelIdentifierFail(const std::string& message) :
    std::runtime_error(message) {}

const char *LevelIdentifierFail::what() const noexcept {
    return std::runtime_error::what();
}

EOFReached::EOFReached(const std::string& message) :
    std::runtime_error(message) {}

const char *EOFReached::what() const noexcept {
    return std::runtime_error::what();
}

UnknownType::UnknownType(const std::string& message) :
    std::runtime_error(message) {}

const char *UnknownType::what() const noexcept {
    return std::runtime_error::what();
}

ExtractError::ExtractError(const std::string& message) :
    std::runtime_error(message) {}

const char *ExtractError::what() const noexcept {
    return std::runtime_error::what();
}
