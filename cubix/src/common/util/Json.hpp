#ifndef JSON_HPP
#define JSON_HPP

#include <stdexcept>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>

class Json {
public:
    static int getInt(const rapidjson::Value& value, const std::string& key);
    static int64_t getInt64(const rapidjson::Value& value, const std::string& key);
    static float getFloat(const rapidjson::Value& value, const std::string& key);
    static std::string getString(const rapidjson::Value& value, const std::string& key);
    static bool getBoolean(const rapidjson::Value& value, const std::string& key);
    static rapidjson::GenericArray<true, rapidjson::Value> getArray(const rapidjson::Value &value,
                                                                    const std::string &key);

    static std::string toString(const rapidjson::Value& value);

protected:
    static bool hasMember(const rapidjson::Value& value, const std::string& key);

    static bool isInt(const rapidjson::Value& value, const std::string& key);
    static bool isInt64(const rapidjson::Value& value, const std::string& key);
    static bool isFloat(const rapidjson::Value& value, const std::string& key);
    static bool isString(const rapidjson::Value& value, const std::string& key);
    static bool isBoolean(const rapidjson::Value& value, const std::string& key);
    static bool isArray(const rapidjson::Value& value, const std::string& key);
};

#endif //JSON_HPP
