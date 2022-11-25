#include "filter_settings_service.h"

#include "after_effects/after_effects_states.h"
#include "filter_consts.h"
#include "filter_effects/zoom_vector_effects.h"
#include "filter_settings.h"
#include "goom_config.h"
#include "goom_plugin_info.h"
#include "utils/enum_utils.h"
#include "utils/math/goom_rand_base.h"
#include "utils/math/misc.h"

#include <array>
#include <stdexcept>
#include <vector>

namespace GOOM::FILTER_FX
{

using AFTER_EFFECTS::AfterEffectsStates;
using AFTER_EFFECTS::AfterEffectsTypes;
using AFTER_EFFECTS::HypercosOverlay;
using AFTER_EFFECTS::RotationAdjustments;
using FILTER_EFFECTS::ZoomVectorEffects;
using UTILS::EnumMap;
using UTILS::NUM;
using UTILS::MATH::IGoomRand;
using UTILS::MATH::U_HALF;
using UTILS::MATH::U_QUARTER;
using UTILS::MATH::U_THREE_QUARTERS;
using UTILS::MATH::Weights;


// For debugging:

//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::AMULET_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::CRYSTAL_BALL_MODE0;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::CRYSTAL_BALL_MODE1;
static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::DISTANCE_FIELD_MODE0;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::DISTANCE_FIELD_MODE1;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::DISTANCE_FIELD_MODE2;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::EXP_RECIPROCAL_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::HYPERCOS_MODE0;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::HYPERCOS_MODE1;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::HYPERCOS_MODE2;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::HYPERCOS_MODE3;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::IMAGE_DISPLACEMENT_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::NORMAL_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::SCRUNCH_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::SPEEDWAY_MODE0;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::SPEEDWAY_MODE1;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::SPEEDWAY_MODE2;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::WAVE_MODE0;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::WAVE_MODE1;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::WATER_MODE;
//static constexpr auto FORCED_FILTER_MODE = ZoomFilterMode::Y_ONLY_MODE;

//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::BLOCK_WAVY;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::HYPERCOS;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::IMAGE_VELOCITY;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::NOISE;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::PLANES;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::ROTATION;
//static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::TAN_EFFECT;
static constexpr auto FORCED_AFTER_EFFECTS_TYPE = AfterEffectsTypes::XY_LERP_EFFECT;

// End debugging


static constexpr auto PROB_HIGH = 0.9F;
static constexpr auto PROB_HALF = 0.5F;
static constexpr auto PROB_LOW  = 0.1F;
static constexpr auto PROB_ZERO = 0.0F;

static constexpr auto PROB_CRYSTAL_BALL_IN_MIDDLE = 0.8F;
static constexpr auto PROB_WAVE_IN_MIDDLE         = 0.5F;
static constexpr auto PROB_CHANGE_SPEED           = 0.5F;
static constexpr auto PROB_REVERSE_SPEED          = 0.5F;

static constexpr auto AMULET_MODE_WEIGHT             = 10.0F;
static constexpr auto CRYSTAL_BALL_MODE0_WEIGHT      = 04.0F;
static constexpr auto CRYSTAL_BALL_MODE1_WEIGHT      = 02.0F;
static constexpr auto DISTANCE_FIELD_MODE0_WEIGHT    = 03.0F;
static constexpr auto DISTANCE_FIELD_MODE1_WEIGHT    = 03.0F;
static constexpr auto DISTANCE_FIELD_MODE2_WEIGHT    = 02.0F;
static constexpr auto EXP_RECIPROCAL_MODE_WEIGHT     = 10.0F;
static constexpr auto HYPERCOS_MODE0_WEIGHT          = 08.0F;
static constexpr auto HYPERCOS_MODE1_WEIGHT          = 04.0F;
static constexpr auto HYPERCOS_MODE2_WEIGHT          = 02.0F;
static constexpr auto HYPERCOS_MODE3_WEIGHT          = 01.0F;
static constexpr auto IMAGE_DISPLACEMENT_MODE_WEIGHT = 05.0F;
static constexpr auto NORMAL_MODE_WEIGHT             = 10.0F;
static constexpr auto SCRUNCH_MODE_WEIGHT            = 06.0F;
static constexpr auto SPEEDWAY_MODE0_WEIGHT          = 02.0F;
static constexpr auto SPEEDWAY_MODE1_WEIGHT          = 01.0F;
static constexpr auto SPEEDWAY_MODE2_WEIGHT          = 05.0F;
static constexpr auto WAVE_MODE0_WEIGHT              = 05.0F;
static constexpr auto WAVE_MODE1_WEIGHT              = 04.0F;
static constexpr auto WATER_MODE_WEIGHT              = 00.0F;
static constexpr auto Y_ONLY_MODE_WEIGHT             = 05.0F;

static constexpr auto BOTTOM_MID_POINT_WEIGHT               = 03.0F;
static constexpr auto TOP_MID_POINT_WEIGHT                  = 03.0F;
static constexpr auto LEFT_MID_POINT_WEIGHT                 = 02.0F;
static constexpr auto RIGHT_MID_POINT_WEIGHT                = 02.0F;
static constexpr auto CENTRE_MID_POINT_WEIGHT               = 18.0F;
static constexpr auto TOP_LEFT_QUARTER_MID_POINT_WEIGHT     = 10.0F;
static constexpr auto TOP_RIGHT_QUARTER_MID_POINT_WEIGHT    = 10.0F;
static constexpr auto BOTTOM_LEFT_QUARTER_MID_POINT_WEIGHT  = 10.0F;
static constexpr auto BOTTOM_RIGHT_QUARTER_MID_POINT_WEIGHT = 10.0F;

// TODO(glk) - When we get to use C++20, replace the below 'inline consts' with 'static constexpr'.

inline const auto CRYSTAL_BALL_MODE0_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::CRYSTAL_BALL_MODE0, 0.0F},
    {ZoomFilterMode::CRYSTAL_BALL_MODE1, 0.0F},
};
inline const auto CRYSTAL_BALL_MODE1_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::CRYSTAL_BALL_MODE0, 0.0F},
    {ZoomFilterMode::CRYSTAL_BALL_MODE1, 0.0F},
};
inline const auto NORMAL_MODE_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {         ZoomFilterMode::NORMAL_MODE, 1.0F},
    {ZoomFilterMode::DISTANCE_FIELD_MODE0, 2.0F},
    {ZoomFilterMode::DISTANCE_FIELD_MODE0, 2.0F},
    {ZoomFilterMode::DISTANCE_FIELD_MODE0, 2.0F},
};
inline const auto HYPERCOS_MODE0_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::HYPERCOS_MODE0, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE1, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE2, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE3, 0.0F},
};
inline const auto HYPERCOS_MODE1_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::HYPERCOS_MODE0, 1.0F}, // OK for mode0 to follow
    {ZoomFilterMode::HYPERCOS_MODE1, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE2, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE3, 0.0F},
};
inline const auto HYPERCOS_MODE2_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::HYPERCOS_MODE0, 1.0F}, // OK for mode0 to follow
    {ZoomFilterMode::HYPERCOS_MODE1, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE2, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE3, 0.0F},
};
inline const auto HYPERCOS_MODE3_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::HYPERCOS_MODE0, 1.0F}, // OK for mode0 to follow
    {ZoomFilterMode::HYPERCOS_MODE1, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE2, 0.0F},
    {ZoomFilterMode::HYPERCOS_MODE3, 0.0F},
};
inline const auto SPEEDWAY_MODE0_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::SPEEDWAY_MODE0, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE1, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE2, 0.0F},
};
inline const auto SPEEDWAY_MODE1_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::SPEEDWAY_MODE0, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE1, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE2, 0.0F},
};
inline const auto SPEEDWAY_MODE2_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::SPEEDWAY_MODE0, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE1, 0.0F},
    {ZoomFilterMode::SPEEDWAY_MODE2, 0.0F},
};
inline const auto WAVE_MODE0_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::WAVE_MODE0, 0.0F},
    {ZoomFilterMode::WAVE_MODE1, 0.0F},
};
inline const auto WAVE_MODE1_MULTIPLIERS = std::map<ZoomFilterMode, float>{
    {ZoomFilterMode::WAVE_MODE0, 0.0F},
    {ZoomFilterMode::WAVE_MODE1, 0.0F},
};

