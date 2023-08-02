#pragma once

#include <lazyjson/variant.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace lazyjson
{

/// @brief Предварительное определение
class array;

/// @brief Предварительное определение
class json;

/// @brief Тип значения
using element = variant<int, float, bool, std::string, json, array>;

/// @brief Массив
class array
{
public:
    using iterator = std::vector<element>::iterator;
    using const_iterator = std::vector<element>::const_iterator;
    using reverse_iterator = std::vector<element>::reverse_iterator;
    using const_reverse_iterator = std::vector<element>::const_reverse_iterator;

    /// @brief Итератор на начало
    /// @return Итератор
    iterator begin()
    {
        return m_vec.begin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    iterator end()
    {
        return m_vec.end();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    const_iterator begin() const
    {
        return m_vec.begin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    const_iterator end() const
    {
        return m_vec.end();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    const_iterator cbegin() const
    {
        return m_vec.cbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    const_iterator cend() const
    {
        return m_vec.cend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    reverse_iterator rbegin()
    {
        return m_vec.rbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    reverse_iterator rend()
    {
        return m_vec.rend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    const_reverse_iterator rbegin() const
    {
        return m_vec.rbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    const_reverse_iterator rend() const
    {
        return m_vec.rend();
    }

    /// @brief Итератор на начало
    /// @return Итератор
    const_reverse_iterator crbegin() const
    {
        return m_vec.crbegin();
    }

    /// @brief Итератор на конец
    /// @return Итератор
    const_reverse_iterator crend() const
    {
        return m_vec.crend();
    }

    /// @brief Оператор рандомного доступа
    /// @param index Индекс
    /// @return Элемент
    element& operator[](std::size_t index)
    {
        return m_vec[index];
    }

    /// @brief Оператор рандомного доступа
    /// @param index Индекс
    /// @return Элемент
    const element& operator[](std::size_t index) const
    {
        return m_vec[index];
    }

    /// @brief Добавить элемент в массив
    /// @param value Элемент
    void push_back(const element& value)
    {
        m_vec.push_back(value);
    }

    /// @brief Очистить массив
    void clear()
    {
        m_vec.clear();
    }

    /// @brief Проверить пустой ли массив
    /// @return True, если пустой
    bool empty() const
    {
        return m_vec.empty();
    }

    /// @brief Удалить крайний объект
    void pop_back()
    {
        if(!m_vec.empty())
        {
            m_vec.pop_back();
        }
    }

    /// @brief Получить первый объект
    /// @return Первый элемент
    element& front()
    {
        return m_vec.front();
    }

    /// @brief Получить первый объект
    /// @return Первый элемент
    const element& front() const
    {
        return m_vec.front();
    }

    /// @brief Получить размер массива
    /// @return Размер массива
    std::size_t size() const
    {
        return m_vec.size();
    }

private:
    /// @brief Массив данных
    std::vector<element> m_vec;
};

/// @brief JSON объект
class json
{
public:
    /// @brief Доступ к объекту по ключу
    /// @param key Ключ
    /// @return Значение
    element& operator[](const std::string& key)
    {
        auto& it = m_obj.find(key);
        if(it != m_obj.end())
        {
            return it->second;
        }

        return m_obj[key];
    }

    /// @brief Доступ к объекту по ключу
    /// @param key Ключ
    /// @return Значение
    /// @throw std::out_of_range, если не существует ключ
    const element& operator[](const std::string& key) const
    {
        return m_obj.at(key);
    }

private:
    /// @brief Список в виде ключ/значение
    std::unordered_map<std::string, element> m_obj;
};

} // namespace lazyjson
