/**
 * @file exceptions.h
 *
 * This module provides the interface of the exception types used in the program.
 */

#pragma once

#include <string>
#include <stdexcept>

/**
 * @class LevelLoadFail
 *
 * @brief Exception used to show that the level parser failed to load a level.
 */
class LevelLoadFail : public std::runtime_error {
    public:
        LevelLoadFail(const std::string& message);

        const char *what() const noexcept override;
};

/**
 * @class LevelIdentifierFail
 *
 * @brief Exception used to show the level parser encountered an unknown identifier.
 */
class LevelIdentifierFail : public std::runtime_error {
    public:
        LevelIdentifierFail(const std::string& message);

        const char *what() const noexcept;
};

/**
 * @class EOFReached
 *
 * @brief Exception used to show that EOF was reached somewhere.
 */
class EOFReached : public std::runtime_error {
    public:
        EOFReached(const std::string& message);

        const char *what() const noexcept override;
};

/** 
 * @class UnknonType
 *
 * @brief Exception used to show that an undefined type was received by something.
 */
class UnknownType : public std::runtime_error {
    public:
        UnknownType(const std::string& message);

        const char *what() const noexcept override;
};

/**
 * @class ExtractError
 *
 * @brief Exception used to show that something could no be extracted.
 */
class ExtractError : public std::runtime_error {
    public:
        ExtractError(const std::string& message);

        const char *what() const noexcept override;
};
