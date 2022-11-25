#pragma once

#include "buffer_view.h"

#include <cstdint>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

namespace GOOM::UTILS
{

struct EmptyHeaderType
{
  int x;
};

template<class T, class HeaderT = EmptyHeaderType>
class BufferSaver
{
public:
  explicit BufferSaver(std::string filenamePrefix,
                       int64_t startBuffNum = 0,
                       int64_t endBuffNum   = 1000000);

  [[nodiscard]] auto GetCurrentFilename() const -> std::string;
  [[nodiscard]] auto GetCurrentBufferNum() const -> int64_t;
  [[nodiscard]] auto GetStartBufferNum() const -> int64_t;
  [[nodiscard]] auto GetEndBufferNum() const -> int64_t;
  [[nodiscard]] auto HaveFinishedBufferRange() const -> bool;

  void Write(const BufferView<T>& buffer, bool binaryFormat);
  void Write(const HeaderT& header, const BufferView<T>& buffer, bool binaryFormat);

  [[nodiscard]] auto PeekHeader(HeaderT& header, bool binaryFormat) -> bool;

  static void WriteBinary(const std::string& filename,
                          int64_t tag,
                          const HeaderT& header,
                          const BufferView<T>& buffer);
  static void WriteBinary(std::ostream& file,
                          int64_t tag,
                          const HeaderT& header,
                          const BufferView<T>& buffer);

  [[nodiscard]] static auto PeekHeaderBinary(const std::string& filename, HeaderT& header) -> bool;
  [[nodiscard]] static auto PeekHeaderBinary(std::istream& file, HeaderT& header) -> bool;

  static void WriteFormatted(std::ostream& file,
                             int64_t tag,
                             const HeaderT& header,
                             const BufferView<T>& buffer);
  static void WriteFormatted(const std::string& filename,
                             int64_t tag,
                             const HeaderT& header,
                             const BufferView<T>& buffer);

