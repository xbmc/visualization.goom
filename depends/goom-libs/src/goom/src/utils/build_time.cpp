#include "build_time.h"

#include "date_utils.h"

namespace GOOM::UTILS
{

auto GetBuildTime() -> std::string
{
  static constexpr auto BUILD_TIME     = __DATE__ ", " __TIME__;
  static constexpr auto BUILD_TIME_FMT = "%b %d %Y, %H:%M:%S";
  return GetStandardDateTimeString(BUILD_TIME, BUILD_TIME_FMT);
}

} // namespace GOOM::UTILS
