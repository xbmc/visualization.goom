#pragma once

#include "goom_states.h"

#include <unordered_set>

namespace GOOM::CONTROL
{

class IGoomStateHandler
{
public:
  using DrawablesState = std::unordered_set<GoomDrawables>;

  IGoomStateHandler() noexcept                                   = default;
  IGoomStateHandler(const IGoomStateHandler&) noexcept           = delete;
  IGoomStateHandler(IGoomStateHandler&&) noexcept                = delete;
  virtual ~IGoomStateHandler() noexcept                          = default;
  auto operator=(const IGoomStateHandler&) -> IGoomStateHandler& = delete;
  auto operator=(IGoomStateHandler&&) -> IGoomStateHandler&      = delete;

  virtual void ChangeToNextState() = 0;

  [[nodiscard]] virtual auto GetCurrentState() const -> GoomStates = 0;
  [[nodiscard]] auto GetCurrentDrawables() const -> DrawablesState;
};

} // namespace GOOM::CONTROL
