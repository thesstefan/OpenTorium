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

#include "ofXml.h"

/** @class LevelParser
 *
 * @brief Parses a level file, by using multiple instances of ObjectParser.
 *
 * Each level file must have 'OpenTorium Level File' as the first line, for the file
 * to be seen as valid.
 */
class LevelParser {
    private:
        /** @brief The ofXml containing the current game object data. **/
        ofXml currentObjectData;

    public:
        /** @brief Constructs the LevelParser **/
        LevelParser();

        /** @brief Opens the file and checks for the first line. **/
        void load(const std::string &path);

        /** @brief Parses an object from the file. */
        std::variant<Emitter *, Field *, Target *> 
            getObject();
};