static constexpr auto FILTER_MODE_NAMES = EnumMap<ZoomFilterMode, std::string_view>{{{
    {ZoomFilterMode::AMULET_MODE, "Amulet"},
    {ZoomFilterMode::CRYSTAL_BALL_MODE0, "Crystal Ball Mode 0"},
    {ZoomFilterMode::CRYSTAL_BALL_MODE1, "Crystal Ball Mode 1"},
    {ZoomFilterMode::DISTANCE_FIELD_MODE0, "Distance Field Mode 0"},
    {ZoomFilterMode::DISTANCE_FIELD_MODE1, "Distance Field Mode 1"},
    {ZoomFilterMode::DISTANCE_FIELD_MODE2, "Distance Field Mode 2"},
    {ZoomFilterMode::EXP_RECIPROCAL_MODE, "Exp Reciprocal"},
    {ZoomFilterMode::HYPERCOS_MODE0, "Hypercos Mode 0"},
    {ZoomFilterMode::HYPERCOS_MODE1, "Hypercos Mode 1"},
    {ZoomFilterMode::HYPERCOS_MODE2, "Hypercos Mode 2"},
    {ZoomFilterMode::HYPERCOS_MODE3, "Hypercos Mode 3"},
    {ZoomFilterMode::IMAGE_DISPLACEMENT_MODE, "Image Displacement"},
    {ZoomFilterMode::NORMAL_MODE, "Normal"},
    {ZoomFilterMode::SCRUNCH_MODE, "Scrunch"},
    {ZoomFilterMode::SPEEDWAY_MODE0, "Speedway Mode 0"},
    {ZoomFilterMode::SPEEDWAY_MODE1, "Speedway Mode 1"},
    {ZoomFilterMode::SPEEDWAY_MODE2, "Speedway Mode 2"},
    {ZoomFilterMode::WATER_MODE, "Water"},
    {ZoomFilterMode::WAVE_MODE0, "Wave Mode 0"},
    {ZoomFilterMode::WAVE_MODE1, "Wave Mode 1"},
    {ZoomFilterMode::Y_ONLY_MODE, "Y Only"},
}}};

