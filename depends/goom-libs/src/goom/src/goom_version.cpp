#include "goom_version.h"

#include <string>

namespace GOOM
{

auto GetFullVersionStr() -> std::string
{
  return std::string(GOOM_VER_NAME) + " " + std::to_string(GOOM_VER_MAJOR) + "." +
         std::to_string(GOOM_VER_MINOR) + "." + std::to_string(GOOM_VER_REVISION) + "," + " " +
         GOOM_VER_DESCRIPTION;
}

} // namespace GOOM
