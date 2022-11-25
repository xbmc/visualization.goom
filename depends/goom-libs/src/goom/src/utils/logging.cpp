// NOLINTBEGIN: Tricky logging code - need to improve

#include "logging.h"

#include "date_utils.h"

#include <format>
#include <functional>
#include <memory>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <string>

namespace GOOM::UTILS
{

std::unique_ptr<Logging> Logging::logger(new Logging());

Logging::Logging() noexcept
{
  SetFileLogLevel(m_cutoffFileLogLevel);
  SetHandlersLogLevel(m_cutoffHandlersLogLevel);
}

Logging::~Logging()
{
  DoFlush();
}

auto Logging::SetDoDateTime(const bool val) -> void
{
  m_doDateTime = val;
}

auto Logging::VLog(const LogLevel lvl,
                   const int lineNum,
                   const std::string& funcName,
                   const std::string& formatStr,
                   const std20::format_args args) -> void
{
  std20::memory_buffer buffer;
  // Pass custom argument formatter as a template arg to vwrite.
  std20::vformat_to(std20::detail::buffer_appender<char>(buffer), formatStr, args);
  Log(lvl, lineNum, funcName, std::string(buffer.data(), buffer.size()));
}

auto Logging::Log(LogLevel lvl,
                  const int lineNum,
                  const std::string& funcName,
                  const std::string& msg) -> void
{
  const std::lock_guard<std::mutex> lock{m_mutex};
  if (!m_doLogging)
  {
    return;
  }

  const std::string mainMsg = funcName + ":" + std::to_string(lineNum) + ":" + msg;
  const std::string logMsg =
      not m_doDateTime ? mainMsg : GetCurrentDateTimeAsString() + ":" + mainMsg;

  if (lvl >= m_cutoffFileLogLevel)
  {
    m_logEntries.push_back(logMsg);
  }
  if (lvl >= m_cutoffHandlersLogLevel)
  {
    for (const auto& handler : m_handlers)
    {
      handler.second(lvl, logMsg);
    }
  }
}

auto Logging::Start() -> void
{
  const std::lock_guard<std::mutex> lock{m_mutex};
  m_doLogging = true;
  m_logEntries.clear();
}

auto Logging::Stop() -> void
{
  const std::lock_guard<std::mutex> lock{m_mutex};
  m_doLogging = false;
  DoFlush();
}

auto Logging::SetFileLogLevel(const LogLevel lvl) -> void
{
  m_cutoffFileLogLevel = lvl;
}

auto Logging::SetHandlersLogLevel(const LogLevel lvl) -> void
{
  m_cutoffHandlersLogLevel = lvl;
}

auto Logging::AddHandler(const std::string& name, const HandlerFunc& handlerFunc) -> void
{
  for (const auto& handler : m_handlers)
  {
    if (handler.first == name)
    {
      return;
    }
  }
  m_handlers.emplace_back(name, handlerFunc);
}

auto Logging::Flush() -> void
{
  const std::lock_guard<std::mutex> lock{m_mutex};
  DoFlush();
}

auto Logging::DoFlush() -> void
{
  if (m_logFile.empty())
  {
    return;
  }
  if (m_logEntries.empty())
  {
    return;
  }

  std::ofstream f(m_logFile, std::ios::out | std::ios::app);
  if (!f.good())
  {
    throw std::runtime_error("Could not open log file \"" + m_logFile + "\".");
  }
  for (const auto& entry : m_logEntries)
  {
    f << entry << std::endl;
  }

  m_logEntries.clear();
}

} // namespace GOOM::UTILS

// NOLINTEND
