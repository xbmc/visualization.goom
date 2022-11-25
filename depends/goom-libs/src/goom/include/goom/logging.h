// NOLINTBEGIN: Tricky logging code - need to improve

#pragma once

#include <format>
#include <fstream>
#include <functional>
#include <memory>
#include <mutex>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace GOOM::UTILS
{

class Logging
{
public:
  enum class LogLevel
  {
    DEBUG,
    INFO,
    WARN,
    // TODO Make others use 'L_' (MSCV build issue)
    L_ERROR
  };
  using HandlerFunc = std::function<void(const LogLevel, const std::string&)>;

  static auto GetLogger() -> Logging&;
  ~Logging();
  Logging(const Logging&)                    = delete;
  Logging(Logging&&)                         = delete;
  auto operator=(const Logging&) -> Logging& = delete;
  auto operator=(Logging&&) -> Logging&      = delete;

  auto SetLogFile(const std::string& logF) -> void;
  auto AddHandler(const std::string& name, const HandlerFunc& handlerFunc) -> void;
  auto SetDoDateTime(bool val) -> void;
  auto Start() -> void;
  auto Stop() -> void;
  auto Flush() -> void;
  auto Suspend() -> void;
  auto Resume() -> void;
  [[nodiscard]] auto IsLogging() const -> bool;
  [[nodiscard]] auto GetFileLogLevel() const -> LogLevel;
  auto SetFileLogLevel(LogLevel lvl) -> void;
  [[nodiscard]] auto GetHandlersLogLevel() const -> LogLevel;
  auto SetHandlersLogLevel(LogLevel lvl) -> void;
  auto Log(LogLevel lvl, int lineNum, const std::string& funcName, const std::string& msg) -> void;
  template<typename... Args>
  auto Log(LogLevel lvl,
           int lineNum,
           const std::string& funcName,
           const std::string& formatStr,
           const Args&... args) -> void;

private:
  Logging() noexcept;
  LogLevel m_cutoffFileLogLevel     = LogLevel::INFO;
  LogLevel m_cutoffHandlersLogLevel = LogLevel::INFO;
  bool m_doDateTime                 = true;
  bool m_doLogging                  = false;
  std::string m_logFile{};
  std::vector<std::pair<std::string, HandlerFunc>> m_handlers{};
  std::vector<std::string> m_logEntries{};
  std::mutex m_mutex{};
  static std::unique_ptr<Logging> logger;
  auto DoFlush() -> void;
  auto VLog(LogLevel lvl,
            int lineNum,
            const std::string& funcName,
            const std::string& formatStr,
            std20::format_args args) -> void;
};

inline auto Logging::GetFileLogLevel() const -> Logging::LogLevel
{
  return m_cutoffFileLogLevel;
}

inline auto Logging::GetHandlersLogLevel() const -> Logging::LogLevel
{
  return m_cutoffHandlersLogLevel;
}

inline auto Logging::SetLogFile(const std::string& logF) -> void
{
  m_logFile = logF;
}

inline auto Logging::Suspend() -> void
{
  m_doLogging = false;
}
inline auto Logging::Resume() -> void
{
  m_doLogging = true;
}
inline auto Logging::IsLogging() const -> bool
{
  return m_doLogging;
}
inline auto Logging::GetLogger() -> Logging&
{
  return *logger;
}

template<typename... Args>
auto Logging::Log(LogLevel lvl,
                  const int lineNum,
                  const std::string& funcName,
                  const std::string& formatStr,
                  const Args&... args) -> void
{
  VLog(lvl, lineNum, funcName, formatStr, std20::make_format_args(args...));
}

#ifdef NO_LOGGING
//#pragma message("Compiling " __FILE__ " with 'NO_LOGGING' = 'ON' - SO THERE WILL BE NO LOGGING.")
#define SetLogFile(logF)
#define AddLogHandler(name, h)
#define SetLogDoDateTime(val)
#define LogStart()
#define LogStop()
#define LogFlush()
#define LogSuspend()
#define LogResume()
#define IsLogging() false
#define GetLogLevel()
#define SetLogLevel(lvl)
#define LogDebug(...)
#define LogInfo(...)
#define LogWarn(...)
#define LogError(...)
#else
#pragma message("Compiling " __FILE__ " with 'NO_LOGGING' = 'OFF' - SO THERE WILL BE LOGGING.")
#define SetLogFile(logF) Logging::GetLogger().SetLogFile(logF)
#define AddLogHandler(name, h) Logging::GetLogger().AddHandler(name, h)
#define SetLogDoDateTime(val) Logging::GetLogger().SetDoDateTime(val)
#define LogStart() Logging::GetLogger().Start()
#define LogStop() Logging::GetLogger().Stop()
#define LogFlush() Logging::GetLogger().Flush()
#define lLogSuspend() Logging::GetLogger().Suspend()
#define LogResume() Logging::GetLogger().Resume()
#define IsLogging() Logging::GetLogger().IsLogging()
#define GetLogLevel() Logging::GetLogger().GetHandlersLogLevel()
#define SetLogLevel(lvl) Logging::GetLogger().SetHandlersLogLevel(lvl)
#define GetLogLevelForFiles() Logging::GetLogger().GetFileLogLevel()
#define SetLogLevelForFiles(lvl) Logging::GetLogger().SetFileLogLevel(lvl)
#define LogDebug(...) \
  Logging::GetLogger().Log(Logging::LogLevel::DEBUG, __LINE__, __func__, __VA_ARGS__)
#define LogInfo(...) \
  Logging::GetLogger().Log(Logging::LogLevel::INFO, __LINE__, __func__, __VA_ARGS__)
#define LogWarn(...) \
  Logging::GetLogger().Log(Logging::LogLevel::WARN, __LINE__, __func__, __VA_ARGS__)
#define LogError(...) \
  Logging::GetLogger().Log(Logging::LogLevel::L_ERROR, __LINE__, __func__, __VA_ARGS__)
#endif


} // namespace GOOM::UTILS

// NOLINTEND
