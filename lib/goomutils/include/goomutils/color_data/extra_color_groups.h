#ifndef VISUALIZATION_GOOM_EXTRA_COLOR_GROUPS_H
#define VISUALIZATION_GOOM_EXTRA_COLOR_GROUPS_H

#include "color_data/colormap_enums.h"

#include <vector>

#if __cplusplus > 201402L
namespace GOOM::UTILS::COLOR_DATA
{
#else
namespace GOOM
{
namespace UTILS
{
namespace COLOR_DATA
{
#endif

extern const std::vector<ColorMapName> wesAndersonMaps;
extern const std::vector<ColorMapName> blueMaps;
extern const std::vector<ColorMapName> redMaps;
extern const std::vector<ColorMapName> greenMaps;
extern const std::vector<ColorMapName> yellowMaps;
extern const std::vector<ColorMapName> orangeMaps;
extern const std::vector<ColorMapName> purpleMaps;
extern const std::vector<ColorMapName> cityMaps;
extern const std::vector<ColorMapName> seasonMaps;
extern const std::vector<ColorMapName> heatMaps;
extern const std::vector<ColorMapName> coldMaps;
extern const std::vector<ColorMapName> pastelMaps;

#if __cplusplus > 201402L
} // namespace GOOM::UTILS::COLOR_DATA
#else
} // namespace COLOR_DATA
} // namespace UTILS
} // namespace GOOM
#endif

#endif //VISUALIZATION_GOOM_EXTRA_COLOR_GROUPS_H
