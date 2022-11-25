#pragma once

#include <string_view>
#include <vector>

namespace GOOM::UTILS
{

auto FindAndReplaceAll(std::string& dataStr,
                       const std::string& searchStr,
                       const std::string& replaceStr) -> void;

// NOLINTNEXTLINE(readability-identifier-naming)
[[nodiscard]] auto bool_to_string(bool value) -> std::string;

[[nodiscard]] auto StringSplit(const std::string& str, const std::string_view& delim)
    -> std::vector<std::string>;

[[nodiscard]] auto StringJoin(const std::vector<std::string>& strings,
                              const std::string_view& delim) -> std::string;

} // namespace GOOM::UTILS
