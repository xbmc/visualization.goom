#include "filter_colors_service.h"

#include "utils/name_value_pairs.h"

#include <string>

namespace GOOM::FILTER_FX
{

using UTILS::GetPair;
using UTILS::NameValuePairs;

auto FilterColorsService::GetNameValueParams(const std::string& paramGroup) const noexcept
    -> NameValuePairs
{
  return {
      GetPair(paramGroup, "blockyWavy", m_blockyWavy),
      GetPair(paramGroup, "buffIntensity", m_buffSettings.buffIntensity),
  };
}

} // namespace GOOM::FILTER_FX
