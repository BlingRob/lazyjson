#include <lazyjson/json.hpp>

#include <gtest/gtest.h>

#include <string>

namespace json = lazyjson;

// Присваивание булевого значения
TEST(JsonUsage, BoolValue)
{
    const bool test = true;
    json::json json;
    json["test"] = test;

    ASSERT_TRUE(json["test"].is_type<bool>());
    ASSERT_FALSE(json["test"].is_type<std::string>());

    const bool res = json["test"].get<bool>();
    ASSERT_EQ(res, test);
}

// Присваивание целочисленного значения
TEST(JsonUsage, IntValue)
{
    const int test = 12345;
    json::json json;
    json["test"] = test;

    ASSERT_TRUE(json["test"].is_type<int>());
    ASSERT_FALSE(json["test"].is_type<float>());

    const int res = json["test"].get<int>();
    ASSERT_EQ(res, test);
}

// Присваивание вещественного значения
TEST(JsonUsage, FloatValue)
{
    const float test = 12345.54321;
    json::json json;
    json["test"] = test;

    ASSERT_TRUE(json["test"].is_type<float>());
    ASSERT_FALSE(json["test"].is_type<int>());

    const float res = json["test"].get<float>();
    ASSERT_EQ(res, test);
}

// Присваивание строкового значения
TEST(JsonUsage, StringValue)
{
    const std::string test = "Some random string value";
    json::json json;
    json["test"] = test;

    ASSERT_TRUE(json["test"].is_type<std::string>());
    ASSERT_FALSE(json["test"].is_type<bool>());

    const std::string res = json["test"].get<std::string>();
    ASSERT_EQ(res, test);
}

// Использование массива
TEST(JsonUsage, Array)
{
    json::json json;
    auto& array = (json["array"] = json::array{}).get<json::array>();

    json::element num{1};
    json::element text{std::string{"some very long and useless text"}};
    json::element value{true};

    array.push_back(num);
    array.push_back(text);
    array.push_back(value);
    text.get<std::string>();

    // TODO: исправить ошибку освобождения памяти в text

    for(const json::element& e: array)
    {
        if(e.is_type<int>())
        {
            ASSERT_TRUE(e.get<int>() == num.get<int>());
        }
        else if(e.is_type<std::string>())
        {
            ASSERT_TRUE(e.get<std::string>() == text.get<std::string>());
        }
        else if(e.is_type<bool>())
        {
            ASSERT_TRUE(e.get<bool>() == value.get<bool>());
        }
    }
}
