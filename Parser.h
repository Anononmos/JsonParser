#ifndef PARSER_H
#define PARSER_H

#include "utils.h"
#include "JsonNode.h"

namespace json {

    // Find brace pairs
    // Use a recursive algorithm

    class JsonParser {
        private:
            const string raw_json;

            /**
             * Skips whitespace characters until reaching a non-whitespace character.
             * If called on a non-whitespace character, returns false.
             */
            bool skipWhitespace(int& index);

            /**
             * Find corresponding pair with brace.
             */
            int findBracePairs(int start);

            int parseString(int start);

            int parseNumber(int start);

        public: 
            /**
             * Initialize parser with JSON string.
             */
            JsonParser(const string src);

            /**
             * Converts JSON string to JsonNode instance
             */
            // json::JsonNode toInstance();

            /**
             * 
             */
            string toString();
    };  
    
    /**
     * Loads JSON string from file.
     */
    const JsonParser load(const string& filename);
}

#endif
