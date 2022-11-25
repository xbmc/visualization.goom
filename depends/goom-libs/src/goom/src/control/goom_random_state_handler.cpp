#include "goom_random_state_handler.h"

#include "control/state_and_filter_consts.h"
#include "goom_config.h"
#include "utils/enum_utils.h"

namespace GOOM::CONTROL
{

using CONTROL::USE_FORCED_GOOM_STATE;
using UTILS::NUM;
using UTILS::MATH::IGoomRand;


// For debugging:

//static constexpr auto FORCED_GOOM_STATE = GoomStates::CIRCLES_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_IFS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_IFS_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_IMAGE_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_LINES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_LINES_STAR_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_LINES_TENTACLES_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_LINES_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_STARS_TENTACLES_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::DOTS_TENTACLES_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_IMAGE;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_LINES_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_STARS_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_TENTACLES_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IFS_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_LINES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_LINES_STARS_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::IMAGE_TUBES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::LINES_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::LINES_STARS;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::LINES_TENTACLES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::SHAPES_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::SHAPES_STARS_LINES;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::STARS_ONLY;
static constexpr auto FORCED_GOOM_STATE = GoomStates::TENTACLES_ONLY;
//static constexpr auto FORCED_GOOM_STATE = GoomStates::TUBES_ONLY;

// End debugging


static constexpr auto CIRCLES_ONLY_WEIGHT                = 050.0F;
static constexpr auto CIRCLES_IFS_WEIGHT                 = 200.0F;
static constexpr auto CIRCLES_IMAGE_WEIGHT               = 050.0F;
static constexpr auto CIRCLES_IMAGE_STARS_WEIGHT         = 200.0F;
static constexpr auto CIRCLES_LINES_WEIGHT               = 200.0F;
static constexpr auto CIRCLES_STARS_TUBES_WEIGHT         = 100.0F;
static constexpr auto CIRCLES_TENTACLES_WEIGHT           = 200.0F;
static constexpr auto DOTS_IFS_WEIGHT                    = 200.0F;
static constexpr auto DOTS_IFS_STARS_WEIGHT              = 100.0F;
static constexpr auto DOTS_IMAGE_STARS_WEIGHT            = 050.0F;
static constexpr auto DOTS_LINES_WEIGHT                  = 050.0F;
static constexpr auto DOTS_LINES_STAR_TENTACLES_WEIGHT   = 040.0F;
static constexpr auto DOTS_LINES_TENTACLES_TUBES_WEIGHT  = 040.0F;
static constexpr auto DOTS_LINES_TUBES_WEIGHT            = 060.0F;
static constexpr auto DOTS_ONLY_WEIGHT                   = 001.0F;
static constexpr auto DOTS_STARS_WEIGHT                  = 100.0F;
static constexpr auto DOTS_STARS_TENTACLES_TUBES_WEIGHT  = 100.0F;
static constexpr auto DOTS_TENTACLES_TUBES_WEIGHT        = 200.0F;
static constexpr auto IFS_IMAGE_WEIGHT                   = 100.0F;
static constexpr auto IFS_IMAGE_SHAPES_WEIGHT            = 100.0F;
static constexpr auto IFS_LINES_STARS_WEIGHT             = 200.0F;
static constexpr auto IFS_ONLY_WEIGHT                    = 100.0F;
static constexpr auto IFS_SHAPES_WEIGHT                  = 100.0F;
static constexpr auto IFS_STARS_WEIGHT                   = 200.0F;
static constexpr auto IFS_STARS_TENTACLES_WEIGHT         = 070.0F;
static constexpr auto IFS_TENTACLES_WEIGHT               = 070.0F;
static constexpr auto IFS_TENTACLES_TUBES_WEIGHT         = 070.0F;
static constexpr auto IFS_TUBES_WEIGHT                   = 200.0F;
static constexpr auto IMAGE_LINES_WEIGHT                 = 100.0F;
static constexpr auto IMAGE_LINES_SHAPES_WEIGHT          = 100.0F;
static constexpr auto IMAGE_LINES_STARS_TENTACLES_WEIGHT = 100.0F;
static constexpr auto IMAGE_ONLY_WEIGHT                  = 001.0F;
static constexpr auto IMAGE_SHAPES_WEIGHT                = 100.0F;
static constexpr auto IMAGE_SHAPES_STARS_WEIGHT          = 100.0F;
static constexpr auto IMAGE_SHAPES_TUBES_WEIGHT          = 100.0F;
static constexpr auto IMAGE_STARS_WEIGHT                 = 200.0F;
static constexpr auto IMAGE_TENTACLES_WEIGHT             = 070.0F;
static constexpr auto IMAGE_TUBES_WEIGHT                 = 200.0F;
static constexpr auto LINES_ONLY_WEIGHT                  = 100.0F;
static constexpr auto LINES_SHAPES_STARS_WEIGHT          = 200.0F;
static constexpr auto LINES_STARS_WEIGHT                 = 100.0F;
static constexpr auto LINES_TENTACLES_WEIGHT             = 200.0F;
static constexpr auto SHAPES_ONLY_WEIGHT                 = 001.0F;
static constexpr auto SHAPES_STARS_WEIGHT                = 200.0F;
static constexpr auto SHAPES_TUBES_WEIGHT                = 200.0F;
static constexpr auto STARS_ONLY_WEIGHT                  = 001.0F;
static constexpr auto TENTACLES_ONLY_WEIGHT              = 001.0F;
static constexpr auto TUBES_ONLY_WEIGHT                  = 001.0F;


GoomRandomStateHandler::GoomRandomStateHandler(const IGoomRand& goomRand)
  : m_weightedStates{
        goomRand,
        {
          {GoomStates::CIRCLES_ONLY, CIRCLES_ONLY_WEIGHT},
          {GoomStates::CIRCLES_IFS, CIRCLES_IFS_WEIGHT},
          {GoomStates::CIRCLES_IMAGE, CIRCLES_IMAGE_WEIGHT},
          {GoomStates::CIRCLES_IMAGE_STARS, CIRCLES_IMAGE_STARS_WEIGHT},
          {GoomStates::CIRCLES_LINES, CIRCLES_LINES_WEIGHT},
          {GoomStates::CIRCLES_STARS_TUBES, CIRCLES_STARS_TUBES_WEIGHT},
          {GoomStates::CIRCLES_TENTACLES, CIRCLES_TENTACLES_WEIGHT},

          {GoomStates::DOTS_IFS, DOTS_IFS_WEIGHT},
          {GoomStates::DOTS_IFS_STARS, DOTS_IFS_STARS_WEIGHT},
          {GoomStates::DOTS_IMAGE_STARS, DOTS_IMAGE_STARS_WEIGHT},
          {GoomStates::DOTS_LINES, DOTS_LINES_WEIGHT},
          {GoomStates::DOTS_LINES_STARS_TENTACLES, DOTS_LINES_STAR_TENTACLES_WEIGHT},
          {GoomStates::DOTS_LINES_TENTACLES_TUBES, DOTS_LINES_TENTACLES_TUBES_WEIGHT},
          {GoomStates::DOTS_LINES_TUBES, DOTS_LINES_TUBES_WEIGHT},
          {GoomStates::DOTS_ONLY, DOTS_ONLY_WEIGHT},
          {GoomStates::DOTS_STARS, DOTS_STARS_WEIGHT},
          {GoomStates::DOTS_STARS_TENTACLES_TUBES, DOTS_STARS_TENTACLES_TUBES_WEIGHT},
          {GoomStates::DOTS_TENTACLES_TUBES, DOTS_TENTACLES_TUBES_WEIGHT},

          {GoomStates::IFS_IMAGE, IFS_IMAGE_WEIGHT},
          {GoomStates::IFS_IMAGE_SHAPES, IFS_IMAGE_SHAPES_WEIGHT},
          {GoomStates::IFS_LINES_STARS, IFS_LINES_STARS_WEIGHT},
          {GoomStates::IFS_ONLY, IFS_ONLY_WEIGHT},
          {GoomStates::IFS_SHAPES, IFS_SHAPES_WEIGHT},
          {GoomStates::IFS_STARS, IFS_STARS_WEIGHT},
          {GoomStates::IFS_STARS_TENTACLES, IFS_STARS_TENTACLES_WEIGHT},
          {GoomStates::IFS_TENTACLES, IFS_TENTACLES_WEIGHT},
          {GoomStates::IFS_TENTACLES_TUBES, IFS_TENTACLES_TUBES_WEIGHT},
          {GoomStates::IFS_TUBES, IFS_TUBES_WEIGHT},

          {GoomStates::IMAGE_LINES, IMAGE_LINES_WEIGHT},
          {GoomStates::IMAGE_LINES_SHAPES, IMAGE_LINES_SHAPES_WEIGHT},
          {GoomStates::IMAGE_LINES_STARS_TENTACLES, IMAGE_LINES_STARS_TENTACLES_WEIGHT},
          {GoomStates::IMAGE_ONLY, IMAGE_ONLY_WEIGHT},
          {GoomStates::IMAGE_SHAPES, IMAGE_SHAPES_WEIGHT},
          {GoomStates::IMAGE_SHAPES_STARS, IMAGE_SHAPES_STARS_WEIGHT},
          {GoomStates::IMAGE_SHAPES_TUBES, IMAGE_SHAPES_TUBES_WEIGHT},
          {GoomStates::IMAGE_STARS, IMAGE_STARS_WEIGHT},
          {GoomStates::IMAGE_TENTACLES, IMAGE_TENTACLES_WEIGHT},
          {GoomStates::IMAGE_TUBES, IMAGE_TUBES_WEIGHT},

          {GoomStates::LINES_ONLY, LINES_ONLY_WEIGHT},
          {GoomStates::LINES_SHAPES_STARS, LINES_SHAPES_STARS_WEIGHT},
          {GoomStates::LINES_STARS, LINES_STARS_WEIGHT},
          {GoomStates::LINES_TENTACLES, LINES_TENTACLES_WEIGHT},

          {GoomStates::SHAPES_ONLY, SHAPES_ONLY_WEIGHT},
          {GoomStates::SHAPES_STARS, SHAPES_STARS_WEIGHT},
          {GoomStates::SHAPES_TUBES, SHAPES_TUBES_WEIGHT},

          {GoomStates::STARS_ONLY, STARS_ONLY_WEIGHT},

          {GoomStates::TENTACLES_ONLY, TENTACLES_ONLY_WEIGHT},

          {GoomStates::TUBES_ONLY, TUBES_ONLY_WEIGHT},
          }
}
{
  Ensures(m_weightedStates.GetNumElements() == NUM<GoomStates>);
}

void GoomRandomStateHandler::ChangeToNextState()
{
  if constexpr (USE_FORCED_GOOM_STATE)
  {
    m_currentState = FORCED_GOOM_STATE;
    return;
  }

  m_currentState = m_weightedStates.GetRandomWeighted();
}

} // namespace GOOM::CONTROL
