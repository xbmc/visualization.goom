/*
 *  Copyright (C) 2005-2020 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005-2013 Team XBMC
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#define __STDC_LIMIT_MACROS

#include "CircularBuffer.h"

extern "C"
{
#include "goom.h"
#include "goom_config.h"
}

#include <condition_variable>
#include <functional>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <kodi/General.h>
#include <kodi/addon-instance/Visualization.h>
#include <kodi/gui/gl/Shader.h>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#define GOOM_TEXTURE_WIDTH 1280
#define GOOM_TEXTURE_HEIGHT 720

class ATTRIBUTE_HIDDEN CVisualizationGoom : public kodi::addon::CAddonBase,
                                            public kodi::addon::CInstanceVisualization,
                                            private kodi::gui::gl::CShaderProgram
{
public:
  CVisualizationGoom();
  ~CVisualizationGoom() override;

  bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) override;
  void Stop() override;
  bool IsDirty() override;
  void Render() override;
  void AudioData(const float* audioData,
                 int audioDataLength,
                 float* freqData,
                 int freqDataLength) override;
  bool UpdateTrack(const kodi::addon::VisualizationTrack& track) override;

  // kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  bool OnEnabled() override;

protected:
  virtual void UpdateGoomBuffer(const char* title, const float floatAudioData[], uint32_t* pixels);
  int m_goomBufferLen;
  int m_audioBufferLen;

private:
  void Process();
  bool InitGLObjects();
  void InitQuadData();
  std::shared_ptr<uint32_t> GetNextActivePixels();
  void PushUsedPixels(std::shared_ptr<uint32_t> pixels);

  int m_tex_width = GOOM_TEXTURE_WIDTH;
  int m_tex_height = GOOM_TEXTURE_HEIGHT;
  size_t m_goomBufferSize;

  int m_window_width;
  int m_window_height;
  int m_window_xpos;
  int m_window_ypos;

  int m_channels;
  std::string m_currentSongName;
  std::string m_lastSongName;
  bool m_titleChange = false;
  bool m_showTitleAlways = false;

  GLint m_componentsPerVertex;
  GLint m_componentsPerTexel;
  int m_numVertices;
  int m_numElements;
  GLfloat* m_quadData = nullptr;

#ifdef HAS_GL
  bool m_usePixelBufferObjects =
      false; // 'true' is supposed to give better performance but it's not obvious.
      // And when 'true', there may be issues with screen refreshes when changing windows in Kodi.
#endif
  GLuint m_textureId = 0;
  const static int g_numPbos = 3;
  GLuint m_pboIds[g_numPbos];
  unsigned char* m_pboGoomBuffer[g_numPbos];
  int m_currentPboIndex;
  glm::mat4 m_projModelMatrix;
  GLuint m_vaoObject = 0;
  GLuint m_vertexVBO = 0;
  GLint m_uProjModelMatLoc = -1;
  GLint m_aPositionLoc = -1;
  GLint m_aCoordLoc = -1;

  // Goom's data itself
  PluginInfo* m_goom = nullptr;

  // Audio buffer storage
  const static size_t g_circular_buffer_size = 16 * NUM_AUDIO_SAMPLES * AUDIO_SAMPLE_LEN;
  circular_buffer<float> m_buffer = g_circular_buffer_size;

  // Goom process thread handles
  bool m_threadExit = false;
  std::thread m_workerThread;
  std::mutex m_mutex;
  std::condition_variable m_wait;

  // Screen frames storage, m_activeQueue for next view and m_storedQueue to
  // use on next goom round become active again.
  static constexpr size_t g_maxActiveQueueLength = 20;
  std::queue<std::shared_ptr<uint32_t>> m_activeQueue;
  std::queue<std::shared_ptr<uint32_t>> m_storedQueue;

  // Start flag to know init was OK
  bool m_started = false;
};