static constexpr auto AMULET_PROB_ROTATE             = PROB_HIGH;
static constexpr auto CRYSTAL_BALL0_PROB_ROTATE      = PROB_HIGH;
static constexpr auto CRYSTAL_BALL1_PROB_ROTATE      = PROB_HIGH;
static constexpr auto DISTANCE_FIELD0_PROB_ROTATE    = PROB_HIGH;
static constexpr auto DISTANCE_FIELD1_PROB_ROTATE    = PROB_HIGH;
static constexpr auto DISTANCE_FIELD2_PROB_ROTATE    = PROB_HIGH;
static constexpr auto EXP_RECIPROCAL_PROB_ROTATE     = PROB_LOW;
static constexpr auto HYPERCOS0_PROB_ROTATE          = PROB_LOW;
static constexpr auto HYPERCOS1_PROB_ROTATE          = PROB_LOW;
static constexpr auto HYPERCOS2_PROB_ROTATE          = PROB_LOW;
static constexpr auto HYPERCOS3_PROB_ROTATE          = PROB_LOW;
static constexpr auto IMAGE_DISPLACEMENT_PROB_ROTATE = PROB_ZERO;
static constexpr auto NORMAL_PROB_ROTATE             = PROB_ZERO;
static constexpr auto SCRUNCH_PROB_ROTATE            = PROB_HALF;
static constexpr auto SPEEDWAY0_PROB_ROTATE          = PROB_HALF;
static constexpr auto SPEEDWAY1_PROB_ROTATE          = PROB_HIGH;
static constexpr auto SPEEDWAY2_PROB_ROTATE          = PROB_HIGH;
static constexpr auto WATER_PROB_ROTATE              = PROB_ZERO;
static constexpr auto WAVE0_PROB_ROTATE              = PROB_HIGH;
static constexpr auto WAVE1_PROB_ROTATE              = PROB_HIGH;
static constexpr auto Y_ONLY_PROB_ROTATE             = PROB_HALF;

static constexpr auto DEFAULT_PROB_BLOCKY_WAVY_EFFECT    = 0.3F;
static constexpr auto DEFAULT_PROB_HYPERCOS_EFFECT       = 0.9F;
static constexpr auto DEFAULT_PROB_IMAGE_VELOCITY_EFFECT = 0.1F;
static constexpr auto DEFAULT_PROB_NOISE_EFFECT          = 0.1F;
static constexpr auto DEFAULT_PROB_PLANE_EFFECT          = 0.7F;
static constexpr auto DEFAULT_PROB_TAN_EFFECT            = 0.2F;
static constexpr auto DEFAULT_PROB_XY_LERP_EFFECT        = 0.2F;

static constexpr auto WAVE0_PROB_PLANE_EFFECT = 0.8F;
static constexpr auto WAVE1_PROB_PLANE_EFFECT = 0.8F;

