/**
 * @file level_parser.h 
 *
 * @brief This file includes the interfaces used to parse a level file.
 */

#pragma once

#include "emitter.h"
#include "target.h"
#include "field.h"

#include <fstream>
#include <variant>
#include <exception>

/** @brief Encapsulates variables matching the existing game objects types. */
enum ObjectType { 
    /** @brief Emitter type */
    EmitterType, 
    /** @brief Field type */
    FieldType, 
    /** @brief Target type */
    TargetType 
};

/** @class ObjectParser
 *
 * @brief Parses a object, by reading all the coresponding data and 
 * creating an identifier-value container.
 *
 * If something unusual is encountered, exceptions are thrown.
 */
class ObjectParser {
    private:
        /** @brief The stream from which is to be read. */
        std::ifstream& stream;
        /** @brief The type of the object to be read. */
        enum ObjectType type;

        /* @brief The identifier-value map. **/
        std::map<const std::string, std::string> data;

    public:
        /** @brief Constructs the ObjectParser.
         *
         * @param identifiers -> The identifiers denoting the attributes which need to
         *                       be read.
         *
         * @param stream -> The stream from which to be read.
         *
         * @param type -> The ObjectType of the object.
         */
        ObjectParser(const std::vector<std::string>& identifiers,
                     std::ifstream &stream,
                     const enum ObjectType type);

        /** @brief Matches the given value with the given identifier. */
        void addValue(const std::string& identifier,
                      const std::string& value);

        /** @brief Returns if the object was successfully read. **/
        bool ready() const;

        /** @brief Parses the file and returns the identifier-value container. */
        const std::map<const std::string, std::string>& parse();
};

/** @class LevelParser
 *
 * @brief Parses a level file, by using multiple instances of ObjectParser.
 *
 * Each level file must have 'OpenTorium Level File' as the first line, for the file
 * to be seen as valid.
 */
class LevelParser {
    private:
        /** @brief The stream from which to read the level. **/
        std::ifstream levelStream;

    public:
        /** @brief Constructs the LevelParser **/
        LevelParser();

        /** @brief Opens the file and checks for the first line. **/
        void load(const std::string &path);

        /** @brief Parses an object from the file. */
        std::variant<Emitter *, Field *, Target *> 
            getObject();
};
