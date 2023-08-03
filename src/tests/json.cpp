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

    const json::element num{1};
    const json::element text{std::string{"some very long and useless text"}};
    const json::element value{true};

    array.push_back(num);
    array.push_back(text);
    array.push_back(value);

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
        else
        {
            GTEST_FAIL();
        }
    }
}

// Сравнение одинаковых JSON объектов
TEST(JsonUsage, CompareEqualJsons)
{
    json::json json1;
    json::json json2;

    json::array array;

    array.push_back(json::element{1});
    array.push_back(json::element{std::string{"some text"}});
    array.push_back(json::element{false});
    array.push_back(json::element{1.0123f});

    json1["array"] = array;
    json2["array"] = array;

    ASSERT_EQ(json1, json2);
}

// Сравнение разных JSON объектов
TEST(JsonUsage, CompareNotEqualJsons)
{
    json::json json1;
    json::json json2;
    json::json json3;
    json::json json4;
    json::json json5;

    json::array array;

    array.push_back(json::element{1});
    array.push_back(json::element{std::string{"some text"}});
    array.push_back(json::element{false});
    array.push_back(json::element{1.0123f});

    json1["array"] = array;
    json2["array2"] = array;
    json3["buffer"] = array;

    array.pop_back();

    json4["buffer"] = array;

    const std::vector<json::json> v{json1, json2, json3, json4, json5};

    for(size_t i = 0; i < v.size(); ++i)
    {
        for(size_t j = i + 1; j < v.size(); ++j)
        {
            ASSERT_NE(v[i], v[j]);
        }
    }
}

// Сравнение одинаковых JSON объектов
TEST(JsonUsage, CompareEqualArrays)
{
    json::array array1;
    json::array array2;

    array1.push_back(json::element{1});
    array2.push_back(json::element{1});
    array1.push_back(json::element{std::string{"some text"}});
    array2.push_back(json::element{std::string{"some text"}});
    array1.push_back(json::element{false});
    array2.push_back(json::element{false});
    array1.push_back(json::element{1.0123f});
    array2.push_back(json::element{1.0123f});

    ASSERT_EQ(array1, array2);
}

// Сравнение разных JSON массивов
TEST(JsonUsage, CompareNotEqualArrays)
{
    json::array array1;
    json::array array2;

    array1.push_back(json::element{1});
    array2.push_back(json::element{1});
    array1.push_back(json::element{std::string{"some text"}});
    array2.push_back(json::element{std::string{"some text"}});
    array1.push_back(json::element{false});
    array1.push_back(json::element{1.0123f});

    ASSERT_NE(array1, array2);
}

// Сравнение JSON массивов после копирования
TEST(JsonUsage, CompareCopiedArrays)
{
    json::array array1;
    json::array array2;

    array1.push_back(json::element{1});
    array1.push_back(json::element{std::string{"some text"}});
    array1.push_back(json::element{false});
    array1.push_back(json::element{1.0123f});

    array2 = array1;
    json::array array3{array2};
    json::array array4 = array3;

    ASSERT_EQ(array1, array2);
    ASSERT_EQ(array1, array3);
    ASSERT_EQ(array1, array4);
}
