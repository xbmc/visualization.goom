#ifndef VISUALIZATION_GOOM_LIB_GOOMUTILS_ENUMUTILS_H_
#define VISUALIZATION_GOOM_LIB_GOOMUTILS_ENUMUTILS_H_

#if __cplusplus > 201402L
#include "color_data/colormap_enums.h"

#include <magic_enum.hpp>
#include <stdexcept>
#endif
#include <cstdint>
#include <string>

#if __cplusplus > 201402L
namespace GOOM::UTILS
{
template<class E>
constexpr uint32_t NUM = static_cast<size_t>(E::_NUM);
}

template<>
struct magic_enum::customize::enum_range<GOOM::UTILS::COLOR_DATA::ColorMapName>
{
  inline static constexpr int min = -1;
  inline static constexpr int max = GOOM::UTILS::NUM<GOOM::UTILS::COLOR_DATA::ColorMapName>;
  static_assert(max > min, "magic_enum::customize::enum_range requires max > min.");
};
#endif

#if __cplusplus <= 201402L
namespace GOOM
{
namespace UTILS
{
#else
namespace GOOM::UTILS
{
#endif

#if __cplusplus <= 201402L
template<class E>
constexpr uint32_t NUM = static_cast<size_t>(E::_NUM);
#endif

template<class E>
auto EnumToString(const E e) -> std::string
{
#if __cplusplus <= 201402L
  return std::to_string(static_cast<int>(e));
#else
  return std::string(magic_enum::enum_name(e));
#endif
}

#if __cplusplus > 201402L
template<class E>
auto StringToEnum(const std::string& eStr) -> E
{
  const auto val = magic_enum::enum_cast<E>(eStr);
  if (val)
  {
    return *val;
  }

  throw std::runtime_error("Unknown enum value \"" + eStr + "\".");
}
#endif

#if __cplusplus <= 201402L
} // namespace UTILS
} // namespace GOOM
#else
} // namespace GOOM::UTILS
#endif
#endif
