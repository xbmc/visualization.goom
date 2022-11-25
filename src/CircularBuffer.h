/*
 *  Copyright (C) 2019-2022 Team Kodi (https://kodi.tv)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

static constexpr int SILENCE_THRESHOLD = 8;

template<typename T>
class CircularBuffer
{
public:
  explicit CircularBuffer(const size_t size) : m_size{size}, m_buffer(size) {}

  [[nodiscard]] auto DataAvailable() const -> size_t { return m_used; }
  [[nodiscard]] auto FreeSpace() const -> size_t { return m_size - m_used; }

  auto Write(const T* srce, size_t count) -> bool
  {
    if (count > FreeSpace())
    {
      return false;
    }
    while (count)
    {
      size_t delta = m_size - m_writePtr;
      if (delta > count)
      {
        delta = count;
      }
      std::copy(srce, srce + delta, begin(m_buffer) + static_cast<std::ptrdiff_t>(m_writePtr));
      m_used += delta;
      m_writePtr = (m_writePtr + delta) % m_size;
      srce += delta;
      count -= delta;
    }
    return true;
  }

  [[nodiscard]] auto Read(T* dest, size_t count) -> size_t
  {
    size_t done = 0;
    for (;;)
    {
      size_t delta = m_size - m_readPtr;
      if (delta > m_used)
      {
        delta = m_used;
      }
      if (delta > count)
      {
        delta = count;
      }
      if (0 == delta)
      {
        break;
      }

      std::copy(cbegin(m_buffer) + static_cast<std::ptrdiff_t>(m_readPtr),
                cbegin(m_buffer) + static_cast<std::ptrdiff_t>(m_readPtr + delta),
                dest);

      dest += delta;
      done += delta;
      m_readPtr = (m_readPtr + delta) % m_size;
      count -= delta;
      m_used -= delta;
    }
    return done;
  }

  // TODO Make this a unit test
  /** Visual Studio not happy with this
  [[nodiscard]] auto TestSilence() const -> bool
  {
    auto* begin = static_cast<T*>(&m_buffer[0]);
    T first = *begin;
    *begin = SILENCE_THRESHOLD * 2;
    T* ptr = begin + m_size;
    while (static_cast<u_int32_t>((*--ptr + SILENCE_THRESHOLD) <=
                                  (static_cast<u_int32_t>(SILENCE_THRESHOLD) * 2)))
    {
    }
    *begin = first;
    return (ptr == begin) && (static_cast<u_int32_t>(first + SILENCE_THRESHOLD) <=
                              (static_cast<u_int32_t>(SILENCE_THRESHOLD) * 2));
  }
  **/

private:
  const size_t m_size;
  std::vector<T> m_buffer;
  size_t m_readPtr  = 0;
  size_t m_writePtr = 0;
  size_t m_used     = 0;
};
