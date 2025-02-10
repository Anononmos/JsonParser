#include "Parser.h"

json::JsonParser::JsonParser(const string& src): raw_json(src) {}



/**
 * 
 */
int json::JsonParser::findBracePairs(int start)
{
    std::map<char, char> open_char{
        {']', '['}, 
        {'}', '{'}
    };
    std::stack<char> parity{};

    do
    {
        char c = raw_json[start];

        if (c == '{' || c == '[')
        {
            parity.push(c);
        }

        // Remove brackets pair if closing character is found
        if (parity.top() == open_char[c])
        {
            parity.pop();
        }
        
        ++start;
    } 
    while ( !parity.empty() && start < raw_json.length() );  
}

/**
 * 
 */
int json::JsonParser::skipWhitespace(int index)
{
    while ( std::isspace(raw_json[index]) && index < raw_json.length() )
    {
        ++index;
    }

    return index;
}