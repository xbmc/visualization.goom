/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      Copyright (C) 2016-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */


/*

Goom Visualization Interface for Kodi
- Team Kodi

*/

#define __STDC_LIMIT_MACROS

#include <kodi/addon-instance/Visualization.h>

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <kodi/gui/gl/Shader.h>

extern "C" {
#include "goom.h"
#include "goom_config.h"
}

#include <string>
#include <thread>
#include <functional>
#include "workers.hpp"
#include "buffer_savers.hpp"


class ATTRIBUTE_HIDDEN CVisualizationGoom
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceVisualization,
    kodi::gui::gl::CShaderProgram
{
public:
  CVisualizationGoom();
  virtual ~CVisualizationGoom();

  virtual bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) override;
  virtual void Stop() override;
  virtual void Render() override;
  virtual void AudioData(const float* audioData, int audioDataLength, float* freqData, int freqDataLength) override;
  virtual bool UpdateTrack(const VisTrack &track) override;

  // kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  bool OnEnabled() override { return true; }

private:
  const static int g_tex_width = GOOM_TEXTURE_WIDTH;
  const static int g_tex_height = GOOM_TEXTURE_HEIGHT;
  const static int g_numGoomBufferElements = 4 * g_tex_width * g_tex_height;
  const static int g_goomBufferSize = g_numGoomBufferElements * sizeof(unsigned char);
  using SamplesArray = short[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN];
  const static int g_audioDataBufferLen = NUM_AUDIO_SAMPLES * AUDIO_SAMPLE_LEN;
  const static int g_audioDataBufferSize = g_audioDataBufferLen * sizeof(short);
  
  int m_window_width;
  int m_window_height;
  int m_window_xpos;
  int m_window_ypos;

  PluginInfo* m_goom;
  bool m_started;

  SamplesArray m_audioData;
  bool m_audioStarted;
  unsigned long m_numTimesAudioSampled;
  std::string m_currentSongName;

  unsigned long m_frameNum;
  const static int g_maxNumSkippedFramesInARow = 0;
  int m_numSkippedFramesInARow;
  unsigned long m_numBufferWaits;
  std::thread m_worker_thread;
  Worker m_worker;
  void UpdateGoomBuffer(const void* audioData, unsigned long audioTag, void* goomBuffer);
  void Logger(int severity, const std::string& msg);

  BufferSaver<short> m_audioBufferSaver;
  const static int g_maxNumSavedAudioBuffers = 10000;
  const static bool g_saveAudioBuffers = false;

  BufferSaver<unsigned char> m_goomBufferSaver;
  const static int g_maxNumSavedGoomBuffers = 10000;
  const static bool g_saveGoomBuffers = false;

  GLint m_componentsPerVertex;
  GLint m_componentsPerTexel;
  int m_numVertices;
  int m_numElements;
  GLfloat* m_quadData;
  void InitQuadData();

  const static bool g_usePixelBufferObjects = true;
  GLuint m_texid;
  const static int g_pixelFormat = GL_RGBA;
  const static int g_numPbos = 3;
  GLuint m_pboIds[g_numPbos];
  unsigned char* m_pboGoomBuffer[g_numPbos];
  int m_currentPboIndex;
  glm::mat4 m_projModelMatrix;
  GLuint m_vaoObject = 0;
  GLuint m_vertexVBO = 0;
  GLint m_uProjModelMatLoc = -1;
  GLint m_aPositionLoc = -1;
  GLint m_aColorLoc = -1;
  bool InitGLObjects();
};

