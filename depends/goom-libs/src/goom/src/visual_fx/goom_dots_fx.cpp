#include "goom_dots_fx.h"

//#undef NO_LOGGING

#include "color/color_adjustment.h"
#include "color/color_maps.h"
#include "color/color_utils.h"
#include "color/random_color_maps.h"
#include "color/random_color_maps_manager.h"
#include "draw/goom_draw.h"
#include "fx_helper.h"
#include "goom_graphic.h"
#include "goom_plugin_info.h"
#include "logging.h"
#include "point2d.h"
#include "spimpl.h"
#include "utils/graphics/image_bitmaps.h"
#include "utils/graphics/small_image_bitmaps.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"
#include "utils/math/paths.h"
#include "utils/t_values.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <memory>

namespace GOOM::VISUAL_FX
{

using COLOR::ColorAdjustment;
using COLOR::ColorMapGroup;
using COLOR::RandomColorMaps;
using COLOR::RandomColorMapsManager;
using DRAW::IGoomDraw;
using UTILS::Logging; // NOLINT(misc-unused-using-decls)
using UTILS::TValue;
using UTILS::GRAPHICS::ImageBitmap;
using UTILS::GRAPHICS::SmallImageBitmaps;
using UTILS::MATH::AngleParams;
using UTILS::MATH::EpicycloidFunction;
using UTILS::MATH::EpicycloidPath;
using UTILS::MATH::HypotrochoidFunction;
using UTILS::MATH::HypotrochoidPath;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::IPath;
using UTILS::MATH::LissajousFunction;
using UTILS::MATH::LissajousPath;
using UTILS::MATH::U_HALF;
using UTILS::MATH::Weights;

class GoomDotsFx::GoomDotsFxImpl
{
public:
  GoomDotsFxImpl(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps);

  auto Start() -> void;

  [[nodiscard]] auto GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>;
  auto SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void;
  auto SetSingleBufferDots(bool val) noexcept -> void;

  auto ApplySingle() -> void;
  auto ApplyMultiple() -> void;

private:
  IGoomDraw& m_draw;
  const PluginInfo& m_goomInfo;
  const IGoomRand& m_goomRand;
  const SmallImageBitmaps& m_smallBitmaps;
  const Point2dInt m_screenMidpoint{U_HALF * m_goomInfo.GetScreenWidth(),
                                    U_HALF* m_goomInfo.GetScreenHeight()};

  SmallImageBitmaps::ImageNames m_currentBitmapName{};
  static constexpr uint32_t MAX_FLOWERS_IN_ROW = 100;
  uint32_t m_numFlowersInRow                   = 0;
  const Weights<SmallImageBitmaps::ImageNames> m_flowerDotTypes;
  [[nodiscard]] auto GetImageBitmap(uint32_t size) const -> const ImageBitmap&;
  void SetFlowerBitmap();
  void SetNonFlowerBitmap();
  void SetNextCurrentBitmapName();
  [[nodiscard]] auto ChangeDotColorsEvent() const -> bool;

  static constexpr auto MIN_DOT_SIZE = 5U;
  static constexpr auto MAX_DOT_SIZE = 17U;
  static_assert(MAX_DOT_SIZE <= SmallImageBitmaps::MAX_IMAGE_SIZE, "Max dot size mismatch.");

  std::array<std::shared_ptr<const RandomColorMaps>, NUM_DOT_TYPES> m_dotColorMapsList{};
  RandomColorMapsManager m_colorMapsManager{};
  std::array<RandomColorMapsManager::ColorMapId, NUM_DOT_TYPES> m_colorMapIds{
      GetDefaultColorMapIds()};
  [[nodiscard]] auto GetDefaultColorMapIds() noexcept
      -> std::array<RandomColorMapsManager::ColorMapId, NUM_DOT_TYPES>;
  std::array<bool, NUM_DOT_TYPES> m_usePrimaryColors{};
  Pixel m_middleColor{};
  bool m_useSingleBuffer              = true;
  bool m_currentlyUseSingleBufferOnly = true;
  bool m_thereIsOneBuffer             = true;
  bool m_useMiddleColor               = true;
  [[nodiscard]] auto GetDotColor(size_t dotNum, float t) const -> Pixel;
  [[nodiscard]] static auto GetDotPrimaryColor(size_t dotNum) -> Pixel;
  [[nodiscard]] static auto IsImagePointCloseToMiddle(size_t x, size_t y, uint32_t radius) -> bool;
  [[nodiscard]] static auto GetMargin(uint32_t radius) -> size_t;
  [[nodiscard]] auto GetMiddleColor() const -> Pixel;

