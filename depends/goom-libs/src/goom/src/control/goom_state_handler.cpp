#include "goom_state_handler.h"

namespace GOOM::CONTROL
{

auto IGoomStateHandler::GetCurrentDrawables() const -> DrawablesState
{
  DrawablesState currentDrawables{};
  for (const auto drawableInfo : GoomStateInfo::GetStateInfo(GetCurrentState()).drawablesInfo)
  {
    currentDrawables.insert(drawableInfo.fx);
  }
  return currentDrawables;
}

} // namespace GOOM::CONTROL
