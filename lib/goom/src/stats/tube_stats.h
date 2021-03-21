#ifndef VISUALIZATION_GOOM_STATS_TUBE_STATS_H
#define VISUALIZATION_GOOM_STATS_TUBE_STATS_H

#include "goom/goom_config.h"
#include "goom/goom_stats.h"

#include <cstdint>

namespace GOOM
{


class TubeStats
{
public:
  TubeStats() = default;

  void Reset();
  void Log(const GoomStats::LogStatsValueFunc& logVal) const;

  void ResetColorMaps();
  void AllJoinedInCentre();
  void AllMaxFromCentre();
  void UpdateAllJoinInCentreSpeed(float val);

  void IncreaseCircleSpeed();
  void DecreaseCircleSpeed();
  void NormalCircleSpeed();
  void UpdateCircleSpeed(float val);

  void IncreaseCentreSpeed();
  void DecreaseCentreSpeed();
  void NormalCentreSpeed();
  void UpdateCentreSpeed(float val);

private:
  uint32_t m_numResetColorMaps = 0;

  uint32_t m_numAllJoinedInCentre = 0;
  uint32_t m_numAllMaxFromCentre = 0;
  float m_lastAllJoinInCentreSpeed = 0.0;
  float m_minAllJoinInCentreSpeed = 10000.0;
  float m_maxAllJoinInCentreSpeed = 0.0;

  uint32_t m_numIncreaseCircleSpeed = 0;
  uint32_t m_numDecreaseCircleSpeed = 0;
  uint32_t m_numNormalCircleSpeed = 0;
  float m_lastCircleSpeed = 0.0;
  float m_minCircleSpeed = 10000.0;
  float m_maxCircleSpeed = 0.0;

  uint32_t m_numIncreaseCentreSpeed = 0;
  uint32_t m_numDecreaseCentreSpeed = 0;
  uint32_t m_numNormalCentreSpeed = 0;
  float m_lastCentreSpeed = 0.0;
  float m_minCentreSpeed = 10000.0;
  float m_maxCentreSpeed = 0.0;
};

} // namespace GOOM

#endif //VISUALIZATION_GOOM_STATS_TUBE_STATS_H