  const std::array<std::unique_ptr<IPath>, NUM_DOT_TYPES> m_dotPaths{GetDotPaths(m_screenMidpoint)};
  [[nodiscard]] static auto GetDotPaths(const Point2dInt& centre)
      -> std::array<std::unique_ptr<IPath>, NUM_DOT_TYPES>;

  void Update();

  void ChangeColors();

  void DotFilter(const Pixel& color, const Point2dInt& dotPosition, uint32_t radius);

  static constexpr auto GAMMA = 2.2F;  // Cancel the shader gamma
  const ColorAdjustment m_colorAdjust{GAMMA, ColorAdjustment::INCREASED_CHROMA_FACTOR};
};

GoomDotsFx::GoomDotsFx(const FxHelper& fxHelper, const SmallImageBitmaps& smallBitmaps) noexcept
  : m_pimpl{spimpl::make_unique_impl<GoomDotsFxImpl>(fxHelper, smallBitmaps)}
{
}

auto GoomDotsFx::GetCurrentColorMapsNames() const noexcept -> std::vector<std::string>
{
  return m_pimpl->GetCurrentColorMapsNames();
}

auto GoomDotsFx::SetWeightedColorMaps(const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  m_pimpl->SetWeightedColorMaps(weightedColorMaps);
}

auto GoomDotsFx::SetSingleBufferDots(const bool val) noexcept -> void
{
  m_pimpl->SetSingleBufferDots(val);
}

auto GoomDotsFx::Start() noexcept -> void
{
  m_pimpl->Start();
}

auto GoomDotsFx::Finish() noexcept -> void
{
  // nothing to do
}

auto GoomDotsFx::Resume() noexcept -> void
{
  // nothing to do
}

auto GoomDotsFx::Suspend() noexcept -> void
{
  // nothing to do
}

auto GoomDotsFx::GetFxName() const noexcept -> std::string
{
  return "goom dots";
}

auto GoomDotsFx::ApplySingle() noexcept -> void
{
  m_pimpl->ApplySingle();
}

auto GoomDotsFx::ApplyMultiple() noexcept -> void
{
  m_pimpl->ApplyMultiple();
}

static constexpr auto IMAGE_NAMES_ORANGE_FLOWER_WEIGHT = 10.0F;
static constexpr auto IMAGE_NAMES_PINK_FLOWER_WEIGHT   = 05.0F;
static constexpr auto IMAGE_NAMES_RED_FLOWER_WEIGHT    = 10.0F;
static constexpr auto IMAGE_NAMES_WHITE_FLOWER_WEIGHT  = 05.0F;

GoomDotsFx::GoomDotsFxImpl::GoomDotsFxImpl(const FxHelper& fxHelper,
                                           const SmallImageBitmaps& smallBitmaps)
  : m_draw{fxHelper.GetDraw()},
    m_goomInfo{fxHelper.GetGoomInfo()},
    m_goomRand{fxHelper.GetGoomRand()},
    m_smallBitmaps{smallBitmaps},
    m_flowerDotTypes{
        m_goomRand,
        {
            {SmallImageBitmaps::ImageNames::ORANGE_FLOWER, IMAGE_NAMES_ORANGE_FLOWER_WEIGHT},
            {SmallImageBitmaps::ImageNames::PINK_FLOWER,   IMAGE_NAMES_PINK_FLOWER_WEIGHT},
            {SmallImageBitmaps::ImageNames::RED_FLOWER,    IMAGE_NAMES_RED_FLOWER_WEIGHT},
            {SmallImageBitmaps::ImageNames::WHITE_FLOWER,  IMAGE_NAMES_WHITE_FLOWER_WEIGHT},
        }
    }
{
}

auto GoomDotsFx::GoomDotsFxImpl::GetDefaultColorMapIds() noexcept
    -> std::array<RandomColorMapsManager::ColorMapId, NUM_DOT_TYPES>
{
  auto colorMapsIds = std::array<RandomColorMapsManager::ColorMapId, NUM_DOT_TYPES>{};

  for (auto& colorMapsId : colorMapsIds)
  {
    colorMapsId = m_colorMapsManager.AddDefaultColorMapInfo(m_goomRand);
  }

  return colorMapsIds;
}

auto GoomDotsFx::GoomDotsFxImpl::GetDotPaths(const Point2dInt& centre)
    -> std::array<std::unique_ptr<IPath>, NUM_DOT_TYPES>
{
  static constexpr auto HYPOTROCHOID_PARAMS1 =
      HypotrochoidFunction::Params{7.0F, 3.0F, 5.0F, 30.0F};
  static constexpr auto HYPOTROCHOID_PARAMS2 =
      HypotrochoidFunction::Params{8.0F, 3.0F, 5.0F, 30.0F};
  static constexpr auto HYPOTROCHOID_PARAMS3 =
      HypotrochoidFunction::Params{9.0F, 3.0F, 5.0F, 30.0F};
  static constexpr auto LISSAJOUS_PATH_PARAMS = LissajousFunction::Params{50.0F, 50.F, 3.0F, 2.0F};
  static constexpr auto EPICYCLOID_PARAMS     = EpicycloidFunction::Params{5.1F, 1.0F, 30.0F};

  static constexpr auto STEP_TYPE              = TValue::StepType::CONTINUOUS_REVERSIBLE;
  static constexpr auto HYPOTROCHOID_STEP_SIZE = 0.01F;
  static constexpr auto LISSAJOUS_STEP_SIZE    = 0.01F;
  static constexpr auto EPICYCLOID_STEP_SIZE   = 0.001F;

  auto hypotrochoidPositionT1 = std::make_unique<TValue>(STEP_TYPE, HYPOTROCHOID_STEP_SIZE);
  auto hypotrochoidPositionT2 = std::make_unique<TValue>(STEP_TYPE, HYPOTROCHOID_STEP_SIZE);
  auto hypotrochoidPositionT3 = std::make_unique<TValue>(STEP_TYPE, HYPOTROCHOID_STEP_SIZE);
  auto lissajousPositionT     = std::make_unique<TValue>(STEP_TYPE, LISSAJOUS_STEP_SIZE);
  auto epicycloidPositionT    = std::make_unique<TValue>(STEP_TYPE, EPICYCLOID_STEP_SIZE);

  const auto centrePos                       = Vec2dFlt{centre.ToFlt()};
  static constexpr auto DEFAULT_ANGLE_PARAMS = AngleParams{};

  return {
      {std::make_unique<HypotrochoidPath>(std::move(hypotrochoidPositionT1),
       centrePos, DEFAULT_ANGLE_PARAMS,
       HYPOTROCHOID_PARAMS1),
       std::make_unique<HypotrochoidPath>(std::move(hypotrochoidPositionT2),
       centrePos, DEFAULT_ANGLE_PARAMS,
       HYPOTROCHOID_PARAMS2),
       std::make_unique<HypotrochoidPath>(std::move(hypotrochoidPositionT3),
       centrePos, DEFAULT_ANGLE_PARAMS,
       HYPOTROCHOID_PARAMS3),
       std::make_unique<LissajousPath>(
       std::move(lissajousPositionT), centrePos, DEFAULT_ANGLE_PARAMS, LISSAJOUS_PATH_PARAMS),
       std::make_unique<EpicycloidPath>(
       std::move(epicycloidPositionT), centrePos, DEFAULT_ANGLE_PARAMS, EPICYCLOID_PARAMS)}
  };
}

inline auto GoomDotsFx::GoomDotsFxImpl::ChangeDotColorsEvent() const -> bool
{
  static constexpr auto PROB_CHANGE_DOT_COLORS = 0.33F;
  return m_goomRand.ProbabilityOf(PROB_CHANGE_DOT_COLORS);
}

inline void GoomDotsFx::GoomDotsFxImpl::Start()
{
  ChangeColors();
}

inline auto GoomDotsFx::GoomDotsFxImpl::GetImageBitmap(const uint32_t size) const
    -> const ImageBitmap&
{
  return m_smallBitmaps.GetImageBitmap(m_currentBitmapName,
                                       std::clamp(size, MIN_DOT_SIZE, MAX_DOT_SIZE));
}

inline void GoomDotsFx::GoomDotsFxImpl::ChangeColors()
{
  m_colorMapsManager.ChangeAllColorMapsNow();

  for (auto& usePrimaryColor : m_usePrimaryColors)
  {
    static constexpr auto PROB_USE_PRIMARY_COLOR = 0.5F;
    usePrimaryColor                              = m_goomRand.ProbabilityOf(PROB_USE_PRIMARY_COLOR);
  }

  static constexpr auto PROB_USE_SINGLE_BUFFER_ONLY = 0.0F / 2.0F;
  m_currentlyUseSingleBufferOnly = m_goomRand.ProbabilityOf(PROB_USE_SINGLE_BUFFER_ONLY);

  static constexpr auto PROB_USE_MIDDLE_COLOR = 0.05F;
  m_useMiddleColor                            = m_goomRand.ProbabilityOf(PROB_USE_MIDDLE_COLOR);
  if (m_useMiddleColor)
  {
    m_middleColor = GetMiddleColor();
  }
}

auto GoomDotsFx::GoomDotsFxImpl::GetMiddleColor() const -> Pixel
{
  if (static constexpr auto PROB_PRIMARY_COLOR = 0.1F; m_goomRand.ProbabilityOf(PROB_PRIMARY_COLOR))
  {
    return GetDotPrimaryColor(m_goomRand.GetRandInRange(0U, NUM_DOT_TYPES));
  }

  static constexpr auto MIN_MIX_T = 0.1F;
  static constexpr auto MAX_MIX_T = 1.0F;
  return RandomColorMaps::GetRandomColor(
      m_goomRand,
      *m_dotColorMapsList[0]->GetRandomColorMapPtr(ColorMapGroup::MISC,
                                                   RandomColorMaps::ALL_COLOR_MAP_TYPES),
      MIN_MIX_T,
      MAX_MIX_T);
}

inline auto GoomDotsFx::GoomDotsFxImpl::GetCurrentColorMapsNames() const noexcept
    -> std::vector<std::string>
{
  return {m_dotColorMapsList.at(0)->GetColorMapsName()};
}

auto GoomDotsFx::GoomDotsFxImpl::SetWeightedColorMaps(
    const WeightedColorMaps& weightedColorMaps) noexcept -> void
{
  Expects(weightedColorMaps.mainColorMaps != nullptr);

  const auto dotNum = weightedColorMaps.id;

  m_dotColorMapsList.at(dotNum) = weightedColorMaps.mainColorMaps;
  m_colorMapsManager.UpdateColorMapInfo(
      m_colorMapIds.at(dotNum),
      {m_dotColorMapsList.at(dotNum), RandomColorMaps::ALL_COLOR_MAP_TYPES});
}

inline auto GoomDotsFx::GoomDotsFxImpl::SetSingleBufferDots(const bool val) noexcept -> void
{
  m_useSingleBuffer = val;
}

inline void GoomDotsFx::GoomDotsFxImpl::ApplySingle()
{
  if (not m_useSingleBuffer)
  {
    return;
  }

  m_thereIsOneBuffer = true;
  Update();
}

inline void GoomDotsFx::GoomDotsFxImpl::ApplyMultiple()
{
  if (m_useSingleBuffer)
  {
    return;
  }

  m_thereIsOneBuffer = false;
  Update();
}

void GoomDotsFx::GoomDotsFxImpl::Update()
{
  auto radius = MIN_DOT_SIZE / 2U;
  if ((0 == m_goomInfo.GetSoundEvents().GetTimeSinceLastGoom()) || ChangeDotColorsEvent())
  {
    ChangeColors();
    radius = m_goomRand.GetRandInRange(radius, (U_HALF * MAX_DOT_SIZE) + 1);
    SetNextCurrentBitmapName();
  }

  const auto speedFactor = 0.35F * m_goomInfo.GetSoundEvents().GetSoundInfo().GetSpeed();
  //  const auto largeFactor = GetLargeSoundFactor(m_goomInfo.GetSoundInfo());
  const auto speedVarMult80Plus15 = static_cast<uint32_t>((speedFactor * 80.0F) + 15.0F);

  const auto speedVarMult80Plus15Div15 = speedVarMult80Plus15 / 15;
  static constexpr auto T_MIN          = 0.1F;
  static constexpr auto T_MAX          = 1.0F;
  const auto tStep = (T_MAX - T_MIN) / static_cast<float>(speedVarMult80Plus15Div15);

  auto t = T_MIN;
  for (auto i = 1U; i <= speedVarMult80Plus15Div15; ++i)
  {
    for (auto dotNum = 0U; dotNum < NUM_DOT_TYPES; ++dotNum)
    {
      const auto dotColor    = GetDotColor(dotNum, t);
      const auto dotPosition = m_dotPaths.at(dotNum)->GetNextPoint();
      m_dotPaths.at(dotNum)->IncrementT();
      DotFilter(dotColor, dotPosition, radius);
    }

    t += tStep;
  }
}

inline auto GoomDotsFx::GoomDotsFxImpl::GetDotColor(const size_t dotNum, const float t) const
    -> Pixel
{
  if (m_usePrimaryColors.at(dotNum))
  {
    return GetDotPrimaryColor(dotNum);
  }

  return m_colorMapsManager.GetColorMap(m_colorMapIds.at(dotNum)).GetColor(t);
}

inline auto GoomDotsFx::GoomDotsFxImpl::GetDotPrimaryColor(const size_t dotNum) -> Pixel
{
  static const auto s_PRIMARY_COLORS = std::array{
      Pixel{255,   0,   0, 0},
      Pixel{  0, 255,   0, 0},
      Pixel{  0,   0, 255, 0},
      Pixel{255, 255,   0, 0},
      Pixel{  0, 255, 255, 0},
  };
  return s_PRIMARY_COLORS.at(dotNum);
}

inline void GoomDotsFx::GoomDotsFxImpl::SetNextCurrentBitmapName()
{
  static constexpr auto PROB_MORE_FLOWERS = 1.0F / 50.0F;

  if (m_numFlowersInRow > 0)
  {
    SetFlowerBitmap();
  }
  else if (m_goomRand.ProbabilityOf(PROB_MORE_FLOWERS))
  {
    m_numFlowersInRow = 1;
    SetNextCurrentBitmapName();
  }
  else
  {
    SetNonFlowerBitmap();
  }
}

inline void GoomDotsFx::GoomDotsFxImpl::SetFlowerBitmap()
{
  ++m_numFlowersInRow;
  if (m_numFlowersInRow > MAX_FLOWERS_IN_ROW)
  {
    m_numFlowersInRow = 0;
  }

  m_currentBitmapName = m_flowerDotTypes.GetRandomWeighted();
}

inline void GoomDotsFx::GoomDotsFxImpl::SetNonFlowerBitmap()
{
  static constexpr auto PROB_SPHERE = 0.7F;

  if (m_goomRand.ProbabilityOf(PROB_SPHERE))
  {
    m_currentBitmapName = SmallImageBitmaps::ImageNames::SPHERE;
  }
  else
  {
    m_currentBitmapName = SmallImageBitmaps::ImageNames::CIRCLE;
  }
}

void GoomDotsFx::GoomDotsFxImpl::DotFilter(const Pixel& color,
                                           const Point2dInt& dotPosition,
                                           const uint32_t radius)
{
  const auto diameter = (2 * radius) + 1; // must be odd
  const auto screenWidthLessDiameter =
      static_cast<int32_t>(m_goomInfo.GetScreenWidth() - diameter);
  const auto screenHeightLessDiameter =
      static_cast<int32_t>(m_goomInfo.GetScreenHeight() - diameter);

  if ((dotPosition.x < static_cast<int32_t>(diameter)) ||
      (dotPosition.y < static_cast<int32_t>(diameter)) ||
      (dotPosition.x >= screenWidthLessDiameter) || (dotPosition.y >= screenHeightLessDiameter))
  {
    return;
  }

  static constexpr auto BRIGHTNESS = 3.5F;
  const auto getColor1 = [this, &radius, &color](const size_t x, const size_t y, const Pixel& bgnd)
  {
    if (0 == bgnd.A())
    {
      return BLACK_PIXEL;
    }
    const auto newColor =
        m_useMiddleColor && IsImagePointCloseToMiddle(x, y, radius) ? m_middleColor : color;
    static constexpr auto COLOR_MIX_T = 0.6F;
    const auto mixedColor             = COLOR::IColorMap::GetColorMix(bgnd, newColor, COLOR_MIX_T);
    return m_colorAdjust.GetAdjustment(BRIGHTNESS, mixedColor);
  };
  const auto getColor2 = [&getColor1]([[maybe_unused]] const size_t x,
                                      [[maybe_unused]] const size_t y,
                                      [[maybe_unused]] const Pixel& bgnd)
  { return getColor1(x, y, bgnd); };

  if (const auto midPoint = Point2dInt{dotPosition.x + static_cast<int32_t>(radius),
                                       dotPosition.y + static_cast<int32_t>(radius)};
      m_thereIsOneBuffer || m_currentlyUseSingleBufferOnly)
  {
    m_draw.Bitmap(midPoint, GetImageBitmap(diameter), getColor1);
  }
  else
  {
    m_draw.Bitmap(midPoint, GetImageBitmap(diameter), {getColor1, getColor2});
  }
}

inline auto GoomDotsFx::GoomDotsFxImpl::IsImagePointCloseToMiddle(const size_t x,
                                                                  const size_t y,
                                                                  const uint32_t radius) -> bool
{
  const auto margin = GetMargin(radius);
  const auto minVal = radius - margin;
  const auto maxVal = radius + margin;
  return (minVal <= x) && (x <= maxVal) && (minVal <= y) && (y <= maxVal);
}

inline auto GoomDotsFx::GoomDotsFxImpl::GetMargin(const uint32_t radius) -> size_t
{
  static constexpr auto SMALLEST_MARGIN = 2U;
  if (static constexpr auto SMALL_RADIUS = 7U; radius < SMALL_RADIUS)
  {
    return SMALLEST_MARGIN;
  }
  return SMALLEST_MARGIN + 1;
}

} // namespace GOOM::VISUAL_FX
