#pragma once

//#define NO_MAGIC_ENUM_AVAILABLE

#include "goom_config.h"

#include <array>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

#ifndef NO_MAGIC_ENUM_AVAILABLE
#include <magic_enum.hpp>
#include <stdexcept>
#endif

namespace GOOM::UTILS
{

template<class E>
static constexpr auto NUM = static_cast<uint32_t>(E::_num);

template<class E>
auto EnumToString(E value) -> std::string;

template<class E>
auto StringToEnum(const std::string& eStr) -> E;

template<typename E, typename T>
class EnumMap
{
public:
  static_assert(std::is_enum_v<E>);

  struct KeyValue
  {
    E key; // NOLINT(misc-non-private-member-variables-in-classes)
    T value; // NOLINT(misc-non-private-member-variables-in-classes)
    // NOLINTBEGIN(readability-identifier-length)
    constexpr KeyValue(E k, const T& v) : key{k}, value{v} {}
    constexpr KeyValue(E k, T&& v) : key{k}, value{std::move(v)} {}
    // NOLINTEND(readability-identifier-length)
    KeyValue() = delete;
  };

  constexpr EnumMap() noexcept = default;
  explicit constexpr EnumMap(std::array<KeyValue, NUM<E>>&& keyValues) noexcept;
  static constexpr auto Make(std::vector<KeyValue>&& keyValues) noexcept -> EnumMap<E, T>;

  [[nodiscard]] constexpr auto size() const noexcept -> size_t;
  [[nodiscard]] constexpr auto operator[](E key) const noexcept -> const T&;
  [[nodiscard]] constexpr auto operator[](E key) noexcept -> T&;

  [[nodiscard]] constexpr auto keys() -> std::array<E, NUM<E>>;
  [[nodiscard]] constexpr auto begin() const { return m_keyValues.begin(); }
  [[nodiscard]] constexpr auto begin() { return m_keyValues.begin(); }
  [[nodiscard]] constexpr auto end() const { return m_keyValues.end(); }
  [[nodiscard]] constexpr auto end() { return m_keyValues.end(); }

private:
  explicit constexpr EnumMap(std::array<T, NUM<E>>&& keyValues) noexcept;
  std::array<T, NUM<E>> m_keyValues;
  template<typename V>
  [[nodiscard]] static constexpr auto GetSortedValuesArray(V&& keyValues) noexcept
      -> std::array<T, NUM<E>>;
};

template<typename E, typename T>
class RuntimeEnumMap
{
public:
  static_assert(std::is_enum_v<E>);
  using KeyValue = typename EnumMap<E, T>::KeyValue;

  RuntimeEnumMap() = delete;
  explicit RuntimeEnumMap(std::array<KeyValue, NUM<E>>&& keyValues) noexcept;
  static auto Make(std::vector<KeyValue>&& keyValues) noexcept -> RuntimeEnumMap<E, T>;

