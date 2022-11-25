#include "catch2/catch.hpp"
#include "utils/enum_utils.h"

#include <algorithm>
#include <string>

namespace GOOM::UNIT_TESTS
{

using UTILS::EnumMap;
using UTILS::RuntimeEnumMap;
using UTILS::EnumToString;
using UTILS::NUM;
using UTILS::StringToEnum;

TEST_CASE("EnumMap")
{
  enum class EnumClass
  {
    ENUM1,
    ENUM2,
    ENUM3,
    _num // unused, and marks the enum end
  };
  REQUIRE(NUM<EnumClass> == 3);

  auto enumMap         = EnumMap<EnumClass, std::string>{{{
      {EnumClass::ENUM1, "enum1"},
      {EnumClass::ENUM3, "enum3"},
      {EnumClass::ENUM2, "enum2"},
  }}};
  auto nonConstEnumMap = RuntimeEnumMap<EnumClass, std::string>{{{
      {EnumClass::ENUM1, "enum1"},
      {EnumClass::ENUM3, "enum3"},
      {EnumClass::ENUM2, "enum2"},
  }}};

  REQUIRE(enumMap.size() == 3);
  REQUIRE(enumMap[EnumClass::ENUM1] == "enum1");
  REQUIRE(enumMap[EnumClass::ENUM2] == "enum2");
  REQUIRE(enumMap[EnumClass::ENUM3] == "enum3");

  REQUIRE(nonConstEnumMap.size() == 3);
  REQUIRE(nonConstEnumMap[EnumClass::ENUM1] == "enum1");
  REQUIRE(nonConstEnumMap[EnumClass::ENUM2] == "enum2");
  REQUIRE(nonConstEnumMap[EnumClass::ENUM3] == "enum3");

  enumMap[EnumClass::ENUM2] = "ENUM2";
  REQUIRE(enumMap[EnumClass::ENUM2] == "ENUM2");

  nonConstEnumMap[EnumClass::ENUM2] = "ENUM2";
  REQUIRE(nonConstEnumMap[EnumClass::ENUM2] == "ENUM2");

  struct Simple
  {
    int i1;
    int i2;
  };
  static constexpr const auto CONST_ENUM_MAP = EnumMap<EnumClass, Simple>{{{
      {EnumClass::ENUM1, {1, 2}},
      {EnumClass::ENUM3, {5, 6}},
      {EnumClass::ENUM2, {3, 4}},
  }}};
  const auto NON_CONST_ENUM_MAP              = RuntimeEnumMap<EnumClass, Simple>{{{
      {EnumClass::ENUM1, {1, 2}},
      {EnumClass::ENUM3, {5, 6}},
      {EnumClass::ENUM2, {3, 4}},
  }}};

  static_assert(CONST_ENUM_MAP.size() == NUM<EnumClass>);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM1].i1 == 1);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM1].i2 == 2);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM2].i1 == 3);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM2].i2 == 4);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM3].i1 == 5);
  static_assert(CONST_ENUM_MAP[EnumClass::ENUM3].i2 == 6);

  REQUIRE(NON_CONST_ENUM_MAP.size() == NUM<EnumClass>);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM1].i1 == 1);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM1].i2 == 2);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM2].i1 == 3);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM2].i2 == 4);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM3].i1 == 5);
  REQUIRE(NON_CONST_ENUM_MAP[EnumClass::ENUM3].i2 == 6);
}

TEST_CASE("ForRange")
{
  enum class EnumClass
  {
    ENUM1,
    ENUM2,
    ENUM3,
    _num // unused, and marks the enum end
  };
  REQUIRE(NUM<EnumClass> == 3);

  static constexpr const auto CONST_ENUM_MAP = EnumMap<EnumClass, int>{{{
      {EnumClass::ENUM1, 1},
      {EnumClass::ENUM3, 2},
      {EnumClass::ENUM2, 3},
  }}};
  auto sum                                   = 0;
  for (const auto& value : CONST_ENUM_MAP)
  {
    sum += value;
  }
  REQUIRE(sum == 6);

  sum = 0;
  std::for_each(std::begin(CONST_ENUM_MAP),
                std::end(CONST_ENUM_MAP),
                [&sum](const auto& value) { sum += value; });
  REQUIRE(sum == 6);
}

//#define TEST_SHOULD_NOT_COMPILE
#ifdef TEST_SHOULD_NOT_COMPILE
TEST_CASE("EnumMapValidation")
{
  enum class EnumClass
  {
    ENUM1,
    ENUM2,
    ENUM3,
    _num // unused, and marks the enum end
  };

  static constexpr auto CONST_ENUM_MAP_WILL_COMPILE = EnumMap<EnumClass, int>{{{
      {EnumClass::ENUM1, 1},
      {EnumClass::ENUM2, 2},
      {EnumClass::ENUM2, 3},
  }}};
  REQUIRE(CONST_ENUM_MAP_WILL_COMPILE.size() == 3);
  static constexpr auto CONST_ENUM_MAP_NOT_COMPILE = EnumMap<EnumClass, int>{{{
      {EnumClass::ENUM1, 1},
      {EnumClass::ENUM2, 2},
  }}};
}
#endif

TEST_CASE("EnumToString/StringToEnum")
{
#ifdef NO_MAGIC_ENUM_AVAILABLE
#error "Must have magic_enum available."
#endif

  enum class EnumClass
  {
    ENUM1,
    ENUM2,
    ENUM3,
    _num // unused, and marks the enum end
  };
  REQUIRE(NUM<EnumClass> == 3);

  REQUIRE(EnumToString(EnumClass::ENUM1) == "ENUM1");
  REQUIRE(StringToEnum<EnumClass>("ENUM1") == EnumClass::ENUM1);
  REQUIRE(EnumToString(EnumClass::ENUM2) == "ENUM2");
  REQUIRE(StringToEnum<EnumClass>("ENUM2") == EnumClass::ENUM2);
  REQUIRE(EnumToString(EnumClass::ENUM3) == "ENUM3");
  REQUIRE(StringToEnum<EnumClass>("ENUM3") == EnumClass::ENUM3);
}

} // namespace GOOM::UNIT_TESTS
