#include <lazyjson/json.hpp>

#include <gtest/gtest.h>

#include <string>

namespace json = lazyjson;

// Присваивание булевого значения
TEST(Test, BoolValue)
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
TEST(Test, IntValue)
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
TEST(Test, FloatValue)
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
TEST(Test, StringValue)
{
    const std::string test = "Some random string value";
    json::json json;
    json["test"] = test;

    ASSERT_TRUE(json["test"].is_type<std::string>());
    ASSERT_FALSE(json["test"].is_type<bool>());

    const std::string res = json["test"].get<std::string>();
    ASSERT_EQ(res, test);
}