  [[nodiscard]] auto size() const noexcept -> size_t; // NOLINT(readability-identifier-naming)
  [[nodiscard]] auto operator[](E key) const noexcept -> const T&;
  [[nodiscard]] auto operator[](E key) noexcept -> T&;

private:
  explicit RuntimeEnumMap(std::vector<T>&& keyValues) noexcept;
  std::vector<T> m_keyValues;
  template<typename V>
  [[nodiscard]] static auto GetSortedValuesArray(V&& keyValues) noexcept -> std::vector<T>;
};

template<typename E, typename T>
constexpr EnumMap<E, T>::EnumMap(std::array<KeyValue, NUM<E>>&& keyValues) noexcept
  : m_keyValues{std::move(GetSortedValuesArray(keyValues))}
{
}

template<typename E, typename T>
constexpr auto EnumMap<E, T>::Make(std::vector<KeyValue>&& keyValues) noexcept -> EnumMap<E, T>
{
  return EnumMap{GetSortedValuesArray(keyValues)};
}

template<typename E, typename T>
constexpr EnumMap<E, T>::EnumMap(std::array<T, NUM<E>>&& keyValues) noexcept
  : m_keyValues{keyValues}
{
}

template<typename E, typename T>
constexpr auto EnumMap<E, T>::keys() -> std::array<E, NUM<E>>
{
  auto keys = std::array<E, NUM<E>>{};
  for (auto i = 0U; i < NUM<E>; ++i)
  {
    keys[i] = static_cast<E>(i);
  }
  return keys;
}

template<typename E, typename T>
constexpr auto EnumMap<E, T>::operator[](const E key) const noexcept -> const T&
{
  return m_keyValues[static_cast<uint32_t>(key)];
}

template<typename E, typename T>
constexpr auto EnumMap<E, T>::operator[](const E key) noexcept -> T&
{
  return m_keyValues[static_cast<uint32_t>(key)];
}

template<typename E, typename T>
constexpr auto EnumMap<E, T>::size() const noexcept -> size_t
{
  return m_keyValues.size();
}

template<typename E, typename T>
template<typename V>
constexpr auto EnumMap<E, T>::GetSortedValuesArray(V&& keyValues) noexcept -> std::array<T, NUM<E>>
{
  auto sortedValuesArray = std::array<T, NUM<E>>{};
  for (auto& keyValue : keyValues)
  {
    sortedValuesArray[static_cast<uint32_t>(keyValue.key)] = std::move(keyValue.value);
  }
  return sortedValuesArray;
}

template<typename E, typename T>
inline RuntimeEnumMap<E, T>::RuntimeEnumMap(std::array<KeyValue, NUM<E>>&& keyValues) noexcept
  : m_keyValues{GetSortedValuesArray(keyValues)}
{
}

template<typename E, typename T>
inline auto RuntimeEnumMap<E, T>::Make(std::vector<KeyValue>&& keyValues) noexcept
    -> RuntimeEnumMap<E, T>
{
  return RuntimeEnumMap{GetSortedValuesArray(keyValues)};
}

template<typename E, typename T>
inline RuntimeEnumMap<E, T>::RuntimeEnumMap(std::vector<T>&& keyValues) noexcept
  : m_keyValues{keyValues}
{
}

template<typename E, typename T>
inline auto RuntimeEnumMap<E, T>::operator[](const E key) const noexcept -> const T&
{
  return m_keyValues[static_cast<uint32_t>(key)];
}

template<typename E, typename T>
inline auto RuntimeEnumMap<E, T>::operator[](const E key) noexcept -> T&
{
  return m_keyValues[static_cast<uint32_t>(key)];
}

template<typename E, typename T>
inline auto RuntimeEnumMap<E, T>::size() const noexcept -> size_t
{
  return m_keyValues.size();
}

template<typename E, typename T>
template<typename V>
inline auto RuntimeEnumMap<E, T>::GetSortedValuesArray(V&& keyValues) noexcept -> std::vector<T>
{
  Expects(keyValues.size() == NUM<E>);

  auto keysArray = std::vector<uint32_t>(NUM<E>);
  for (auto i = 0U; i < NUM<E>; ++i)
  {
    keysArray[static_cast<uint32_t>(keyValues[i].key)] = i;
  }

  auto sortedValuesArray = std::vector<T>{};
  for (const auto& key : keysArray)
  {
    sortedValuesArray.emplace_back(keyValues[key].value);
  }
  return sortedValuesArray;
}

#ifdef NO_MAGIC_ENUM_AVAILABLE
template<class E>
auto EnumToString(const E value) -> std::string
{
  static_assert(std::is_enum_v<E>);
  return std::to_string(static_cast<int>(value));
}
#else
template<class E>
auto EnumToString(const E value) -> std::string
{
  static_assert(std::is_enum_v<E>);
  return std::string(magic_enum::enum_name(value));
}

template<class E>
auto StringToEnum(const std::string& eStr) -> E
{
  static_assert(std::is_enum_v<E>);

  if (const auto val = magic_enum::enum_cast<E>(eStr); val)
  {
    return *val;
  }

  throw std::runtime_error("Unknown enum value \"" + eStr + "\".");
}
#endif

} // namespace GOOM::UTILS
