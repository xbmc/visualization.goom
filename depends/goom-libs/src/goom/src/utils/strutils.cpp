#include "strutils.h"

#if __cplusplus > 201703L
#include <ranges>
#endif
#include <string>
#include <vector>

namespace GOOM::UTILS
{

auto FindAndReplaceAll(std::string& dataStr,
                       const std::string& searchStr,
                       const std::string& replaceStr) -> void
{
  auto pos = dataStr.find(searchStr);
  while (pos != std::string::npos)
  {
    dataStr.replace(pos, searchStr.size(), replaceStr);
    pos = dataStr.find(searchStr, pos + replaceStr.size());
  }
}

auto bool_to_string(const bool value) -> std::string
{
  return value ? "true" : "false";
}

auto StringJoin(const std::vector<std::string>& strings, const std::string_view& delim)
    -> std::string
{
  auto joinedStr = std::string{};

  for (auto str = cbegin(strings); str != cend(strings); ++str)
  {
    joinedStr += *str;
    if (str != (cend(strings) - 1))
    {
      joinedStr += delim;
    }
  }

  return joinedStr;
}

auto StringSplit(const std::string& str, const std::string_view& delim) -> std::vector<std::string>
{
#if __cplusplus <= 201703L
  auto vec       = std::vector<std::string>{};
  auto copyOfStr = str;
  while (true)
  {
    const auto pos = copyOfStr.find(delim);
    if (pos == std::string::npos)
    {
      break;
    }
    const auto token = copyOfStr.substr(0, pos);
    copyOfStr.erase(0, pos + delim.length());
    vec.emplace_back(token);
  }
  if (!copyOfStr.empty())
  {
    vec.emplace_back(copyOfStr);
  }
  return vec;
#else
  auto parts = str | std::ranges::views::split(delim);
  std::vector<std::string> vec;
  for (auto part : parts)
  {
    std::string s = "";
    for (auto c : part)
    {
      s += c;
    }
    vec.emplace_back(s);
  }
  return vec;
#endif
}

} // namespace GOOM::UTILS
