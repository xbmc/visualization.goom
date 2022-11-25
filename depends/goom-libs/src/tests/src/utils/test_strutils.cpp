#include "catch2/catch.hpp"
#include "utils/enum_utils.h"
#include "utils/strutils.h"

#include <string>
#include <vector>

namespace GOOM::UNIT_TESTS
{

using namespace UTILS;

TEST_CASE("FindAndReplaceAll")
{
  std::string str               = "hello Everyone out there. hello again and Hello again.";
  const std::string expectedStr = "Hello Everyone out there. Hello again and Hello again.";

  FindAndReplaceAll(str, "hello", "Hello");
  REQUIRE(str == expectedStr);

  FindAndReplaceAll(str, "zzz", "ZZZ");
  REQUIRE(str == expectedStr);
}

TEST_CASE("StringJoin", "[StringJoin]")
{
  REQUIRE("" == StringJoin({""}, ", "));
  REQUIRE("word1" == StringJoin({"word1"}, ", "));
  REQUIRE("word1, word2, word3" == StringJoin({"word1", "word2", "word3"}, ", "));
  REQUIRE("word1, word2, word3," == StringJoin({"word1", "word2", "word3,"}, ", "));
}

TEST_CASE("StringSplit", "[StringSplit]")
{
  const std::string testString1 = "line1: word1, word2\nline2: word3, word4\n";

  const std::vector<std::string> test1 = StringSplit(testString1, ",");
  UNSCOPED_INFO("testString1 = \"" << testString1 + "\"");
  for (const auto& s : test1)
  {
    UNSCOPED_INFO("s = " << s);
  }
  REQUIRE(test1.size() == 3);
  REQUIRE(test1[0] == "line1: word1");
  REQUIRE(test1[1] == " word2\nline2: word3");
  REQUIRE(test1[2] == " word4\n");

  const std::vector<std::string> test2 = StringSplit(testString1, "\n");
  REQUIRE(test2.size() == 2);
  REQUIRE(test2[0] == "line1: word1, word2");
  REQUIRE(test2[1] == "line2: word3, word4");

  const std::string testString2        = "word1; word2; word3; word4";
  const std::vector<std::string> test3 = StringSplit(testString2, "; ");
  REQUIRE(test3.size() == 4);
  REQUIRE(test3[0] == "word1");
  REQUIRE(test3[1] == "word2");
  REQUIRE(test3[2] == "word3");
  REQUIRE(test3[3] == "word4");

  const std::string testString3        = "word1 \nword2\nword3 \nword4 ";
  const std::vector<std::string> test4 = StringSplit(testString3, "\n");
  REQUIRE(test4.size() == 4);
  REQUIRE(test4[0] == "word1 ");
  REQUIRE(test4[1] == "word2");
  REQUIRE(test4[2] == "word3 ");
  REQUIRE(test4[3] == "word4 ");
}

TEST_CASE("EnumToString", "[EnumToString]")
{
  enum class EnumTester
  {
    _NULL = -1,
    TEST1,
    TEST2,
    TEST3,
    _num // unused, and marks the enum end
  };

  EnumTester test = EnumTester::_NULL;
  REQUIRE(EnumToString(test) == "_NULL");
  test = EnumTester::TEST1;
  REQUIRE(EnumToString(test) == "TEST1");
  test = EnumTester::TEST2;
  REQUIRE(EnumToString(test) == "TEST2");
  test = EnumTester::_num;
  REQUIRE(EnumToString(test) == "_num");

  REQUIRE(EnumToString(EnumTester::TEST3) == "TEST3");
}

} // namespace GOOM::UNIT_TESTS
