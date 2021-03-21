#include "tube_stats.h"

#include "goom/goom_stats.h"

namespace GOOM
{

void TubeStats::Reset()
{
  m_numResetColorMaps = 0;
  m_numAllJoinedInCentre = 0;
  m_numAllMaxFromCentre = 0;
  m_numIncreaseCentreSpeed = 0;
  m_numDecreaseCentreSpeed = 0;
  m_numNormalCentreSpeed = 0;
  m_numIncreaseCircleSpeed = 0;
  m_numDecreaseCircleSpeed = 0;
  m_numNormalCircleSpeed = 0;
}

void TubeStats::Log(const GoomStats::LogStatsValueFunc& logVal) const
{
  const constexpr char* MODULE = "Tube";

  logVal(MODULE, "numResetColorMaps", m_numResetColorMaps);

  logVal(MODULE, "numAllJoinedInCentre", m_numAllJoinedInCentre);
  logVal(MODULE, "numAllMaxFromCentre", m_numAllMaxFromCentre);
  logVal(MODULE, "lastAllJoinInCentreSpeed", m_lastAllJoinInCentreSpeed);
  logVal(MODULE, "minAllJoinInCentreSpeed", m_minAllJoinInCentreSpeed);
  logVal(MODULE, "maxAllJoinInCentreSpeed", m_maxAllJoinInCentreSpeed);

  logVal(MODULE, "lastCircleSpeed", m_lastCircleSpeed);
  logVal(MODULE, "minCircleSpeed", m_minCircleSpeed);
  logVal(MODULE, "maxCircleSpeed", m_maxCircleSpeed);
  logVal(MODULE, "numIncreaseCircleSpeed", m_numIncreaseCircleSpeed);
  logVal(MODULE, "numDecreaseCircleSpeed", m_numDecreaseCircleSpeed);
  logVal(MODULE, "numNormalCircleSpeed", m_numNormalCircleSpeed);

  logVal(MODULE, "lastCentreSpeed", m_lastCentreSpeed);
  logVal(MODULE, "minCentreSpeed", m_minCentreSpeed);
  logVal(MODULE, "maxCentreSpeed", m_maxCentreSpeed);
  logVal(MODULE, "numIncreaseCentreSpeed", m_numIncreaseCentreSpeed);
  logVal(MODULE, "numDecreaseCentreSpeed", m_numDecreaseCentreSpeed);
  logVal(MODULE, "numNormalCentreSpeed", m_numNormalCentreSpeed);
}

void TubeStats::ResetColorMaps()
{
  m_numResetColorMaps++;
}

void TubeStats::AllJoinedInCentre()
{
  m_numAllJoinedInCentre++;
}

void TubeStats::AllMaxFromCentre()
{
  m_numAllMaxFromCentre++;
}

void TubeStats::UpdateAllJoinInCentreSpeed(const float val)
{
  m_lastAllJoinInCentreSpeed = val;
  if (val < m_minAllJoinInCentreSpeed)
  {
    m_minAllJoinInCentreSpeed = val;
  }
  if (val > m_maxAllJoinInCentreSpeed)
  {
    m_maxAllJoinInCentreSpeed = val;
  }
}

void TubeStats::IncreaseCircleSpeed()
{
  m_numIncreaseCircleSpeed++;
}

void TubeStats::DecreaseCircleSpeed()
{
  m_numDecreaseCircleSpeed++;
}

void TubeStats::NormalCircleSpeed()
{
  m_numNormalCircleSpeed++;
}

void TubeStats::UpdateCircleSpeed(const float val)
{
  m_lastCircleSpeed = val;
  if (val < m_minCircleSpeed)
  {
    m_minCircleSpeed = val;
  }
  if (val > m_maxCircleSpeed)
  {
    m_maxCircleSpeed = val;
  }
}

void TubeStats::IncreaseCentreSpeed()
{
  m_numIncreaseCentreSpeed++;
}

void TubeStats::DecreaseCentreSpeed()
{
  m_numDecreaseCentreSpeed++;
}

void TubeStats::NormalCentreSpeed()
{
  m_numNormalCentreSpeed++;
}

void TubeStats::UpdateCentreSpeed(const float val)
{
  m_lastCentreSpeed = val;
  if (val < m_minCentreSpeed)
  {
    m_minCentreSpeed = val;
  }
  if (val > m_maxCentreSpeed)
  {
    m_maxCentreSpeed = val;
  }
}

} // namespace GOOM