// clang-format off
static constexpr auto EFFECTS_PROBABILITIES = EnumMap<ZoomFilterMode,
                                                      EnumMap<AfterEffectsTypes, float>>{{{
    { ZoomFilterMode::AMULET_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, AMULET_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::CRYSTAL_BALL_MODE0,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, CRYSTAL_BALL0_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::CRYSTAL_BALL_MODE1,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, CRYSTAL_BALL1_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::DISTANCE_FIELD_MODE0,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, DISTANCE_FIELD0_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::DISTANCE_FIELD_MODE1,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, DISTANCE_FIELD1_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::DISTANCE_FIELD_MODE2,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, DISTANCE_FIELD2_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::EXP_RECIPROCAL_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, EXP_RECIPROCAL_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::HYPERCOS_MODE0,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, HYPERCOS0_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::HYPERCOS_MODE1,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, HYPERCOS1_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::HYPERCOS_MODE2,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, HYPERCOS2_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::HYPERCOS_MODE3,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, HYPERCOS3_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::IMAGE_DISPLACEMENT_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, IMAGE_DISPLACEMENT_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::NORMAL_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, NORMAL_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::SCRUNCH_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, SCRUNCH_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::SPEEDWAY_MODE0,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, SPEEDWAY0_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::SPEEDWAY_MODE1,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, SPEEDWAY1_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::SPEEDWAY_MODE2,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, SPEEDWAY2_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::WATER_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, WATER_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::WAVE_MODE0,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, WAVE0_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, WAVE0_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::WAVE_MODE1,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, WAVE1_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, WAVE1_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
    { ZoomFilterMode::Y_ONLY_MODE,
      EnumMap<AfterEffectsTypes, float>{{{
          {AfterEffectsTypes::BLOCK_WAVY, DEFAULT_PROB_BLOCKY_WAVY_EFFECT},
          {AfterEffectsTypes::HYPERCOS, DEFAULT_PROB_HYPERCOS_EFFECT},
          {AfterEffectsTypes::IMAGE_VELOCITY, DEFAULT_PROB_IMAGE_VELOCITY_EFFECT},
          {AfterEffectsTypes::NOISE, DEFAULT_PROB_NOISE_EFFECT},
          {AfterEffectsTypes::PLANES, DEFAULT_PROB_PLANE_EFFECT},
          {AfterEffectsTypes::ROTATION, Y_ONLY_PROB_ROTATE},
          {AfterEffectsTypes::TAN_EFFECT, DEFAULT_PROB_TAN_EFFECT},
          {AfterEffectsTypes::XY_LERP_EFFECT, DEFAULT_PROB_XY_LERP_EFFECT},
      }}}
    },
}}};
// clang-format on

static constexpr auto DEFAULT_AFTER_EFFECTS_STATES = EnumMap<AfterEffectsTypes, bool>{{{
    {AfterEffectsTypes::BLOCK_WAVY, false},
    {AfterEffectsTypes::HYPERCOS, false},
    {AfterEffectsTypes::IMAGE_VELOCITY, false},
    {AfterEffectsTypes::NOISE, false},
    {AfterEffectsTypes::PLANES, false},
    {AfterEffectsTypes::ROTATION, false},
    {AfterEffectsTypes::TAN_EFFECT, false},
    {AfterEffectsTypes::XY_LERP_EFFECT, false},
}}};

static constexpr auto DEFAULT_AFTER_EFFECTS_PROBABILITIES = EnumMap<AfterEffectsTypes, float>{{{
    {AfterEffectsTypes::BLOCK_WAVY, 0.0F},
    {AfterEffectsTypes::HYPERCOS, 0.0F},
    {AfterEffectsTypes::IMAGE_VELOCITY, 0.0F},
    {AfterEffectsTypes::NOISE, 0.0F},
    {AfterEffectsTypes::PLANES, 0.0F},
    {AfterEffectsTypes::ROTATION, 0.0F},
    {AfterEffectsTypes::TAN_EFFECT, 0.0F},
    {AfterEffectsTypes::XY_LERP_EFFECT, 0.0F},
}}};

static constexpr auto DEFAULT_REPEAT_AFTER_EFFECTS_PROBABILITIES =
    EnumMap<AfterEffectsTypes, float>{{{
        {AfterEffectsTypes::BLOCK_WAVY, 0.9F},
        {AfterEffectsTypes::HYPERCOS, 0.5F},
        {AfterEffectsTypes::IMAGE_VELOCITY, 0.8F},
        {AfterEffectsTypes::NOISE, 0.0F},
        {AfterEffectsTypes::PLANES, 0.0F},
        {AfterEffectsTypes::ROTATION, 0.0F},
        {AfterEffectsTypes::TAN_EFFECT, 0.0F},
        {AfterEffectsTypes::XY_LERP_EFFECT, 0.1F},
    }}};
static constexpr auto ZERO_REPEAT_AFTER_EFFECTS_PROBABILITIES = EnumMap<AfterEffectsTypes, float>{{{
    {AfterEffectsTypes::BLOCK_WAVY, 0.0F},
    {AfterEffectsTypes::HYPERCOS, 0.0F},
    {AfterEffectsTypes::IMAGE_VELOCITY, 0.0F},
    {AfterEffectsTypes::NOISE, 0.0F},
    {AfterEffectsTypes::PLANES, 0.0F},
    {AfterEffectsTypes::ROTATION, 0.0F},
    {AfterEffectsTypes::TAN_EFFECT, 0.0F},
    {AfterEffectsTypes::XY_LERP_EFFECT, 0.0F},
}}};

static constexpr auto DEFAULT_AFTER_EFFECTS_OFF_TIMES = EnumMap<AfterEffectsTypes, uint32_t>{{{
    {AfterEffectsTypes::BLOCK_WAVY, 100U},
    {AfterEffectsTypes::HYPERCOS, 100U},
    {AfterEffectsTypes::IMAGE_VELOCITY, 100U},
    {AfterEffectsTypes::NOISE, 100U},
    {AfterEffectsTypes::PLANES, 100U},
    {AfterEffectsTypes::ROTATION, 0U},
    {AfterEffectsTypes::TAN_EFFECT, 100U},
    {AfterEffectsTypes::XY_LERP_EFFECT, 100U},
}}};

[[nodiscard]] constexpr auto GetAfterEffectsProbability(const ZoomFilterMode filterMode)
    -> EnumMap<AfterEffectsTypes, float>
{
  if constexpr (USE_FORCED_AFTER_EFFECT)
  {
    auto forcedProbabilities                       = DEFAULT_AFTER_EFFECTS_PROBABILITIES;
    forcedProbabilities[FORCED_AFTER_EFFECTS_TYPE] = 1.0F;
    return forcedProbabilities;
  }

  return EFFECTS_PROBABILITIES[filterMode];
}

[[nodiscard]] constexpr auto GetRepeatAfterEffectsProbability() -> EnumMap<AfterEffectsTypes, float>
{
  if constexpr (USE_FORCED_AFTER_EFFECT)
  {
    auto forcedRepeatProbabilities                       = ZERO_REPEAT_AFTER_EFFECTS_PROBABILITIES;
    forcedRepeatProbabilities[FORCED_AFTER_EFFECTS_TYPE] = 1.0F;
    return forcedRepeatProbabilities;
  }

  return DEFAULT_REPEAT_AFTER_EFFECTS_PROBABILITIES;
}

[[nodiscard]] constexpr auto GetAfterEffectsOffTime() -> EnumMap<AfterEffectsTypes, uint32_t>
{
  if constexpr (USE_FORCED_AFTER_EFFECT)
  {
    auto forcedOffTimes                       = DEFAULT_AFTER_EFFECTS_OFF_TIMES;
    forcedOffTimes[FORCED_AFTER_EFFECTS_TYPE] = 0;
    return forcedOffTimes;
  }

  return DEFAULT_AFTER_EFFECTS_OFF_TIMES;
}

// TODO(glk) - Can make this 'constexpr' with C++20.

[[nodiscard]] static auto GetHypercosWeights(const ZoomFilterMode filterMode) noexcept
    -> std::vector<Weights<HypercosOverlay>::KeyValue>
{
  constexpr auto FORCED_HYPERCOS =
      USE_FORCED_AFTER_EFFECT and (FORCED_AFTER_EFFECTS_TYPE == AfterEffectsTypes::HYPERCOS);

  using Hyp         = HypercosOverlay;
  using ModeWeights = std::array<Weights<HypercosOverlay>::KeyValue, NUM<HypercosOverlay>>;

  constexpr auto AMULET_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 20.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto CRYSTAL_BALL0_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 5.0F},
       {Hyp::MODE0, 10.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto CRYSTAL_BALL1_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 5.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 99.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto DISTANCE_FIELD_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 5.0F},
       {Hyp::MODE0, 10.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto EXP_RECIPROCAL_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 5.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 0.0F}}
  };
  constexpr auto HYPERCOS0_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 1.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 2.0F},
       {Hyp::MODE2, 2.0F},
       {Hyp::MODE3, 2.0F}}
  };
  constexpr auto HYPERCOS1_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 1.0F},
       {Hyp::MODE0, 2.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 2.0F},
       {Hyp::MODE3, 2.0F}}
  };
  constexpr auto HYPERCOS2_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 1.0F},
       {Hyp::MODE0, 2.0F},
       {Hyp::MODE1, 2.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 2.0F}}
  };
  constexpr auto HYPERCOS3_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 1.0F},
       {Hyp::MODE0, 2.0F},
       {Hyp::MODE1, 2.0F},
       {Hyp::MODE2, 2.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto IMAGE_DISPLACEMENT_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto NORMAL_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 5.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 0.0F}}
  };
  constexpr auto SCRUNCH_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto SPEEDWAY_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 5.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto WATER_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto WAVE0_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 5.0F},
       {Hyp::MODE1, 1.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto WAVE1_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };
  constexpr auto Y_ONLY_HYPERCOS_WEIGHTS = ModeWeights{
      {{Hyp::NONE, FORCED_HYPERCOS ? 0.0F : 10.0F},
       {Hyp::MODE0, 1.0F},
       {Hyp::MODE1, 5.0F},
       {Hyp::MODE2, 1.0F},
       {Hyp::MODE3, 1.0F}}
  };

  constexpr auto HYPERCOS_WEIGHTS = EnumMap<ZoomFilterMode, ModeWeights>{{{
      {ZoomFilterMode::AMULET_MODE, AMULET_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::CRYSTAL_BALL_MODE0, CRYSTAL_BALL0_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::CRYSTAL_BALL_MODE1, CRYSTAL_BALL1_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::DISTANCE_FIELD_MODE0, DISTANCE_FIELD_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::DISTANCE_FIELD_MODE1, DISTANCE_FIELD_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::DISTANCE_FIELD_MODE2, DISTANCE_FIELD_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::EXP_RECIPROCAL_MODE, EXP_RECIPROCAL_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::HYPERCOS_MODE0, HYPERCOS0_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::HYPERCOS_MODE1, HYPERCOS1_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::HYPERCOS_MODE2, HYPERCOS2_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::HYPERCOS_MODE3, HYPERCOS3_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::IMAGE_DISPLACEMENT_MODE, IMAGE_DISPLACEMENT_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::NORMAL_MODE, NORMAL_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::SCRUNCH_MODE, SCRUNCH_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::SPEEDWAY_MODE0, SPEEDWAY_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::SPEEDWAY_MODE1, SPEEDWAY_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::SPEEDWAY_MODE2, SPEEDWAY_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::WATER_MODE, WATER_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::WAVE_MODE0, WAVE0_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::WAVE_MODE1, WAVE1_HYPERCOS_WEIGHTS},
      {ZoomFilterMode::Y_ONLY_MODE, Y_ONLY_HYPERCOS_WEIGHTS},
  }}};
  Expects(HYPERCOS_WEIGHTS.size() == NUM<ZoomFilterMode>);

  return std::vector<Weights<HypercosOverlay>::KeyValue>{cbegin(HYPERCOS_WEIGHTS[filterMode]),
                                                         cend(HYPERCOS_WEIGHTS[filterMode])};
}

