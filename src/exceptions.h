#pragma once

#include <string>
#include <stdexcept>

class LevelLoadFail : public std::runtime_error {
    public:
        LevelLoadFail(const std::string& message);

        const char *what() const noexcept override;
};

class LevelIdentifierFail : public std::runtime_error {
    public:
        LevelIdentifierFail(const std::string& message);

        const char *what() const noexcept;
};

class EOFReached : public std::runtime_error {
    public:
        EOFReached(const std::string& message);

        const char *what() const noexcept override;
};

class UnknownType : public std::runtime_error {
    public:
        UnknownType(const std::string& message);

        const char *what() const noexcept override;
};

class ExtractError : public std::runtime_error {
    public:
        ExtractError(const std::string& message);

        const char *what() const noexcept override;
};
