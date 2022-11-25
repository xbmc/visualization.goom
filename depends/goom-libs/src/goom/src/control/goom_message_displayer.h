#pragma once

#include "draw/text_draw.h"

#include <string>
#include <vector>

namespace GOOM
{

namespace DRAW
{
class IGoomDraw;
}
namespace UTILS
{
class Parallel;
}

namespace CONTROL
{

class GoomMessageDisplayer
{
public:
  GoomMessageDisplayer(DRAW::IGoomDraw& textOutput, const std::string& updateMessagesFontFile);

  void UpdateMessages(const std::vector<std::string>& msgLines);

private:
  UTILS::Parallel& m_parallel;
  DRAW::IGoomDraw& m_textOutput;
  const std::string m_updateMessagesFontFile;

  static constexpr int32_t MSG_FONT_SIZE         = 10;
  static constexpr size_t DEFAULT_NUM_DISPLAYERS = 1;
  std::vector<DRAW::TextDraw> m_updateMessagesDisplayers{
      GetUpdateMessagesDisplayers(DEFAULT_NUM_DISPLAYERS, m_textOutput, m_updateMessagesFontFile)};
  [[nodiscard]] static auto GetUpdateMessagesDisplayers(size_t numDisplayers,
                                                        DRAW::IGoomDraw& textOutput,
                                                        const std::string& updateMessagesFontFile)
      -> std::vector<DRAW::TextDraw>;
};

} // namespace CONTROL
} // namespace GOOM