auto FilterSettingsService::GetFilterModeData(
    const IGoomRand& goomRand,
    const std::string& resourcesDirectory,
    const CreateZoomInCoefficientsEffectFunc& createZoomInCoefficientsEffect) -> FilterModeEnumMap
{
  Expects(FILTER_MODE_NAMES.size() == NUM<ZoomFilterMode>);
  Expects(EFFECTS_PROBABILITIES.size() == NUM<ZoomFilterMode>);

  auto filterModeVec = std::vector<FilterModeEnumMap::KeyValue>{};

  for (auto i = 0U; i < NUM<ZoomFilterMode>; ++i)
  {
    const auto filterMode = static_cast<ZoomFilterMode>(i);

    filterModeVec.emplace_back(
        filterMode,
        ZoomFilterModeInfo{
            FILTER_MODE_NAMES[filterMode],
            createZoomInCoefficientsEffect(filterMode, goomRand, resourcesDirectory),
            {Weights<HypercosOverlay>{goomRand, GetHypercosWeights(filterMode)},
                                                        GetAfterEffectsProbability(filterMode)},
    });
  }

  return FilterModeEnumMap::Make(std::move(filterModeVec));
}

FilterSettingsService::FilterSettingsService(const PluginInfo& goomInfo,
                                             const IGoomRand& goomRand,
                                             const std::string& resourcesDirectory,
                                             const CreateZoomInCoefficientsEffectFunc&
                                                 createZoomInCoefficientsEffect)
  : m_goomInfo{goomInfo},
    m_goomRand{goomRand},
    m_screenMidpoint{U_HALF * m_goomInfo.GetScreenWidth(),
                     U_HALF * m_goomInfo.GetScreenHeight()},
    m_resourcesDirectory{resourcesDirectory},
    m_randomizedAfterEffects{
        std::make_unique<AfterEffectsStates>(m_goomRand,
                                             GetRepeatAfterEffectsProbability(),
                                             GetAfterEffectsOffTime())},
    m_filterModeData{GetFilterModeData(m_goomRand,
                                       m_resourcesDirectory,
                                       createZoomInCoefficientsEffect)},
    m_filterSettings{
        false,
        {
           Vitesse{},
           DEFAULT_MAX_ZOOM_IN_COEFF,
           DEFAULT_BASE_ZOOM_IN_COEFF_FACTOR_MULTIPLIER,
           nullptr,
           {DEFAULT_ZOOM_MID_X, DEFAULT_ZOOM_MID_Y},
           {
               HypercosOverlay::NONE,
               DEFAULT_AFTER_EFFECTS_STATES,
               RotationAdjustments{},
            }
        },
        {DEFAULT_TRAN_LERP_INCREMENT, DEFAULT_SWITCH_MULT, DEFAULT_FILTER_VIEWPORT},
    },
    m_weightedFilterEvents{
        m_goomRand,
        {
            {ZoomFilterMode::AMULET_MODE,             AMULET_MODE_WEIGHT},
            {ZoomFilterMode::CRYSTAL_BALL_MODE0,      CRYSTAL_BALL_MODE0_WEIGHT},
            {ZoomFilterMode::CRYSTAL_BALL_MODE1,      CRYSTAL_BALL_MODE1_WEIGHT},
            {ZoomFilterMode::DISTANCE_FIELD_MODE0,    DISTANCE_FIELD_MODE0_WEIGHT},
            {ZoomFilterMode::DISTANCE_FIELD_MODE1,    DISTANCE_FIELD_MODE1_WEIGHT},
            {ZoomFilterMode::DISTANCE_FIELD_MODE2,    DISTANCE_FIELD_MODE2_WEIGHT},
            {ZoomFilterMode::EXP_RECIPROCAL_MODE,     EXP_RECIPROCAL_MODE_WEIGHT},
            {ZoomFilterMode::HYPERCOS_MODE0,          HYPERCOS_MODE0_WEIGHT},
            {ZoomFilterMode::HYPERCOS_MODE1,          HYPERCOS_MODE1_WEIGHT},
            {ZoomFilterMode::HYPERCOS_MODE2,          HYPERCOS_MODE2_WEIGHT},
            {ZoomFilterMode::HYPERCOS_MODE3,          HYPERCOS_MODE3_WEIGHT},
            {ZoomFilterMode::IMAGE_DISPLACEMENT_MODE, IMAGE_DISPLACEMENT_MODE_WEIGHT},
            {ZoomFilterMode::NORMAL_MODE,             NORMAL_MODE_WEIGHT},
            {ZoomFilterMode::SCRUNCH_MODE,            SCRUNCH_MODE_WEIGHT},
            {ZoomFilterMode::SPEEDWAY_MODE0,          SPEEDWAY_MODE0_WEIGHT},
            {ZoomFilterMode::SPEEDWAY_MODE1,          SPEEDWAY_MODE1_WEIGHT},
            {ZoomFilterMode::SPEEDWAY_MODE2,          SPEEDWAY_MODE2_WEIGHT},
            {ZoomFilterMode::WAVE_MODE0,              WAVE_MODE0_WEIGHT},
            {ZoomFilterMode::WAVE_MODE1,              WAVE_MODE1_WEIGHT},
            {ZoomFilterMode::WATER_MODE,              WATER_MODE_WEIGHT},
            {ZoomFilterMode::Y_ONLY_MODE,             Y_ONLY_MODE_WEIGHT},
        },
        {
            {ZoomFilterMode::CRYSTAL_BALL_MODE0, CRYSTAL_BALL_MODE0_MULTIPLIERS},
            {ZoomFilterMode::CRYSTAL_BALL_MODE1, CRYSTAL_BALL_MODE1_MULTIPLIERS},
            {ZoomFilterMode::NORMAL_MODE,        NORMAL_MODE_MULTIPLIERS},
            {ZoomFilterMode::HYPERCOS_MODE0,     HYPERCOS_MODE0_MULTIPLIERS},
            {ZoomFilterMode::HYPERCOS_MODE1,     HYPERCOS_MODE1_MULTIPLIERS},
            {ZoomFilterMode::HYPERCOS_MODE2,     HYPERCOS_MODE2_MULTIPLIERS},
            {ZoomFilterMode::HYPERCOS_MODE3,     HYPERCOS_MODE3_MULTIPLIERS},
            {ZoomFilterMode::SPEEDWAY_MODE0,     SPEEDWAY_MODE0_MULTIPLIERS},
            {ZoomFilterMode::SPEEDWAY_MODE1,     SPEEDWAY_MODE1_MULTIPLIERS},
            {ZoomFilterMode::SPEEDWAY_MODE2,     SPEEDWAY_MODE2_MULTIPLIERS},
            {ZoomFilterMode::WAVE_MODE0,         WAVE_MODE0_MULTIPLIERS},
            {ZoomFilterMode::WAVE_MODE1,         WAVE_MODE1_MULTIPLIERS},
        },
    },
    m_zoomMidpointWeights{
      m_goomRand,
      {
          {ZoomMidpointEvents::BOTTOM_MID_POINT,            BOTTOM_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::TOP_MID_POINT,               TOP_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::LEFT_MID_POINT,              LEFT_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::RIGHT_MID_POINT,             RIGHT_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::CENTRE_MID_POINT,            CENTRE_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::BOTTOM_LEFT_QUARTER_MID_POINT,
                                                            BOTTOM_LEFT_QUARTER_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::TOP_LEFT_QUARTER_MID_POINT,  TOP_LEFT_QUARTER_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::BOTTOM_RIGHT_QUARTER_MID_POINT,
                                                            BOTTOM_RIGHT_QUARTER_MID_POINT_WEIGHT},
          {ZoomMidpointEvents::TOP_RIGHT_QUARTER_MID_POINT, TOP_RIGHT_QUARTER_MID_POINT_WEIGHT},
      }
    }
{
}

