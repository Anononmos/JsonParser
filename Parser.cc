#include "Parser.h"


/**
 * 
 */
const json::JsonParser json::load(const string& filename)
{
    if (filename.length() < 5)
    {
        throw std::invalid_argument("Input file is not a JSON file.");
    }

    size_t pos = filename.length() - 5;

    if ( filename.find(".json", pos) == string::npos )
    {
        throw std::invalid_argument("Input file is not a JSON file.");
    }
    
    std::ifstream file(filename);
    if ( !file.is_open() )
    {   
        file.close();

        throw std::runtime_error("Input file cannot open.");
    }

    const string jsonString( 
        ( std::istreambuf_iterator<char>(file) ), 
        std::istreambuf_iterator<char>()
    );

    file.close();

    return JsonParser(jsonString);
}


/**
 * 
 */
json::JsonParser::JsonParser(const string src): raw_json(src) {}

/**
 * 
 */
string json::JsonParser::toString()
{
    return raw_json;
}


/**
 * 
 */
int json::JsonParser::findBracePairs(int start)
{
    bool insideQuotes = false;
    bool seenBackslash = false;

    int location = start;   // For debugging, the position when brackets
    std::stack<char> parity{};

    auto open_char = [](char c)
    {
        switch (c)
        {
        case '}':
            return '{';
        
        case ']':
            return '[';
    
        default:
            return '\0';
        }
    };

    do 
    {   
        char c = raw_json[start];

        // Toggle quotes flag if quote is encountered unless preceeded by a backslash

        if (c == '\\')
        {
            seenBackslash = !seenBackslash;
        }

        if (c == '"' && !seenBackslash)
        {
            insideQuotes = !insideQuotes;
        }

        if ( !skipWhitespace(start)  )
        {
            ++start;
        }

        // Ignore brackets inside quotes.

        if (insideQuotes)
        {
            continue;
        }

        if (c == '{' || c == '[')
        {
            parity.push(c);
            continue;
        }
        
        if ( parity.top() == open_char(c) )
        {
            parity.pop();
            continue;
        }

        // Detect extra closing character

        if ( parity.top() != open_char(c) )
        {
            throw 1;    // Temporary throw value
        }

    } while ( !parity.empty() && start < raw_json.length() );

    // Detect extra opening character
    if ( !parity.empty() )
    {
        throw 2;
    }

    // Detect unclosed Quote
    if (insideQuotes)
    {
        throw 3;
    }

    if (seenBackslash)
    {
        throw 4;
    }

    return start;
}


/**
 * 
 */
bool json::JsonParser::skipWhitespace(int& index)
{
    bool hasIncremented = false;
    
    while ( std::isspace(raw_json[index]) && index < raw_json.length() )
    {
        ++index;
        hasIncremented = true;
    }

    return hasIncremented;
}


/**
 * 
 */
int json::JsonParser::parseString(int start)
{
    bool seenBacklash = false;
    bool insideQuotes = false;

    do
    {
        char c = raw_json[start];

        if (c == '"')
        {
            insideQuotes = !insideQuotes;
        }

        ++start;

    } while (insideQuotes && start < raw_json.length());

    return start;
}


/**
 * 
 */
int json::JsonParser::parseNumber(int start)
{
    bool isDecimal = false;
    char c = raw_json[start];

    // Fail condition
    // start index exceeds json length
    // If the character is not a digit 
    // If the decimal point appears more than once

    while ( ( isdigit(c) || c == '.' ) && (c != '.' || !isDecimal) && start < raw_json.length() )
    {
        ++start;
    }

    return start;
}