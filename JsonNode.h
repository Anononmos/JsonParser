#ifndef JSON_H
#define JSON_H

#include "utils.h"

namespace json {

    typedef std::vector<JsonNode*> List;
    typedef std::unordered_map<string, JsonNode*> Object;

    enum class JsonType {
        Int, Double, Bool, Null, String, List, Object
    };

    /**
     * 
     */
    class JsonNode {
        private:
            JsonType type;

            union JsonValue {
                int i;
                double d;
                bool b;

                nullptr_t null;
                string* str;
                List* arr;
                Object* obj;
            } data;

        public:
            // Empty JSON object
            JsonNode();

            // Destructor
            ~JsonNode();

            // Type constructors
            JsonNode(int value);

            JsonNode(double value);

            JsonNode(bool value);

            JsonNode(nullptr_t value);

            JsonNode(const string& value);

            JsonNode(const List& value);

            JsonNode(const Object& value);

            // Copy constructor
            JsonNode(const JsonNode& node);

            // Copy assignment operator
            JsonNode& operator=(const JsonNode& node);

            bool isList();

            bool isObject();

            bool isValue();

            // Equality operator
            bool operator==(const JsonNode& node) const;

            // Inequality operator
            bool operator!=(const JsonNode& node) const;

            // List get operator
            JsonNode operator[](int i) const;

            // List set operator
            JsonNode& operator[](int i);

            // Object get operator
            JsonNode operator[](const string& key) const;

            // Object set operator
            JsonNode& operator[](const string& key);
    };
}

#endif