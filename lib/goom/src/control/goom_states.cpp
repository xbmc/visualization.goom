#include "goom_states.h"

#include "goom_graphic.h"

#include <utility>
#include <vector>

#if __cplusplus <= 201402L
namespace GOOM
{
namespace CONTROL
{
#else
namespace GOOM::CONTROL
{
#endif

//@formatter:off
// clang-format off
GoomStates::WeightedStatesArray GoomStates::STATES{{
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IMAGE,     /*.buffSettings = */{ /*.buffIntensity = */0.8, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.8, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::TENTACLES,     /*.buffSettings = */{ /*.buffIntensity = */0.8, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
    }},
  },
  {
   /*.weight = */1,
   /*.normaliseBuffIntensity = */false,
   /*.drawables */{{
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */false  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */1.0, /*.allowOverexposed = */false  } },
    }},
  },
  {
    /*.weight = */1,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */false } },
  }},
 },
  {
    /*.weight = */200,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.1, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */200,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */200,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */200,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.4, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */200,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */100,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.6, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */20,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */60,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.4, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */70,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */70,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::IFS,       /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true } },
    }},
  },
  {
    /*.weight = */40,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.6, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */40,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.2, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */100,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.6, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.4, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */70,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.6, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
    }},
  },
  {
    /*.weight = */100,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::TENTACLES, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.4, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::IMAGE,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */60,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.4, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */60,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.7, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::STARS,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */false } },
      { /*.fx = */GoomDrawable::IMAGE,     /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */60,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
    }},
  },
  {
    /*.weight = */60,
    /*.normaliseBuffIntensity = */false,
    /*.drawables */{{
      { /*.fx = */GoomDrawable::DOTS,      /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::LINES,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::SCOPE,     /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::FAR_SCOPE, /*.buffSettings = */{ /*.buffIntensity = */0.5, /*.allowOverexposed = */true  } },
      { /*.fx = */GoomDrawable::TUBE,    /*.buffSettings = */{ /*.buffIntensity = */0.3, /*.allowOverexposed = */true  } },
    }},
 },
}};
// clang-format on
//@formatter:on

GoomStates::GoomStates() : m_weightedStates{GetWeightedStates(STATES)}
{
  NormaliseStates();
  DoRandomStateChange();
}

auto GoomStates::GetCurrentDrawables() const -> GoomStates::DrawablesState
{
  GoomStates::DrawablesState currentDrawables{};
  for (const auto d : STATES[m_currentStateIndex].drawables)
  {
    currentDrawables.insert(d.fx);
  }
  return currentDrawables;
}

auto GoomStates::GetCurrentBuffSettings(const GoomDrawable theFx) const -> FXBuffSettings
{
  for (const auto& d : STATES[m_currentStateIndex].drawables)
  {
    if (d.fx == theFx)
    {
      return d.buffSettings;
    }
  }
  return FXBuffSettings{};
}

void GoomStates::DoRandomStateChange()
{
  m_currentStateIndex = static_cast<size_t>(m_weightedStates.GetRandomWeighted());
}

void GoomStates::NormaliseStates()
{
  for (auto& state : STATES)
  {
    if (!state.normaliseBuffIntensity)
    {
      continue;
    }

    float totalBuffIntensity = 0.0;
    for (const auto& drawableInfo : state.drawables)
    {
      totalBuffIntensity += drawableInfo.buffSettings.buffIntensity;
    }
    if (totalBuffIntensity <= 1.0)
    {
      continue;
    }

    for (auto& drawableInfo : state.drawables)
    {
      drawableInfo.buffSettings.buffIntensity /= totalBuffIntensity;
    }
  }
}

auto GoomStates::GetWeightedStates(const GoomStates::WeightedStatesArray& theStates)
    -> std::vector<std::pair<uint16_t, size_t>>
{
  std::vector<std::pair<uint16_t, size_t>> weightedVals(theStates.size());
  for (size_t i = 0; i < theStates.size(); i++)
  {
    weightedVals[i] = std::make_pair(i, theStates[i].weight);
  }
  return weightedVals;
}

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif
