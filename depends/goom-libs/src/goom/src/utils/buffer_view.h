#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

static_assert(__cplusplus >= 201703L, "c++ std too low");

namespace GOOM::UTILS
{

template<class T>
class BufferView
{
public:
  BufferView(size_t buffLen, const T* buff) noexcept;
  BufferView(const BufferView&)                   = delete;
  BufferView(BufferView&&) noexcept               = default;
  auto operator=(const BufferView&) -> BufferView = delete;
  auto operator=(BufferView&&) -> BufferView      = delete;
  virtual ~BufferView() noexcept                  = default;

  [[nodiscard]] auto Data() const -> const T*;
  auto operator[](size_t i) const -> const T&;

  [[nodiscard]] auto GetBufferLen() const -> size_t;
  [[nodiscard]] auto GetBufferSize() const -> size_t;

protected:
  BufferView() noexcept;
  void SetBuffer(size_t buffLen, const T* buff);

private:
  size_t m_buffLen  = 0;
  const T* m_buffer = nullptr;
};

template<class T>
inline BufferView<T>::BufferView() noexcept = default;

template<class T>
inline BufferView<T>::BufferView(size_t buffLen, const T* buff) noexcept
  : m_buffLen{buffLen}, m_buffer{buff}
{
}

template<class T>
void inline BufferView<T>::SetBuffer(size_t buffLen, const T* buff)
{
  m_buffLen = buffLen;
  m_buffer  = buff;
}

template<class T>
inline auto BufferView<T>::Data() const -> const T*
{
  return m_buffer;
}

template<class T>
inline auto BufferView<T>::operator[](size_t i) const -> const T&
{
  return m_buffer[i];
}

template<class T>
inline auto BufferView<T>::GetBufferLen() const -> size_t
{
  return m_buffLen;
}

template<class T>
inline auto BufferView<T>::GetBufferSize() const -> size_t
{
  return m_buffLen * sizeof(T);
}

} // namespace GOOM::UTILS