  [[nodiscard]] static auto PeekHeaderFormatted(const std::string& filename, HeaderT& header)
      -> bool;

protected:
  auto IncCurrentBufferNum() noexcept -> void;

private:
  const std::string m_filenamePrefix;
  const int64_t m_startBuffNum;
  const int64_t m_endBuffNum;
  int64_t m_currentBuffNum;
};

template<class T, class HeaderT>
inline BufferSaver<T, HeaderT>::BufferSaver(std::string filenamePrefix,
                                            const int64_t startBuffNum,
                                            const int64_t endBuffNum)
  : m_filenamePrefix{std::move(filenamePrefix)},
    m_startBuffNum{startBuffNum},
    m_endBuffNum{endBuffNum},
    m_currentBuffNum{startBuffNum}
{
}

template<class T, class HeaderT>
auto BufferSaver<T, HeaderT>::GetCurrentFilename() const -> std::string
{
  return std20::format("{}_{:05}", m_filenamePrefix, m_currentBuffNum);
}

template<class T, class HeaderT>
inline auto BufferSaver<T, HeaderT>::GetCurrentBufferNum() const -> int64_t
{
  return m_currentBuffNum;
}

template<class T, class HeaderT>
inline auto BufferSaver<T, HeaderT>::IncCurrentBufferNum() noexcept -> void
{
  ++m_currentBuffNum;
}

template<class T, class HeaderT>
inline auto BufferSaver<T, HeaderT>::GetStartBufferNum() const -> int64_t
{
  return m_startBuffNum;
}

template<class T, class HeaderT>
inline auto BufferSaver<T, HeaderT>::GetEndBufferNum() const -> int64_t
{
  return m_endBuffNum;
}

template<class T, class HeaderT>
inline auto BufferSaver<T, HeaderT>::HaveFinishedBufferRange() const -> bool
{
  return m_currentBuffNum > m_endBuffNum;
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::Write(const BufferView<T>& buffer, const bool binaryFormat)
{
  auto ignore = HeaderT{};
  Write(ignore, buffer, binaryFormat);
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::Write(const HeaderT& header,
                                    const BufferView<T>& buffer,
                                    const bool binaryFormat)
{
  if ((m_currentBuffNum < m_startBuffNum) || (m_currentBuffNum > m_endBuffNum))
  {
    return;
  }

  const auto filename = GetCurrentFilename();
  if (binaryFormat)
  {
    WriteBinary(filename, m_currentBuffNum, header, buffer);
  }
  else
  {
    WriteFormatted(filename, m_currentBuffNum, header, buffer);
  }
  ++m_currentBuffNum;
}

template<class T, class HeaderT>
auto BufferSaver<T, HeaderT>::PeekHeader(HeaderT& header, bool binaryFormat) -> bool
{
  if ((m_currentBuffNum < m_startBuffNum) || (m_currentBuffNum > m_endBuffNum))
  {
    return false;
  }

  const auto filename = GetCurrentFilename();
  const auto done =
      binaryFormat ? PeekHeaderBinary(filename, header) : PeekHeaderFormatted(filename, header);

  return done;
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::WriteBinary(const std::string& filename,
                                          const int64_t tag,
                                          const HeaderT& header,
                                          const BufferView<T>& buffer)
{
  auto file = std::ofstream{filename, std::ios::out | std::ios::binary};
  if (not file.good())
  {
    throw std::runtime_error(std20::format("Could not open file for writing: '{}'.", filename));
  }
  WriteBinary(file, tag, header, buffer);
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::WriteBinary(std::ostream& file,
                                          const int64_t tag,
                                          const HeaderT& header,
                                          const BufferView<T>& buffer)
{
  if (typeid(HeaderT) != typeid(EmptyHeaderType))
  {
    file.write(reinterpret_cast<const char*>(&header), sizeof(HeaderT));
  }

  const auto bufferLen = buffer.GetBufferLen();
  file.write(reinterpret_cast<const char*>(&tag), sizeof(tag));
  file.write(reinterpret_cast<const char*>(&bufferLen), sizeof(bufferLen));
  file.write(reinterpret_cast<const char*>(buffer.Data()),
             static_cast<std::streamsize>(bufferLen * sizeof(T)));
}

template<class T, class HeaderT>
auto BufferSaver<T, HeaderT>::PeekHeaderBinary(const std::string& filename, HeaderT& header) -> bool
{
  auto file = std::ifstream{filename, std::ios::in | std::ios::binary};
  if (not file.good())
  {
    return false;
  }
  return PeekHeaderBinary(file, header);
}

template<class T, class HeaderT>
auto BufferSaver<T, HeaderT>::PeekHeaderBinary(std::istream& file, HeaderT& header) -> bool
{
  if (typeid(HeaderT) != typeid(EmptyHeaderType))
  {
    HeaderT header1;
    file.read(reinterpret_cast<char*>(&header1), sizeof(HeaderT));
    header = header1;
    file.seekg(0);
  }
  return true;
}

template<class T, class HeaderT>
auto BufferSaver<T, HeaderT>::PeekHeaderFormatted(const std::string& filename,
                                                  [[maybe_unused]] HeaderT& header) -> bool
{
  [[maybe_unused]] auto file = std::ifstream{filename, std::ios::in};
  return false;
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::WriteFormatted(const std::string& filename,
                                             const int64_t tag,
                                             const HeaderT& header,
                                             const BufferView<T>& buffer)
{
  auto file = std::ofstream{filename, std::ios::out};
  WriteFormatted(file, tag, header, buffer);
}

template<class T, class HeaderT>
void BufferSaver<T, HeaderT>::WriteFormatted(std::ostream& file,
                                             const int64_t tag,
                                             [[maybe_unused]] const HeaderT& header,
                                             const BufferView<T>& buffer)
{
  if (typeid(HeaderT) != typeid(EmptyHeaderType))
  {
    throw std::runtime_error("Write formatted header not ready.");
  }

  file << "tag: " << tag << "\n";
  file << "bufferLen: " << buffer.GetBufferLen() << "\n";
  file << "bufferSize: " << (buffer.GetBufferLen() * sizeof(T)) << "\n";
  for (auto i = 0U; i < buffer.GetBufferLen(); ++i)
  {
    //    file << std20::format("{:#018x}", buffer[i]);
    file << std20::format("{}", buffer[i]);
    if (i < (buffer.GetBufferLen() - 1))
    {
      file << ", ";
    }
    file << "\n";
  }
  file << "\n";
}

} // namespace GOOM::UTILS
