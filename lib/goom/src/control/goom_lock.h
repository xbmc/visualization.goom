#ifndef VISUALIZATION_GOOM_GOOM_LOCK_H
#define VISUALIZATION_GOOM_GOOM_LOCK_H

#include <cstdint>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace CONTROL
{
#else
namespace GOOM::CONTROL
{
#endif

/* note pour ceux qui n'ont pas suivis : le GoomLock permet d'empecher un */
/* changement d'etat du plugin juste apres un autre changement d'etat. oki */
// -- Note for those who have not followed: the GoomLock prevents a change
// of state of the plugin just after another change of state.
class GoomLock
{
public:
  GoomLock() noexcept = default;

  auto IsLocked() const -> bool;

  void Update();

  auto GetLockTime() const -> uint32_t;
  void SetLockTime(uint32_t val);
  void IncreaseLockTime(uint32_t byAmount);

private:
  int32_t m_lockTime = 0;
};

inline auto GoomLock::IsLocked() const -> bool
{
  return m_lockTime > 0;
}

inline void GoomLock::Update()
{
  m_lockTime--;
  if (m_lockTime < 0)
  {
    m_lockTime = 0;
  }
}

inline auto GoomLock::GetLockTime() const -> uint32_t
{
  return static_cast<uint32_t>(m_lockTime);
}

inline void GoomLock::SetLockTime(const uint32_t val)
{
  m_lockTime = static_cast<int32_t>(val);
}

inline void GoomLock::IncreaseLockTime(const uint32_t byAmount)
{
  m_lockTime += static_cast<int32_t>(byAmount);
}

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif

#endif //VISUALIZATION_GOOM_GOOM_LOCK_H
