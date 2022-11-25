#pragma once

/*
 *  Copyright (C) 2005-2022 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005-2013 Team XBMC
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

//#define SAVE_AUDIO_BUFFERS

#include "CircularBuffer.h"
#include "goom/goom_config.h"
#include "goom/goom_control.h"
#include "goom/goom_graphic.h"
#include "goom/sound_info.h"
#ifdef SAVE_AUDIO_BUFFERS
#include "src/goom/src/utils/buffer_saver.h"
#endif

#include <array>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <glm/gtc/type_ptr.hpp>
#include <kodi/addon-instance/Visualization.h>
#ifdef TARGET_DARWIN
#define GL_SILENCE_DEPRECATION
#endif
#include <kodi/gui/gl/Shader.h>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

// TODO Fix this properly!
#if !defined(ATTRIBUTE_HIDDEN)
#define ATTRIBUTE_HIDDEN
#endif

class ATTRIBUTE_HIDDEN CVisualizationGoom : public kodi::addon::CAddonBase,
                                            public kodi::addon::CInstanceVisualization,
                                            public kodi::gui::gl::CShaderProgram
{
public:
  CVisualizationGoom();
  CVisualizationGoom(const CVisualizationGoom&) noexcept = delete;
  CVisualizationGoom(CVisualizationGoom&&) noexcept      = delete;
  ~CVisualizationGoom() override;
  auto operator=(const CVisualizationGoom&) -> CVisualizationGoom& = delete;
  auto operator=(CVisualizationGoom&&) -> CVisualizationGoom&      = delete;

  [[nodiscard]] auto Start(int numChannels,
                           int samplesPerSec,
                           int bitsPerSample,
                           const std::string& songName) -> bool override;
  void Stop() override;
  [[nodiscard]] auto IsDirty() -> bool override;
  void Render() override;
  void AudioData(const float* audioData, size_t audioDataLength) override;
  [[nodiscard]] auto UpdateTrack(const kodi::addon::VisualizationTrack& track) -> bool override;

  // kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  [[nodiscard]] auto OnEnabled() -> bool override;

protected:
  static constexpr size_t MAX_ACTIVE_QUEUE_LENGTH = 20;
  struct PixelBufferData
  {
    std::shared_ptr<GOOM::PixelBuffer> pixelBuffer;
    GOOM::GoomShaderEffects goomShaderEffects;
  };

  static constexpr size_t NUM_AUDIO_BUFFERS_IN_CIRCULAR_BUFFER = 16;
  [[nodiscard]] auto GetGoomControl() const -> const GOOM::GoomControl& { return *m_goomControl; };
  [[nodiscard]] auto GetGoomControl() -> GOOM::GoomControl& { return *m_goomControl; };
  [[nodiscard]] auto AudioBufferLen() const -> size_t { return m_audioBufferLen; };
  [[nodiscard]] auto TexWidth() const -> uint32_t { return m_textureWidth; };
  [[nodiscard]] auto TexHeight() const -> uint32_t { return m_textureHeight; };
  [[nodiscard]] auto GoomBufferLen() const -> size_t { return m_goomBufferLen; };
  [[nodiscard]] auto NumChannels() const -> size_t { return m_numChannels; };
  virtual void NoActiveBufferAvailable() {}
  virtual void AudioDataQueueTooBig() {}
  virtual void SkippedAudioData() {}
  virtual void AudioDataIncorrectReadLength() {}
  virtual void UpdateGoomBuffer(const std::vector<float>& floatAudioData,
                                PixelBufferData& pixelBufferData);

private:
  const int32_t m_windowWidth;
  const int32_t m_windowHeight;
  const int32_t m_windowXPos;
  const int32_t m_windowYPos;

  const uint32_t m_textureWidth;
  const uint32_t m_textureHeight;
  const size_t m_goomBufferLen;
  const size_t m_goomBufferSize;

  size_t m_numChannels                                        = 0;
  size_t m_audioBufferLen                                     = 0;
  uint32_t m_audioBufferNum                                   = 0;
  static constexpr uint32_t MIN_AUDIO_BUFFERS_BEFORE_STARTING = 6;

  const GOOM::GoomControl::ShowTitleType m_showTitle;

  const GLint m_componentsPerVertex = 2;
#ifdef HAS_GL
  const GLint m_componentsPerTexel = 2;
#endif
  static constexpr int32_t NUM_VERTICES_IN_TRIANGLE = 3;
  static constexpr int32_t NUM_TRIANGLES            = 2;
  const int32_t m_numVertices                       = NUM_TRIANGLES * NUM_VERTICES_IN_TRIANGLE;
  const std::vector<GLfloat> m_quadData;
  [[nodiscard]] static auto GetGlQuadData(int32_t width, int32_t height, int32_t xPos, int32_t yPos)
      -> std::vector<GLfloat>;

  GLuint m_textureId = 0;
#ifdef HAS_GL
  const bool m_usePixelBufferObjects;
  // Note: 'true' is supposed to give better performance, but it's not obvious.
  // And when 'true', there may be issues with screen refreshes when changing windows in Kodi.
  [[nodiscard]] auto SetupGlPixelBufferObjects() -> bool;
  void RenderGlPBOPixelBuffer(const GOOM::PixelBuffer& pixelBuffer);
  static constexpr int32_t G_NUM_PBOS = 3;
  std::array<GLuint, G_NUM_PBOS> m_pboIds{};
  std::array<uint8_t*, G_NUM_PBOS> m_pboGoomBuffer{};
  size_t m_currentPboIndex = 0;
  GLuint m_vaoObject       = 0;
#endif
  glm::mat4 m_projModelMatrix{};
  GLuint m_vertexVBO                     = 0;
  GLint m_uProjModelMatLoc               = -1;
  GLint m_aPositionLoc                   = -1;
  GLint m_aTexCoordsLoc                  = -1;
  GLint m_uTexExposureLoc                = -1;
  GLint m_uTexBrightnessLoc              = -1;
  GLint m_uTexContrastLoc                = -1;
  GLint m_uTexContrastMinChannelValueLoc = -1;
  GLint m_uTexHueShiftLerpTLoc           = -1;
  GLint m_uTexSrceHueShiftLoc            = -1;
  GLint m_uTexDestHueShiftLoc            = -1;
  GLint m_uTimeLoc                       = -1;

  // The Goom object
  std::unique_ptr<GOOM::GoomControl> m_goomControl{};

  // Audio buffer storage
  static constexpr size_t CIRCULAR_BUFFER_SIZE = NUM_AUDIO_BUFFERS_IN_CIRCULAR_BUFFER *
                                                 GOOM::AudioSamples::NUM_AUDIO_SAMPLES *
                                                 GOOM::AudioSamples::AUDIO_SAMPLE_LEN;
  CircularBuffer<float> m_audioBuffer{CIRCULAR_BUFFER_SIZE};

  // Goom process thread handles
  bool m_workerThreadExit = false;
  std::thread m_workerThread{};
  std::mutex m_mutex{};
  std::condition_variable m_wait{};

  void SetNumChannels(int numChannels);
  static void StartLogging();
  [[nodiscard]] auto InitGoomController() -> bool;
  void DeinitGoomController();
  void StartGoomProcessBuffersThread();
  void StopGoomProcessBuffersThread();
  void ExitWorkerThread();
  void Process();
  [[nodiscard]] auto GetNextActivePixelBufferData() -> PixelBufferData;
  void PushUsedPixels(const PixelBufferData& pixelBufferData);

  [[nodiscard]] auto InitGl() -> bool;
  void DeinitGl();
  [[nodiscard]] auto InitGlShaders() -> bool;
  [[nodiscard]] auto InitGlObjects() -> bool;
  void InitGlVertexAttributes();
  void InitVertexAttributes() const;
  void DeinitVertexAttributes() const;
  [[nodiscard]] auto CreateGlTexture() -> bool;
  void DrawGlTexture();
  void RenderGlPixelBuffer(const GOOM::PixelBuffer& pixelBuffer);
  void RenderGlNormalPixelBuffer(const GOOM::PixelBuffer& pixelBuffer) const;
  void SetGlShaderValues(const GOOM::GoomShaderEffects& goomShaderEffects) const;

  [[nodiscard]] auto MakePixelBufferData() const -> PixelBufferData;
  // Screen frames storage: m_activeQueue for next view and m_storedQueue to
  // use on next goom update.
  std::queue<PixelBufferData> m_activeQueue{};
  std::queue<PixelBufferData> m_storedQueue{};
  void StartActiveQueue();

  // Start flag to know init was OK
  bool m_started = false;

  [[nodiscard]] auto StartWithCatch(int numChannels,
                                    int samplesPerSec,
                                    int bitsPerSample,
                                    const std::string& songName) -> bool;
  [[nodiscard]] auto StartWithNoCatch(int numChannels,
                                      int samplesPerSec,
                                      int bitsPerSample,
                                      const std::string& songName) -> bool;
  [[nodiscard]] auto StartVis(int numChannels,
                              int samplesPerSec,
                              int bitsPerSample,
                              const std::string& songName) -> bool;

  void StopWithCatch();
  void StopWithNoCatch();
  void StopVis();

  void ProcessWithCatch();
  void ProcessWithNoCatch();
  void ProcessVis();

#ifdef SAVE_AUDIO_BUFFERS
  using AudioBufferWriter = GOOM::UTILS::BufferSaver<float>;
  [[nodiscard]] static auto GetAudioBufferWriter(const std::string& songName)
      -> std::unique_ptr<AudioBufferWriter>;
  std::unique_ptr<AudioBufferWriter> m_audioBufferWriter{};
  auto SaveAudioBuffer(const std::vector<float>& floatAudioData) -> void;
#endif

  static void HandleError(const std::string& errorMsg);
};
