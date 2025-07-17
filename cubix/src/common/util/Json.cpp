#include "Json.hpp"
std::string Json::toString(const rapidjson::Value& value) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer writer(buffer);
    value.Accept(writer);

    return buffer.GetString();
};

bool Json::hasMember(const rapidjson::Value& value, const std::string& key) {
    if (!value.HasMember(key.c_str()))
        throw std::runtime_error("Json: Key " + key + " does not exist");

    return true;
};

bool Json::isInt(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsInt())
        throw std::runtime_error("Json: Expected an int value");

    return true;
};
int Json::getInt(const rapidjson::Value& value, const std::string& key) {
    Json::isInt(value, key);
    return value[key.c_str()].GetInt();
};

bool Json::isInt64(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsInt64())
        throw std::runtime_error("Json: Expected an int64 value");

    return true;
};
int64_t Json::getInt64(const rapidjson::Value& value, const std::string& key) {
    Json::isInt64(value, key);
    return value[key.c_str()].GetInt64();
};

bool Json::isFloat(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsFloat())
        throw std::runtime_error("Json: Expected a float value");

    return true;
};
float Json::getFloat(const rapidjson::Value& value, const std::string& key) {
    Json::isFloat(value, key);
    return value[key.c_str()].GetFloat();
};

bool Json::isString(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsString())
        throw std::runtime_error("Json: Expected a string value");

    return true;
};
std::string Json::getString(const rapidjson::Value& value, const std::string& key) {
    Json::isString(value, key);
    return value[key.c_str()].GetString();
};

bool Json::isBoolean(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsBool())
        throw std::runtime_error("Json: Expected a boolean value");

    return true;
};
bool Json::getBoolean(const rapidjson::Value& value, const std::string& key) {
    Json::isBoolean(value, key);
    return value[key.c_str()].GetBool();
};


bool Json::isArray(const rapidjson::Value& value, const std::string& key) {
    Json::hasMember(value, key);
    if (!value[key.c_str()].IsArray())
        throw std::runtime_error("Json: Expected an array value");

    return true;
};

rapidjson::GenericArray<true, rapidjson::Value> Json::getArray(
    const rapidjson::Value &value,
    const std::string &key
) {
    Json::isArray(value, key);
    return value[key.c_str()].GetArray();
};