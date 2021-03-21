#ifndef VISUALIZATION_GOOM_GOOM_STATES_H
#define VISUALIZATION_GOOM_GOOM_STATES_H

#include "goom_graphic.h"
#include "goomutils/goomrand.h"

#include <unordered_set>
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

enum class GoomDrawable
{
  IFS = 0,
  DOTS,
  TENTACLES,
  STARS,
  LINES,
  SCOPE,
  FAR_SCOPE,
  IMAGE,
  TUBE,
  _NUM // unused and must be last
};

class GoomStates
{
public:
  using DrawablesState = std::unordered_set<GoomDrawable>;

  GoomStates();

  [[nodiscard]] auto IsCurrentlyDrawable(GoomDrawable drawable) const -> bool;
  [[nodiscard]] auto GetCurrentStateIndex() const -> size_t;
  [[nodiscard]] auto GetCurrentDrawables() const -> DrawablesState;
  [[nodiscard]] auto GetCurrentBuffSettings(GoomDrawable theFx) const -> FXBuffSettings;

  void DoRandomStateChange();

private:
  struct DrawableInfo
  {
    GoomDrawable fx;
    FXBuffSettings buffSettings;
  };
  using DrawableInfoArray = std::vector<DrawableInfo>;
  struct State
  {
    uint32_t weight;
    bool normaliseBuffIntensity;
    DrawableInfoArray drawables;
  };
  using WeightedStatesArray = std::vector<State>;
  static WeightedStatesArray STATES;
  static void NormaliseStates();
  static auto GetWeightedStates(const WeightedStatesArray& theStates)
      -> std::vector<std::pair<uint16_t, size_t>>;
  const UTILS::Weights<uint16_t> m_weightedStates;
  size_t m_currentStateIndex = 0;
};

inline auto GoomStates::IsCurrentlyDrawable(const GoomDrawable drawable) const -> bool
{
#if __cplusplus <= 201402L
  return GetCurrentDrawables().find(drawable) != GetCurrentDrawables().end();
#else
  return GetCurrentDrawables().contains(drawable);
#endif
}

inline auto GoomStates::GetCurrentStateIndex() const -> size_t
{
  return m_currentStateIndex;
}

#if __cplusplus <= 201402L
} // namespace CONTROL
} // namespace GOOM
#else
} // namespace GOOM::CONTROL
#endif

#endif //VISUALIZATION_GOOM_GOOM_STATES_H
