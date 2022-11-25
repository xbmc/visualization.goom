#include "date_utils.h"

#include <chrono>
#include <ctime>
#include <string>

namespace GOOM::UTILS
{

inline auto GetTimeTAsString(const std::time_t timeT) noexcept -> std::string
{
  static constexpr auto BUFF_SIZE = 100U;
  struct tm buff
  {
  };
#ifdef _MSC_VER
  ::localtime_s(&buff, &timeT);
  if (char str[BUFF_SIZE]; std::strftime(str, sizeof(str), "%Y-%m-%d_%H-%M-%S", &buff))
  {
    return std::string{str};
  }
#else
  if (char str[BUFF_SIZE];
      std::strftime(str, sizeof(str), "%Y-%m-%d_%H-%M-%S", ::localtime_r(&timeT, &buff)))
  {
    return std::string{str};
  }
#endif

  return "TIME_ERROR";
}

#ifdef _MSC_VER
auto GetStandardDateTimeString(const std::string& otherFormatDateTime,
                               [[maybe_unused]] const std::string& otherFormat) noexcept
    -> std::string
{
  // 'strptime' is not supported by Microsoft.
  return otherFormatDateTime;
}
#else

auto GetStandardDateTimeString(const std::string& otherFormatDateTime,
                               const std::string& otherFormat) noexcept -> std::string
{
  struct tm timeTm;
  ::strptime(otherFormatDateTime.c_str(), otherFormat.c_str(), &timeTm);
  timeTm.tm_isdst = -1; // check for daylight savings
  const time_t timeT = ::mktime(&timeTm);
  return GetTimeTAsString(timeT);
}
#endif

inline auto GetSteadyClockAsTimeT(const std::chrono::steady_clock::time_point t) noexcept -> time_t
{
  const auto steadyClockDiff = t - std::chrono::steady_clock::now();
  const auto millisDiff = std::chrono::duration_cast<std::chrono::milliseconds>(steadyClockDiff);
  return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + millisDiff);
}

auto GetCurrentDateTimeAsString() noexcept -> std::string
{
  return GetSteadyClockAsString(std::chrono::steady_clock::now());
}

auto GetSteadyClockAsString(const std::chrono::steady_clock::time_point& timePoint) noexcept
    -> std::string
{
  const std::time_t timeT = GetSteadyClockAsTimeT(timePoint);
  return GetTimeTAsString(timeT);
}

} // namespace GOOM::UTILS