CVisualizationGoom::CVisualizationGoom()
  : m_texid(0),
    m_started(false),
    m_frameNum(0),
    m_numSkippedFramesInARow(0),
    m_audioStarted(false),
    m_currentSongName(""),
    m_numTimesAudioSampled(0),
    m_goomBufferSaver("Goom Buffer Saver", g_maxNumSavedGoomBuffers, g_numGoomBufferElements, g_saveGoomBuffers),
    m_audioBufferSaver("Audio Buffer Saver", g_maxNumSavedAudioBuffers, g_audioDataBufferLen, g_saveAudioBuffers),
    m_worker(g_audioDataBufferSize, g_goomBufferSize)
{
  m_worker.SetInputDataProcessor(std::bind(&CVisualizationGoom::UpdateGoomBuffer, 
    this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

//  m_worker.SetLogger(std::bind(&CVisualizationGoom::Logger, this, std::placeholders::_1, std::placeholders::_2));
//  m_goomBufferSaver.SetLogger(std::bind(&CVisualizationGoom::Logger, this, std::placeholders::_1, std::placeholders::_2));
//  m_audioBufferSaver.SetLogger(std::bind(&CVisualizationGoom::Logger, this, std::placeholders::_1, std::placeholders::_2));

  m_goom = goom_init(g_tex_width, g_tex_height);
  if (!m_goom)
  {
    kodi::Log(ADDON_LOG_FATAL, "CVisualizationGoom: Goom could not be initialized!");
    return;
  }

  m_window_width = Width();
  m_window_height = Height();
  m_window_xpos = X();
  m_window_ypos = Y();

  InitQuadData();
}

//-- Destroy -------------------------------------------------------------------
// Do everything before unload of this add-on
// !!! Add-on master function !!!
//-----------------------------------------------------------------------------
CVisualizationGoom::~CVisualizationGoom()
{
  if (m_goom)
  {
    goom_close(m_goom);
    m_goom = nullptr;
  }

  delete[] m_quadData;

  kodi::Log(ADDON_LOG_DEBUG, "~CVisualizationGoom: Destroyed CVisualizationGoom object.");
}

//-- Start --------------------------------------------------------------------
// Called when a new soundtrack is played
//-----------------------------------------------------------------------------
bool CVisualizationGoom::Start(int iChannels, int iSamplesPerSec, int iBitsPerSample, std::string szSongName)
{
  if (m_started) {
    kodi::Log(ADDON_LOG_WARNING, "Start: Already started without a stop - skipping this.");
    return true;
  }

  m_started = true;
  m_audioStarted = false;
  m_numTimesAudioSampled = 0;
  m_numBufferWaits = 0;
  m_currentSongName = szSongName;
  memset(m_audioData, 0, g_audioDataBufferSize);
  
  if (!LoadShaderFiles(kodi::GetAddonPath("resources/shaders/vert.glsl"),
                       kodi::GetAddonPath("resources/shaders/frag.glsl")))
  {
    kodi::Log(ADDON_LOG_FATAL, "Start: Failed to load GL shaders.");
    return false;
  }

  if (!CompileAndLink())
  {
    kodi::Log(ADDON_LOG_FATAL, "Start: Failed to compile GL shaders.");
    return false;
  }

  if (!InitGLObjects())
  {
    kodi::Log(ADDON_LOG_FATAL, "Start: Could not intilize GL objects.");
    return false;
  }

  kodi::Log(ADDON_LOG_DEBUG, "Start: Setting up buffer worker thread.");
  m_frameNum = 0;
  m_numSkippedFramesInARow = 0;
  m_worker_thread = std::thread(&Worker::Thread, &m_worker);

  return true;
}

//-- Stop ---------------------------------------------------------------------
// Called when the visualisation is closed by Kodi
//-----------------------------------------------------------------------------
void CVisualizationGoom::Stop()
{
  if (!m_started) {
    kodi::Log(ADDON_LOG_WARNING, "Stop: Not started - skipping this.");
  }
  m_audioStarted = false;
  m_started = false;
  
  kodi::Log(ADDON_LOG_DEBUG, "Stop: Stopping processed buffers thread...");
  kodi::Log(ADDON_LOG_DEBUG, "Stop: %u processed buffers left, %u request buffers left.", 
      m_worker.ProcessedQueueLength(), m_worker.RequestsQueueLength());

  kodi::Log(ADDON_LOG_NOTICE, "Stop: There were %u frames rendered, %u audio samples, %u buffer waits, and %u audio buffers skipped.", 
    m_frameNum, m_numTimesAudioSampled, m_numBufferWaits, m_worker.NumMissedRequests());

  m_worker.Stop();
  m_worker.AddRequest(m_audioData, m_numTimesAudioSampled);
  m_worker_thread.join();
  kodi::Log(ADDON_LOG_DEBUG, "Stop: Processed buffers thread stopped.");

  m_audioBufferSaver.Write("/tmp/goom_audio_buffer_%05d", false);
  m_goomBufferSaver.Write("/tmp/goom_buffer_%05d", true);

  if (m_texid)
  {
    glDeleteTextures(1, &m_texid);
    m_texid = 0;
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
}

void CVisualizationGoom::OnCompiledAndLinked()
{
  m_uProjModelMatLoc = glGetUniformLocation(ProgramHandle(), "u_projModelMat");
  m_aPositionLoc = glGetAttribLocation(ProgramHandle(), "in_position");
  m_aColorLoc = glGetAttribLocation(ProgramHandle(), "in_tex_coord");
}

//-- Audiodata ----------------------------------------------------------------
// Called by Kodi to pass new audio data to the vis
//-----------------------------------------------------------------------------
void CVisualizationGoom::AudioData(const float* pAudioData, int iAudioDataLength, float* pFreqData, int iFreqDataLength)
{
  if (!m_started) {
    kodi::Log(ADDON_LOG_WARNING, "AudioData: Not started - skipping this.");
  }

  const int copyLen = iAudioDataLength < g_audioDataBufferLen ? iAudioDataLength : g_audioDataBufferLen;
  if (copyLen < g_audioDataBufferLen) {
    memset(m_audioData, 0, g_audioDataBufferSize);
  }
  int i = 0;
  for(int ipos = 0; ipos < copyLen; ipos += 2)
  {
    m_audioData[0][i] = static_cast<int>(pAudioData[ipos] * (INT16_MAX + 0.5f));
    m_audioData[1][i] = static_cast<int>(pAudioData[ipos + 1] * (INT16_MAX + 0.5f));
    i++;
  }

  m_numTimesAudioSampled++;
  m_worker.AddRequest(m_audioData, m_numTimesAudioSampled);
  m_worker.AddRequest(m_audioData, m_numTimesAudioSampled);

  if (!m_audioStarted) {
    m_audioStarted = true;
    kodi::Log(ADDON_LOG_DEBUG, "AudioData: Audio now started - Used *(%u + 0.5) as short conversion factor.", INT16_MAX);
  }
}

bool CVisualizationGoom::UpdateTrack(const VisTrack &track)
{
  if (m_goom)
  {
    m_currentSongName = track.title;
  }
  return true;
}


void CVisualizationGoom::InitQuadData() {
  GLfloat x0 = m_window_xpos;
  GLfloat y0 = m_window_ypos;
  GLfloat x1 = m_window_xpos + m_window_width;
  GLfloat y1 = m_window_ypos + m_window_height;
  const GLfloat tempQuadData[] =
  {
      // Vertex positions
      x0, y0,  // bottom left
      x0, y1,  // top left
      x1, y0,  // bottom right
      x1, y0,  // bottom right
      x1, y1,  // top right
      x0, y1,  // top left
      // Texture coordinates
      0.0, 1.0,
      0.0, 0.0,
      1.0, 1.0,
      1.0, 1.0,
      1.0, 0.0,
      0.0, 0.0,
  };
  m_numElements = sizeof(tempQuadData)/sizeof(GLfloat);
  m_quadData = new GLfloat[m_numElements];
  for (int i = 0; i < m_numElements; i++)
  {
    m_quadData[i] = tempQuadData[i];
  };
  m_componentsPerVertex = 2; 
  m_componentsPerTexel = 2; 
  m_numVertices = 2 * 3; // 2 triangles
  m_vertexVBO = 0;
}

bool CVisualizationGoom::InitGLObjects() {
  m_projModelMatrix = glm::ortho(0.0f, float(Width()), 0.0f, float(Height()));

  // Setup vertex attributes
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  glGenVertexArrays(1, &m_vaoObject);
  glBindVertexArray(m_vaoObject);
  glGenBuffers(1, &m_vertexVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);  
  glVertexAttribPointer(0, m_componentsPerVertex, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glVertexAttribPointer(1, m_componentsPerTexel, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(m_numVertices * m_componentsPerVertex * sizeof(GLfloat)));
  glBufferData(GL_ARRAY_BUFFER, m_numElements*sizeof(GLfloat), m_quadData, GL_STATIC_DRAW);
  glBindVertexArray(0);

  // Create texture.
  glGenTextures(1, &m_texid);
  if (!m_texid) {
    kodi::Log(ADDON_LOG_ERROR, "InitGLObjects: Could not do glGenTextures.");
    return false;
  }
  glClear(GL_COLOR_BUFFER_BIT);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_texid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glGenerateMipmap(GL_TEXTURE_2D);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_tex_width, g_tex_height, 0, g_pixelFormat, GL_UNSIGNED_BYTE, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (!g_usePixelBufferObjects) {
    kodi::Log(ADDON_LOG_DEBUG, "InitGLObjects: Not using pixel buffer objects.");
  } else {  
    kodi::Log(ADDON_LOG_DEBUG, "InitGLObjects: Using pixel buffer objects.");
    m_currentPboIndex = 0;

    glGenBuffers(g_numPbos, m_pboIds);
    for (int i = 0; i < g_numPbos; i++) {
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[i]);
      glBufferData(GL_PIXEL_UNPACK_BUFFER, g_goomBufferSize, 0, GL_STREAM_DRAW);
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[i]);
      glBufferData(GL_PIXEL_UNPACK_BUFFER, g_goomBufferSize, 0, GL_STREAM_DRAW);
      m_pboGoomBuffer[i] = reinterpret_cast<unsigned char*>(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
      if (!m_pboGoomBuffer[i]) {
        kodi::Log(ADDON_LOG_ERROR, "InitGLObjects: Could not do glMapBuffer for pbo %d.", i);
        return false;
      }
    }
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  }

  return true;
}

//-- Render -------------------------------------------------------------------
// Called once per frame. Do all rendering here.
//-----------------------------------------------------------------------------

void CVisualizationGoom::Render()
{
    if (!m_started) {
      kodi::Log(ADDON_LOG_WARNING, "Render: Not started - skipping this.");
    }
    if (!m_audioStarted) {
      kodi::Log(ADDON_LOG_DEBUG, "Render: Audio not started yet - skipping this.");
      return;
    }  
    if (!m_texid) {
      kodi::Log(ADDON_LOG_ERROR, "Render: Texture has not been initialized.");
      return;
    }  

    auto dataPackagePtr = m_worker.ProcessedTryPop();
    if (dataPackagePtr != nullptr) {
      // kodi::Log(ADDON_LOG_DEBUG, "Render: Successfully popped buffer.");
      m_frameNum++;
    } else {  
      // kodi::Log(ADDON_LOG_DEBUG, "Render: No processed buffers ready.");
      if (m_worker.RequestsQueueEmpty()) {
        m_worker.AddRequest(m_audioData, m_numTimesAudioSampled);
      }
      m_numSkippedFramesInARow++;
      if (m_numSkippedFramesInARow <= g_maxNumSkippedFramesInARow) {
        kodi::Log(ADDON_LOG_DEBUG, "Render: No processed buffers ready - skipping this render. (m_numSkippedFramesInARow = %d.)", 
          m_numSkippedFramesInARow);
      } else {  
        // kodi::Log(ADDON_LOG_DEBUG, "Render: Wait for finished processed buffer. (m_numSkippedFramesInARow = %d.)", 
        //  m_numSkippedFramesInARow);
        dataPackagePtr = m_worker.ProcessedPop();
        // kodi::Log(ADDON_LOG_DEBUG, "Render: Successfully popped buffer with tag %lu after wait.", dataPackagePtr->GetTag());
        m_numSkippedFramesInARow = 0;
        m_numBufferWaits++;
        m_frameNum++;
      }
    }

    // Setup vertex attributes.
    glBindVertexArray(m_vaoObject);
      
    // Setup texture.
    glBindTexture(GL_TEXTURE_2D, m_texid);
    if (dataPackagePtr != nullptr) {
      if (!g_usePixelBufferObjects) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_tex_width, g_tex_height, g_pixelFormat, GL_UNSIGNED_BYTE, dataPackagePtr->GetData());
        dataPackagePtr->SetFinishedWith();
      } else {
        m_currentPboIndex = (m_currentPboIndex + 1) % g_numPbos;
        const int nextPboIndex = (m_currentPboIndex + 1) % g_numPbos;

        // Bind to current PBO and send pixels to texture object.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[m_currentPboIndex]);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_tex_width, g_tex_height, g_pixelFormat, GL_UNSIGNED_BYTE, 0);

        // Bind to next PBO and update data directly on the mapped buffer.
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[nextPboIndex]);
        memcpy(m_pboGoomBuffer[nextPboIndex], dataPackagePtr->GetData(), g_goomBufferSize);
        dataPackagePtr->SetFinishedWith();

        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
      }
    }  
    
    delete dataPackagePtr;

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);

    EnableShader();
    glUniformMatrix4fv(m_uProjModelMatLoc, 1, GL_FALSE, glm::value_ptr(m_projModelMatrix));
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    DisableShader();

    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBindVertexArray(0);
}

void CVisualizationGoom::UpdateGoomBuffer(const void* audioData, unsigned long audioTag, void* goomBuffer) 
{
    const char* title = nullptr;
    if (m_currentSongName != "") {
      title = m_currentSongName.c_str();
      kodi::Log(ADDON_LOG_DEBUG, "UpdateGoomBuffer: Setting song title '%s'.", title);
    }

    goom_set_screenbuffer(m_goom, goomBuffer);
    goom_update(m_goom, reinterpret_cast<const SamplesArray&>(audioData), 0, 0, title, (char*)"Kodi");

    m_currentSongName = "";

    m_goomBufferSaver.Save(reinterpret_cast<const unsigned char*>(goomBuffer), audioTag);
    m_audioBufferSaver.Save(reinterpret_cast<const short*>(audioData), audioTag);
}

void CVisualizationGoom::Logger(int severity, const std::string& msg)
{
    kodi::Log(ADDON_LOG_DEBUG, msg.c_str());
}

ADDONCREATOR(CVisualizationGoom) // Don't touch this!
