#ifndef JSON_EXCEPTION_H
#define JSON_EXCEPTION_H

#include <iostream>

class JsonException: std::exception {

};

class JsonTypeMismatchException: JsonException {
        
};

#endif