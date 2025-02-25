#include "JsonNode.h"


/**
 * 
 */
json::JsonNode::JsonNode(): type(JsonType::Object)
{
    // Returns empty JSON node

    data.obj = new Object();
}


/**
 * 
 */
json::JsonNode::~JsonNode()
{
    if ( isValue() ) 
    {
        return;
    }
    
    if ( isList() ) 
    {
        for (JsonNode* node : *data.arr) 
        {
            delete node;
        }

        delete data.arr;

        return;
    }

    if ( isObject() ) 
    {
        // Iterate over object values

        for (std::pair<string, JsonNode*>& node : *data.obj) 
        {
            delete node.second;
        }

        delete data.obj;

        return;
    }
}


/**
 * 
 */
json::JsonNode::JsonNode(int value): type(JsonType::Int)
{
    data.i = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(double value): type(JsonType::Double)
{
    data.d = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(bool value): type(JsonType::Bool)
{
    data.b = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(nullptr_t value): type(JsonType::Null)
{
    data.null = nullptr;
}


/**
 * 
 */
json::JsonNode::JsonNode(const string& value): type(JsonType::String)
{
    *(data.str) = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(const List& value): type(JsonType::List)
{
    *(data.arr) = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(const Object& value): type(JsonType::Object)
{
    *(data.obj) = value;
}


/**
 * 
 */
json::JsonNode::JsonNode(const JsonNode& node): type(node.type)
{
    // TODO: Check type then recursive copy
}


/**
 * 
 */
json::JsonNode& json::JsonNode::operator=(const JsonNode& node)
{
    return *this;
}


// private functions

/**
 * 
 */
bool json::JsonNode::isList() 
{
    return type == JsonType::List;
}


/**
 * 
 */
bool json::JsonNode::isObject()
{
    return type == JsonType::Object;
}


/**
 * 
 */
bool json::JsonNode::isValue() 
{
    return type != JsonType::List && type != JsonType::Object;
}

/**
 * 
 */
bool json::JsonNode::operator==(const JsonNode& node) const
{
    // TODO: Complete this

    if (type != node.type)
        return false;

    // If types match

    
}


// List get operator

/**
 * 
 */
json::JsonNode json::JsonNode::operator[](int i) const
{
    size_t length = data.arr->size();

    // Backwards index
    if (i < 0 && i >= -length) 
    {
        size_t j = length + i;

        return data.arr->at(j);
    }

    return data.arr->at(i);
}


// List set operator

/**
 * 
 */
json::JsonNode& json::JsonNode::operator[](int i)
{
    size_t length = data.arr->size();

    // Backwards index
    if (i < 0 && i >= -length) 
    {
        size_t j = length + i;

        return data.arr->at(j);
    }

    return data.arr->at(i);
}


// Object get operator

/**
 * 
 */
json::JsonNode json::JsonNode::operator[](const string& key) const
{
    // Throws error if key does not exist.
    
    return data.obj->at(key);
}


// Object set operator

/**
 * 
 */
json::JsonNode& json::JsonNode::operator[](const string& key)
{
    // Throws error if key does not exist.
    
    return data.obj->at(key);
}