FilterSettingsService::~FilterSettingsService() noexcept = default;

auto FilterSettingsService::GetNewRandomMode() const -> ZoomFilterMode
{
  if constexpr (USE_FORCED_FILTER_MODE)
  {
    return FORCED_FILTER_MODE;
  }
  return m_weightedFilterEvents.GetRandomWeighted(m_filterMode);
}

auto FilterSettingsService::Start() -> void
{
  SetNewRandomFilter();
}

inline auto FilterSettingsService::GetZoomInCoefficientsEffect()
    -> std::shared_ptr<IZoomInCoefficientsEffect>&
{
  return m_filterModeData[m_filterMode].zoomInCoefficientsEffect;
}

auto FilterSettingsService::NewCycle() -> void
{
  m_randomizedAfterEffects->UpdateTimers();
}

auto FilterSettingsService::NotifyUpdatedFilterEffectsSettings() -> void
{
  m_filterSettings.filterEffectsSettingsHaveChanged = false;

  m_filterModeAtLastUpdate = m_filterMode;
  m_randomizedAfterEffects->CheckForPendingOffTimers();
}

auto FilterSettingsService::SetDefaultSettings() -> void
{
  m_filterSettings.filterEffectsSettings.zoomInCoefficientsEffect = GetZoomInCoefficientsEffect();
  m_filterSettings.filterEffectsSettings.zoomMidpoint             = m_screenMidpoint;
  m_filterSettings.filterBufferSettings.filterEffectViewport      = Viewport{};
  m_filterSettings.filterEffectsSettings.vitesse.SetDefault();

  m_randomizedAfterEffects->SetDefaults();
}

