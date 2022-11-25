#pragma once

#include "goom_config.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"

#include <array>
#include <string_view>
#include <vector>

namespace GOOM::CONTROL
{

enum class GoomStates : size_t
{
  CIRCLES_ONLY = 0,
  CIRCLES_IFS,
  CIRCLES_IMAGE,
  CIRCLES_IMAGE_STARS,
  CIRCLES_LINES,
  CIRCLES_STARS_TUBES,
  CIRCLES_TENTACLES,
  DOTS_IFS,
  DOTS_IFS_STARS,
  DOTS_IMAGE_STARS,
  DOTS_LINES,
  DOTS_LINES_STARS_TENTACLES,
  DOTS_LINES_TENTACLES_TUBES,
  DOTS_LINES_TUBES,
  DOTS_ONLY,
  DOTS_STARS,
  DOTS_STARS_TENTACLES_TUBES,
  DOTS_TENTACLES_TUBES,
  IFS_IMAGE,
  IFS_IMAGE_SHAPES,
  IFS_LINES_STARS,
  IFS_ONLY,
  IFS_SHAPES,
  IFS_STARS,
  IFS_STARS_TENTACLES,
  IFS_TENTACLES,
  IFS_TENTACLES_TUBES,
  IFS_TUBES,
  IMAGE_LINES,
  IMAGE_LINES_SHAPES,
  IMAGE_LINES_STARS_TENTACLES,
  IMAGE_ONLY,
  IMAGE_SHAPES,
  IMAGE_SHAPES_STARS,
  IMAGE_SHAPES_TUBES,
  IMAGE_STARS,
  IMAGE_TENTACLES,
  IMAGE_TUBES,
  LINES_ONLY,
  LINES_SHAPES_STARS,
  LINES_STARS,
  LINES_TENTACLES,
  SHAPES_ONLY,
  SHAPES_STARS,
  SHAPES_TUBES,
  STARS_ONLY,
  TENTACLES_ONLY,
  TUBES_ONLY,
  _num // unused, and marks the enum end
};

enum class GoomDrawables
{
  CIRCLES = 0,
  DOTS,
  IFS,
  LINES,
  IMAGE,
  SHAPES,
  STARS,
  TENTACLES,
  TUBES,
  _num // unused, and marks the enum end
};

using BuffIntensityRange = UTILS::MATH::IGoomRand::NumberRange<float>;

class GoomStateInfo
{
public:
  struct DrawableInfo
  {
    GoomDrawables fx{};
    BuffIntensityRange buffIntensityRange{};
  };
  struct StateInfo
  {
    std::string_view name;
    std::vector<DrawableInfo> drawablesInfo;
  };

  GoomStateInfo() noexcept = delete;

  [[nodiscard]] static auto GetStateInfo(GoomStates goomState) -> const StateInfo&;
  [[nodiscard]] static auto GetBuffIntensityRange(GoomStates goomState, GoomDrawables fx)
      -> BuffIntensityRange;
  [[nodiscard]] static auto IsMultiThreaded(GoomStates goomState) -> bool;

private:
  using StateInfoMap = UTILS::EnumMap<GoomStates, StateInfo>;
  static const StateInfoMap STATE_INFO_MAP;
  [[nodiscard]] static auto GetStateInfoMap() noexcept -> StateInfoMap;
  [[nodiscard]] static auto GetDrawablesInfo(GoomStates goomState) -> std::vector<DrawableInfo>;
};

inline auto GoomStateInfo::GetStateInfo(const GoomStates goomState) -> const StateInfo&
{
  return STATE_INFO_MAP[goomState];
}

} // namespace GOOM::CONTROL
