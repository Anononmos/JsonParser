#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include <iostream>

namespace json {

    class JsonException: std::exception {

    };

    class JsonInvalidSyntaxException: JsonException {

    };

    class JsonTypeMismatchException: JsonException {
            
    };
};

#endif