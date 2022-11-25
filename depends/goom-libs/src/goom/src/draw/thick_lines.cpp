// NOLINTBEGIN: Not my code

#include "thick_lines.h"

#include "goom_config.h"

#include <cmath>
#include <cstdint>

namespace GOOM::DRAW
{

static void DrawXVariableThicknessLine(const PlotPointFunc& plot,
                                       int32_t x0,
                                       int32_t y0,
                                       int32_t dx,
                                       int32_t dy,
                                       int32_t xStep,
                                       int32_t yStep,
                                       const GetLineWidthFunc& getLeftWidth,
                                       const GetLineWidthFunc& getRightWidth,
                                       int32_t pxStep,
                                       int32_t pyStep);
static void DrawYVariableThicknessLine(const PlotPointFunc& plot,
                                       int32_t x0,
                                       int32_t y0,
                                       int32_t dx,
                                       int32_t dy,
                                       int32_t xStep,
                                       int32_t yStep,
                                       const GetLineWidthFunc& getLeftWidth,
                                       const GetLineWidthFunc& getRightWidth,
                                       int32_t pxStep,
                                       int32_t pyStep);
static void DrawXPerpendicular(const PlotPointFunc& plot,
                               int32_t x0,
                               int32_t y0,
                               int32_t dx,
                               int32_t dy,
                               int32_t xStep,
                               int32_t yStep,
                               int32_t eInit,
                               int32_t widthLeft,
                               int32_t widthRight,
                               int32_t widthInit);
static void DrawYPerpendicular(const PlotPointFunc& plot,
                               int32_t x0,
                               int32_t y0,
                               int32_t dx,
                               int32_t dy,
                               int32_t xStep,
                               int32_t yStep,
                               int32_t eInit,
                               int32_t widthLeft,
                               int32_t widthRight,
                               int32_t widthInit);

/***********************************************************************
 *                                                                     *
 *                                ENTRY                                *
 *                                                                     *
 ***********************************************************************/

auto DrawVariableThicknessLine(const PlotPointFunc& plot,
                               const int32_t x0,
                               const int32_t y0,
                               const int32_t x1,
                               const int32_t y1,
                               GetLineWidthFunc getLeftWidth,
                               GetLineWidthFunc getRightWidth) noexcept -> void
{
  auto dx = x1 - x0;
  auto dy = y1 - y0;

  if ((0 == dx) and (0 == dy))
  {
    plot(x0, y0);
    return;
  }

  auto xStep = 1;
  if (0 == dx)
  {
    xStep = 0;
  }
  else if (dx < 0)
  {
    dx    = -dx;
    xStep = -1;
  }

  auto yStep = 1;
  if (0 == dy)
  {
    yStep = 0;
  }
  else if (dy < 0)
  {
    dy    = -dy;
    yStep = -1;
  }

  auto swapLeftRightWidthFuncs = false;
  int32_t pxStep = 0;
  int32_t pyStep = 0;
  switch (xStep + (yStep * 4))
  {
    case -1 + (-1 * 4):
      pyStep                  = -1;
      pxStep                  = +1;
      swapLeftRightWidthFuncs = true;
      break; // -5
    case -1 + (0 * 4):
      pyStep                  = -1;
      pxStep                  = 0;
      swapLeftRightWidthFuncs = true;
      break; // -1
    case -1 + (1 * 4):
      pyStep = +1;
      pxStep = +1;
      break; // 3
    case 0 + (-1 * 4):
      pyStep = 0;
      pxStep = -1;
      break; // -4
    case 0 + (0 * 4):
      pyStep = 0;
      pxStep = 0;
      break; // 0
    case 0 + (1 * 4):
      pyStep = 0;
      pxStep = +1;
      break; // 4
    case 1 + (-1 * 4):
      pyStep = -1;
      pxStep = -1;
      break; // -3
    case 1 + (0 * 4):
      pyStep = -1;
      pxStep = 0;
      break; // 1
    case 1 + (1 * 4):
      pyStep                  = +1;
      pxStep                  = -1;
      swapLeftRightWidthFuncs = true;
      break; // 5
    default:
      FailFast();
  }

  if (swapLeftRightWidthFuncs)
  {
    std::swap(getLeftWidth, getRightWidth);
  }

  if (dx > dy)
  {
    DrawXVariableThicknessLine(
        plot, x0, y0, dx, dy, xStep, yStep, getLeftWidth, getRightWidth, pxStep, pyStep);
  }
  else
  {
    DrawYVariableThicknessLine(
        plot, x0, y0, dx, dy, xStep, yStep, getLeftWidth, getRightWidth, pxStep, pyStep);
  }
}

/***********************************************************************
 *                                                                     *
 *                            X BASED LINES                            *
 *                                                                     *
 ***********************************************************************/

static void DrawXPerpendicular(const PlotPointFunc& plot,
                               const int32_t x0,
                               const int32_t y0,
                               const int32_t dx,
                               const int32_t dy,
                               const int32_t xStep,
                               const int32_t yStep,
                               const int32_t eInit,
                               const int32_t widthLeft,
                               const int32_t widthRight,
                               const int32_t widthInit)
{
  const auto threshold = dx - (2 * dy);
  const auto eDiag     = -2 * dx;
  const auto eSquare   = 2 * dy;

  auto error = eInit;
  auto tk    = (dx + dy) - widthInit;
  auto x     = x0;
  auto y     = y0;

  auto pointNum1 = 0U;
  while (tk <= widthLeft)
  {
    plot(x, y);
    if (error >= threshold)
    {
      x     = x + xStep;
      error = error + eDiag;
      tk    = tk + (2 * dy);
    }
    error = error + eSquare;
    y     = y + yStep;
    tk    = tk + (2 * dx);
    ++pointNum1;
  }

  x     = x0;
  y     = y0;
  error = -eInit;
  tk    = (dx + dy) + widthInit;

  auto pointNum2 = 0U;
  while (tk <= widthRight)
  {
    if (pointNum2 > 0)
    {
      plot(x, y);
    }
    if (error > threshold)
    {
      x     = x - xStep;
      error = error + eDiag;
      tk    = tk + (2 * dy);
    }
    error = error + eSquare;
    y     = y - yStep;
    tk    = tk + (2 * dx);
    ++pointNum2;
  }

  if ((0 == pointNum1) and (pointNum2 < 2))
  {
    plot(x0, y0); // we need this for very thin lines
  }
}

static void DrawXVariableThicknessLine(const PlotPointFunc& plot,
                                       const int32_t x0,
                                       const int32_t y0,
                                       const int32_t dx,
                                       const int32_t dy,
                                       const int32_t xStep,
                                       const int32_t yStep,
                                       const GetLineWidthFunc& getLeftWidth,
                                       const GetLineWidthFunc& getRightWidth,
                                       const int32_t pxStep,
                                       const int32_t pyStep)
{
  const auto threshold  = dx - (2 * dy);
  const auto eDiag      = -2 * dx;
  const auto eSquare    = 2 * dy;
  const auto lineLength = dx + 1;
  const auto D          = std::sqrt(static_cast<double>((dx * dx) + (dy * dy)));

  auto pError = 0;
  auto error  = 0;
  auto x      = x0;
  auto y      = y0;

  for (auto pointNum = 0; pointNum < lineLength; ++pointNum)
  {
    const auto widthLeft  = (2.0 * D) * getLeftWidth(pointNum, lineLength);
    const auto widthRight = (2.0 * D) * getRightWidth(pointNum, lineLength);

    DrawXPerpendicular(plot,
                       x,
                       y,
                       dx,
                       dy,
                       pxStep,
                       pyStep,
                       pError,
                       static_cast<int32_t>(widthLeft),
                       static_cast<int32_t>(widthRight),
                       error);

    if (error >= threshold)
    {
      y     = y + yStep;
      error = error + eDiag;
      if (pError >= threshold)
      {
        DrawXPerpendicular(plot,
                           x,
                           y,
                           dx,
                           dy,
                           pxStep,
                           pyStep,
                           (pError + eDiag + eSquare),
                           static_cast<int32_t>(widthLeft),
                           static_cast<int32_t>(widthRight),
                           error);
        pError = pError + eDiag;
      }
      pError = pError + eSquare;
    }
    error = error + eSquare;
    x     = x + xStep;
  }
}

/***********************************************************************
 *                                                                     *
 *                            Y BASED LINES                            *
 *                                                                     *
 ***********************************************************************/

static void DrawYPerpendicular(const PlotPointFunc& plot,
                               const int32_t x0,
                               const int32_t y0,
                               const int32_t dx,
                               const int32_t dy,
                               const int32_t xStep,
                               const int32_t yStep,
                               const int32_t eInit,
                               const int32_t widthLeft,
                               const int32_t widthRight,
                               const int32_t widthInit)
{
  const auto threshold = dy - (2 * dx);
  const auto eDiag     = -2 * dy;
  const auto eSquare   = 2 * dx;

  auto error = -eInit;
  auto tk    = (dx + dy) + widthInit;
  auto x     = x0;
  auto y     = y0;

  auto pointNum1 = 0;
  while (tk <= widthLeft)
  {
    plot(x, y);
    if (error > threshold)
    {
      y     = y + yStep;
      error = error + eDiag;
      tk    = tk + (2 * dx);
    }
    error = error + eSquare;
    x     = x + xStep;
    tk    = tk + (2 * dy);
    ++pointNum1;
  }


  x     = x0;
  y     = y0;
  error = eInit;
  tk    = (dx + dy) - widthInit;

  auto pointNum2 = 0;
  while (tk <= widthRight)
  {
    if (pointNum2 > 0)
    {
      plot(x, y);
    }
    if (error >= threshold)
    {
      y     = y - yStep;
      error = error + eDiag;
      tk    = tk + (2 * dx);
    }
    error = error + eSquare;
    x     = x - xStep;
    tk    = tk + (2 * dy);
    ++pointNum2;
  }

  if ((0 == pointNum1) and (pointNum2 < 2))
  {
    plot(x0, y0); // we need this for very thin lines
  }
}


static void DrawYVariableThicknessLine(const PlotPointFunc& plot,
                                       const int32_t x0,
                                       const int32_t y0,
                                       const int32_t dx,
                                       const int32_t dy,
                                       const int32_t xStep,
                                       const int32_t yStep,
                                       const GetLineWidthFunc& getLeftWidth,
                                       const GetLineWidthFunc& getRightWidth,
                                       const int32_t pxStep,
                                       const int32_t pyStep)
{
  const auto threshold  = dy - (2 * dx);
  const auto eDiag      = -2 * dy;
  const auto eSquare    = 2 * dx;
  const auto lineLength = dy + 1;
  const auto D          = std::sqrt(static_cast<double>((dx * dx) + (dy * dy)));

  auto pError = 0;
  auto error  = 0;
  auto x      = x0;
  auto y      = y0;
  for (auto pointNum = 0; pointNum < lineLength; ++pointNum)
  {
    const auto widthLeft  = (2.0 * D) * getLeftWidth(pointNum, lineLength);
    const auto widthRight = (2.0 * D) * getRightWidth(pointNum, lineLength);

    DrawYPerpendicular(plot,
                       x,
                       y,
                       dx,
                       dy,
                       pxStep,
                       pyStep,
                       pError,
                       static_cast<int32_t>(widthLeft),
                       static_cast<int32_t>(widthRight),
                       error);

    if (error >= threshold)
    {
      x = x + xStep;

      error = error + eDiag;
      if (pError >= threshold)
      {
        DrawYPerpendicular(plot,
                           x,
                           y,
                           dx,
                           dy,
                           pxStep,
                           pyStep,
                           pError + eDiag + eSquare,
                           static_cast<int32_t>(widthLeft),
                           static_cast<int32_t>(widthRight),
                           error);
        pError = pError + eDiag;
      }
      pError = pError + eSquare;
    }

    error = error + eSquare;
    y     = y + yStep;
  }
}

} // namespace GOOM::DRAW

// NOLINTEND