auto FilterSettingsService::SetFilterModeRandomViewport() -> void
{
  m_filterSettings.filterBufferSettings.filterEffectViewport =
      m_filterModeData[m_filterMode].zoomInCoefficientsEffect->GetZoomInCoefficientsViewport();
}

auto FilterSettingsService::SetFilterModeRandomEffects() -> void
{
  m_filterSettings.filterEffectsSettings.zoomInCoefficientsEffect->SetRandomParams();
}

auto FilterSettingsService::SetFilterModeExtraEffects() -> void
{
  SetRandomizedExtraEffects();
  SetWaveModeExtraEffects();
}

auto FilterSettingsService::ResetRandomExtraEffects() -> void
{
  const auto& modeInfo = m_filterModeData[m_filterMode];
  m_randomizedAfterEffects->ResetStandardStates(modeInfo.afterEffectsProbabilities);
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
}

auto FilterSettingsService::SetRandomizedExtraEffects() -> void
{
  const auto& modeInfo = m_filterModeData[m_filterMode];

  m_randomizedAfterEffects->ResetAllStates(modeInfo.afterEffectsProbabilities);

  m_filterSettings.filterEffectsSettings.afterEffectsSettings.rotationAdjustments.SetMultiplyFactor(
      modeInfo.afterEffectsProbabilities.probabilities[AfterEffectsTypes::ROTATION],
      RotationAdjustments::AdjustmentType::AFTER_RANDOM);
}

auto FilterSettingsService::SetWaveModeExtraEffects() -> void
{
  if ((m_filterMode != ZoomFilterMode::WAVE_MODE0) && (m_filterMode != ZoomFilterMode::WAVE_MODE1))
  {
    return;
  }

  m_randomizedAfterEffects->TurnPlaneEffectOn();

  auto& filterEffectsSettings = m_filterSettings.filterEffectsSettings;
  filterEffectsSettings.vitesse.SetReverseVitesse(m_goomRand.ProbabilityOf(PROB_REVERSE_SPEED));
  if (m_goomRand.ProbabilityOf(PROB_CHANGE_SPEED))
  {
    filterEffectsSettings.vitesse.SetVitesse(
        U_HALF * (Vitesse::DEFAULT_SPEED + filterEffectsSettings.vitesse.GetVitesse()));
  }
}

auto FilterSettingsService::UpdateFilterSettingsFromExtraEffects() -> void
{
  m_filterSettings.filterEffectsSettingsHaveChanged = true;
  m_randomizedAfterEffects->UpdateFilterSettingsFromStates(
      m_filterSettings.filterEffectsSettings.afterEffectsSettings);
}

