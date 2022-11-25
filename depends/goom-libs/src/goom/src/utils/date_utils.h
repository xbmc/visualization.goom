#pragma once

#include <chrono>
#include <string>

namespace GOOM::UTILS
{

[[nodiscard]] auto GetCurrentDateTimeAsString() noexcept -> std::string;

[[nodiscard]] auto GetStandardDateTimeString(const std::string& otherFormatDateTime,
                                             const std::string& otherFormat) noexcept
    -> std::string;

[[nodiscard]] auto GetSteadyClockAsString(
    const std::chrono::steady_clock::time_point& timePoint) noexcept -> std::string;

} // namespace GOOM::UTILS
