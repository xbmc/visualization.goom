#include "name_value_pairs.h"

#include "strutils.h"

#include <algorithm>
#include <vector>

namespace GOOM::UTILS
{


[[nodiscard]] auto GetNameValuesString(const NameValuePairs& nameValuePairs) -> std::string
{
  auto nameValueStrings = std::vector<std::string>{};
  std::transform(cbegin(nameValuePairs),
                 cend(nameValuePairs),
                 std::back_inserter(nameValueStrings),
                 [](const NameValuePair& pair) { return GetNameValueString(pair); });
  return StringJoin(nameValueStrings, "\n");
}

} // namespace GOOM::UTILS
