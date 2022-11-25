#pragma once

#include <string>

namespace GOOM
{

[[nodiscard]] inline auto GetCompilerVersion() -> std::string
{
#if defined(__clang_major__)
  return std::string("clang ") + std::to_string(__clang_major__) + "." +
         std::to_string(__clang_minor__) + "-" + std::to_string(__clang_patchlevel__);
#elif defined(__GNUC__)
  return std::string("gcc ") + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__);
#elif defined(_MSC_VER)
  return std::string("MSC ") + std::to_string(_MSC_VER);
#elif defined(__MINGW32_MAJOR_VERSION)
  return std::string("MinGw32 ") + std::to_string(__MINGW32_MAJOR_VERSION) +
         std::to_string(__MINGW32_MINOR_VERSION);
#elif defined(__MINGW64_VERSION_MAJOR)
  return std::string("MinGw64 ") + std::to_string(__MINGW64_VERSION_MAJOR) +
         std::to_string(__MINGW64_VERSION_MINOR);
#else
  return "unknown_compiler";
#endif
}

} // namespace GOOM