auto FilterSettingsService::SetBaseZoomInCoeffFactorMultiplier() noexcept -> void
{
  if (static constexpr auto PROB_CALM_DOWN = 0.8F; m_goomRand.ProbabilityOf(PROB_CALM_DOWN))
  {
    m_filterSettings.filterEffectsSettings.baseZoomInCoeffFactorMultiplier = 1.0F;
    return;
  }

  // TODO(glk) Lerp between old and new?
  static constexpr auto MULTIPLIER_RANGE = IGoomRand::NumberRange<float>{0.1F, 5.0F};

  static_assert(
      ZoomVectorEffects::MIN_ALLOWED_BASE_ZOOM_IN_COEFF <=
      ZoomVectorEffects::GetBaseZoomInCoeff(
          MULTIPLIER_RANGE.min * ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, -1.0F));
  static_assert(
      ZoomVectorEffects::MIN_ALLOWED_BASE_ZOOM_IN_COEFF <=
      ZoomVectorEffects::GetBaseZoomInCoeff(
          MULTIPLIER_RANGE.max * ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, -1.0F));
  static_assert(
      ZoomVectorEffects::MAX_ALLOWED_BASE_ZOOM_IN_COEFF >=
      ZoomVectorEffects::GetBaseZoomInCoeff(
          MULTIPLIER_RANGE.min * ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, +1.0F));
  static_assert(
      ZoomVectorEffects::MAX_ALLOWED_BASE_ZOOM_IN_COEFF >=
      ZoomVectorEffects::GetBaseZoomInCoeff(
          MULTIPLIER_RANGE.max * ZoomVectorEffects::RAW_BASE_ZOOM_IN_COEFF_FACTOR, +1.0F));

  m_filterSettings.filterEffectsSettings.baseZoomInCoeffFactorMultiplier =
      m_goomRand.GetRandInRange(MULTIPLIER_RANGE);
}

auto FilterSettingsService::SetRandomZoomMidpoint() -> void
{
  if (ALL_AFTER_EFFECTS_TURNED_OFF or IsZoomMidpointInTheMiddle())
  {
    m_filterSettings.filterEffectsSettings.zoomMidpoint = m_screenMidpoint;
    return;
  }

  const auto allowEdgePoints =
      (m_filterMode != ZoomFilterMode::WAVE_MODE0) && (m_filterMode != ZoomFilterMode::WAVE_MODE1);
  SetAnyRandomZoomMidpoint(allowEdgePoints);
}

auto FilterSettingsService::IsZoomMidpointInTheMiddle() const -> bool
{
  if ((m_filterMode == ZoomFilterMode::WATER_MODE) || (m_filterMode == ZoomFilterMode::AMULET_MODE))
  {
    return true;
  }

  if (((m_filterMode == ZoomFilterMode::CRYSTAL_BALL_MODE0) ||
       (m_filterMode == ZoomFilterMode::CRYSTAL_BALL_MODE1)) &&
      m_goomRand.ProbabilityOf(PROB_CRYSTAL_BALL_IN_MIDDLE))
  {
    return true;
  }

  if (((m_filterMode == ZoomFilterMode::WAVE_MODE0) ||
       (m_filterMode == ZoomFilterMode::WAVE_MODE1)) &&
      m_goomRand.ProbabilityOf(PROB_WAVE_IN_MIDDLE))
  {
    return true;
  }

  return false;
}

auto FilterSettingsService::GetWeightRandomMidPoint(const bool allowEdgePoints) const
    -> ZoomMidpointEvents
{
  auto midPointEvent = m_zoomMidpointWeights.GetRandomWeighted();

  if (allowEdgePoints)
  {
    return midPointEvent;
  }

  while (IsEdgeMidPoint(midPointEvent))
  {
    midPointEvent = m_zoomMidpointWeights.GetRandomWeighted();
  }
  return midPointEvent;
}

inline auto FilterSettingsService::IsEdgeMidPoint(const ZoomMidpointEvents midPointEvent) -> bool
{
  return (midPointEvent == ZoomMidpointEvents::BOTTOM_MID_POINT) ||
         (midPointEvent == ZoomMidpointEvents::TOP_MID_POINT) ||
         (midPointEvent == ZoomMidpointEvents::RIGHT_MID_POINT) ||
         (midPointEvent == ZoomMidpointEvents::LEFT_MID_POINT);
}

auto FilterSettingsService::SetAnyRandomZoomMidpoint(const bool allowEdgePoints) -> void
{
  switch (GetWeightRandomMidPoint(allowEdgePoints))
  {
    case ZoomMidpointEvents::BOTTOM_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {U_HALF * m_goomInfo.GetScreenWidth(),
                                                             m_goomInfo.GetScreenHeight() - 2U};
      break;
    case ZoomMidpointEvents::TOP_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {U_HALF * m_goomInfo.GetScreenWidth(),
                                                             1U};
      break;
    case ZoomMidpointEvents::LEFT_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {1U,
                                                             U_HALF * m_goomInfo.GetScreenHeight()};
      break;
    case ZoomMidpointEvents::RIGHT_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {m_goomInfo.GetScreenWidth() - 2U,
                                                             U_HALF * m_goomInfo.GetScreenHeight()};
      break;
    case ZoomMidpointEvents::CENTRE_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = m_screenMidpoint;
      break;
    case ZoomMidpointEvents::BOTTOM_LEFT_QUARTER_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {
          U_QUARTER * m_goomInfo.GetScreenWidth(), U_THREE_QUARTERS * m_goomInfo.GetScreenHeight()};
      break;
    case ZoomMidpointEvents::TOP_LEFT_QUARTER_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {
          U_QUARTER * m_goomInfo.GetScreenWidth(), U_QUARTER * m_goomInfo.GetScreenHeight()};
      break;
    case ZoomMidpointEvents::BOTTOM_RIGHT_QUARTER_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {
          U_THREE_QUARTERS * m_goomInfo.GetScreenWidth(),
          U_THREE_QUARTERS * m_goomInfo.GetScreenHeight()};
      break;
    case ZoomMidpointEvents::TOP_RIGHT_QUARTER_MID_POINT:
      m_filterSettings.filterEffectsSettings.zoomMidpoint = {
          U_THREE_QUARTERS * m_goomInfo.GetScreenWidth(), U_QUARTER * m_goomInfo.GetScreenHeight()};
      break;
    default:
      FailFast();
  }
}

} // namespace GOOM::FILTER_FX
