#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>
#include <map>

using std::string;

namespace json {

    // Find brace pairs
    // Use a recursive algorithm

    class JsonParser {
        private:
            const string& raw_json;
            
        public:
            JsonParser(const string& src);

            int findBracePairs(int start);
            int skipWhitespace(int index);
            
    };
}

#endif
