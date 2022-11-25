#pragma once

#include "goom_types.h"
#include "spimpl.h"

#include <cstdint>
#include <string>

namespace GOOM
{

class AudioSamples;
class PixelBuffer;
struct GoomShaderEffects;

class GoomControl
{
public:
  static auto GetRandSeed() -> uint64_t;
  static void SetRandSeed(uint64_t seed);

  GoomControl() noexcept = delete;
  GoomControl(const Dimensions& dimensions, const std::string& resourcesDirectory);

  enum class ShowTitleType
  {
    AT_START,
    ALWAYS,
    NEVER,
  };
  auto SetShowTitle(ShowTitleType value) -> void;

  auto Start() -> void;
  auto Finish() -> void;

  struct SongInfo
  {
    std::string title{};
    std::string genre{};
    uint32_t duration{};
  };
  auto SetSongInfo(const SongInfo& songInfo) -> void;

  auto SetScreenBuffer(const std::shared_ptr<PixelBuffer>& buffer) -> void;
  auto NoZooms(bool value) -> void;
  auto ShowGoomState(bool value) -> void;
  auto SetDumpDirectory(const std::string& dumpDirectory) -> void;

  /*
   * Update the next goom buffer.
   *
   */
  auto Update(const AudioSamples& audioSamples, const std::string& message = "") -> void;

  [[nodiscard]] auto GetLastShaderEffects() const -> const GoomShaderEffects&;

  [[nodiscard]] static auto GetCompilerVersion() -> std::string;
  [[nodiscard]] static auto GetGoomVersionInfo() -> std::string;
  [[nodiscard]] static auto GetGoomLibBuildTime() -> std::string;

private:
  class GoomControlImpl;
  spimpl::unique_impl_ptr<GoomControlImpl> m_pimpl;
};

} // namespace GOOM
