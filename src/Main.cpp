/*
 *  Copyright (C) 2005-2020 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005-2013 Team XBMC
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "Main.h"

CVisualizationGoom::CVisualizationGoom()
{
  switch (kodi::GetSettingInt("quality"))
  {
  case 0:
    m_tex_width = 512;
    m_tex_height = 256;
    break;
  case 1:
    m_tex_width = 640;
    m_tex_height = 360;
    break;
  case 2:
    m_tex_width = 1280;
    m_tex_height = 720;
    break;
  default:
    m_tex_width = GOOM_TEXTURE_WIDTH;
    m_tex_height = GOOM_TEXTURE_HEIGHT;
    break;
  }

  m_goomBufferSize = m_tex_width * m_tex_height * sizeof(uint32_t);

#ifdef HAS_GL
  m_usePixelBufferObjects = kodi::GetSettingBoolean("use_pixel_buffer_objects");
#endif

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
  delete[] m_quadData;

  kodi::Log(ADDON_LOG_DEBUG, "~CVisualizationGoom: Destroyed CVisualizationGoom object.");
}

//-- Start --------------------------------------------------------------------
// Called when a new soundtrack is played
//-----------------------------------------------------------------------------
bool CVisualizationGoom::Start(int iChannels, int iSamplesPerSec, int iBitsPerSample, std::string szSongName)
{
  if (m_started)
  {
    kodi::Log(ADDON_LOG_WARNING, "Start: Already started without a stop - skipping this.");
    return true;
  }

  m_channels = iChannels;
  m_currentSongName = szSongName;
  m_titleChange = true;

  // Make one init frame in black
  std::shared_ptr<uint32_t> sp(new uint32_t[m_tex_width * m_tex_height], std::default_delete<uint32_t[]>());
  memset(sp.get(), 0, m_tex_width * m_tex_height * sizeof(uint32_t));
  m_activeQueue.push(sp);

  // Init GL parts
  if (!LoadShaderFiles(kodi::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/vert.glsl"),
                       kodi::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/frag.glsl")))
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

  // Start the goom process thread
  kodi::Log(ADDON_LOG_DEBUG, "Start: Setting up buffer worker thread.");
  m_workerThread = std::thread(&CVisualizationGoom::Process, this);

  m_started = true;
  return true;
}

//-- Stop ---------------------------------------------------------------------
// Called when the visualisation is closed by Kodi
//-----------------------------------------------------------------------------
void CVisualizationGoom::Stop()
{
  if (!m_started)
  {
    kodi::Log(ADDON_LOG_WARNING, "Stop: Not started - skipping this.");
    return;
  }

  m_started = false;

  kodi::Log(ADDON_LOG_DEBUG, "Stop: Stopping processed buffers thread...");
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_threadExit = true;
    m_wait.notify_one();
  }
  if (m_workerThread.joinable())
    m_workerThread.join();

  kodi::Log(ADDON_LOG_DEBUG, "Stop: Processed buffers thread stopped.");

  glDeleteTextures(1, &m_textureId);
  m_textureId = 0;

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
}

void CVisualizationGoom::OnCompiledAndLinked()
{
  m_uProjModelMatLoc = glGetUniformLocation(ProgramHandle(), "u_projModelMat");
  m_aPositionLoc = glGetAttribLocation(ProgramHandle(), "in_position");
  m_aCoordLoc = glGetAttribLocation(ProgramHandle(), "in_tex_coord");
}

bool CVisualizationGoom::OnEnabled()
{
  glUniformMatrix4fv(m_uProjModelMatLoc, 1, GL_FALSE, glm::value_ptr(m_projModelMatrix));
  return true;
}

//-- Audiodata ----------------------------------------------------------------
// Called by Kodi to pass new audio data to the vis
//-----------------------------------------------------------------------------
void CVisualizationGoom::AudioData(const float* pAudioData, int iAudioDataLength, float* pFreqData, int iFreqDataLength)
{
  if (!m_started)
  {
    kodi::Log(ADDON_LOG_WARNING, "AudioData: Not started - skipping this.");
    return;
  }

  std::unique_lock<std::mutex> lock(m_mutex);

  if (m_buffer.data_available() >= g_circular_buffer_size)
    return;

  m_buffer.write(pAudioData, iAudioDataLength);
  m_wait.notify_one();
}

bool CVisualizationGoom::UpdateTrack(const VisTrack &track)
{
  if (m_goom)
  {
    m_lastSongName = m_currentSongName;
    std::string artist = track.artist;
    if (artist.empty())
      artist = track.albumArtist;
    std::string title;
    if (!artist.empty())
       m_currentSongName = artist + " - " + track.title;
    else
      m_currentSongName = track.title;

    if (m_lastSongName != m_currentSongName)
      m_titleChange = true;

    m_showTitleAlways = kodi::GetSettingBoolean("show_title_always");
  }
  return true;
}

//-- Render -------------------------------------------------------------------
// Called once per frame. Do all rendering here.
//-----------------------------------------------------------------------------

bool CVisualizationGoom::IsDirty()
{
  return true;//!m_worker.RequestsQueueEmpty();
}

void CVisualizationGoom::Render()
{
  if (!m_started)
  {
    kodi::Log(ADDON_LOG_WARNING, "Render: Not started - skipping this.");
    return;
  }

  // Setup vertex attributes.
#ifdef HAS_GL
  glBindVertexArray(m_vaoObject);
#else
  glVertexAttribPointer(m_aPositionLoc, 2, GL_FLOAT, GL_FALSE, 0, m_quadData);
  glEnableVertexAttribArray(m_aPositionLoc);
  glVertexAttribPointer(m_aCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, m_quadData+m_numVertices * m_componentsPerVertex);
  glEnableVertexAttribArray(m_aCoordLoc);
#endif

  // Setup texture.
  glDisable(GL_BLEND);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textureId);
  if (!m_activeQueue.empty())
  {
    std::shared_ptr<uint32_t> pixels = m_activeQueue.front();
    m_activeQueue.pop();

#ifdef HAS_GL
    if (m_usePixelBufferObjects)
    {
      m_currentPboIndex = (m_currentPboIndex + 1) % g_numPbos;
      const int nextPboIndex = (m_currentPboIndex + 1) % g_numPbos;

      // Bind to current PBO and send pixels to texture object.
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[m_currentPboIndex]);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_tex_width, m_tex_height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

      // Bind to next PBO and update data directly on the mapped buffer.
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[nextPboIndex]);
      std::memcpy(m_pboGoomBuffer[nextPboIndex], pixels.get(), sizeof(uint32_t) * m_tex_width * m_tex_height);

      glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
    else
#endif
    {
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_tex_width, m_tex_height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
    }

    m_storedQueue.push(pixels);
  }

  EnableShader();
  glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
  DisableShader();

  glEnable(GL_BLEND);

#ifdef HAS_GL
  glBindVertexArray(0);
#else
  glDisableVertexAttribArray(m_aPositionLoc);
  glDisableVertexAttribArray(m_aCoordLoc);
#endif
}

static inline int16_t FloatToInt16(float f)
{
  if (f >= 1.0f)
    return INT16_MAX;
  else if (f < -1.0f)
    return -INT16_MAX;
  else
    return static_cast<int16_t>((f * static_cast<float>(INT16_MAX)));
}

bool CVisualizationGoom::FillBuffer(int16_t* data)
{
  if (m_buffer.data_available() < AUDIO_SAMPLE_LEN * m_channels)
    return false;

  float floatData[NUM_AUDIO_SAMPLES*AUDIO_SAMPLE_LEN];
  unsigned read = m_buffer.read(floatData, AUDIO_SAMPLE_LEN * m_channels);

  int ipos = 0;
  int fpos = 0;
  while (ipos < AUDIO_SAMPLE_LEN)
  {
    data[ipos] = FloatToInt16(floatData[fpos++]);
    data[AUDIO_SAMPLE_LEN + ipos] = m_channels == 1 ? data[ipos] : FloatToInt16(floatData[fpos++]);
    ipos++;
  }

  return true;
}

void CVisualizationGoom::Process()
{
  m_goom = goom_init(m_tex_width, m_tex_height);
  if (!m_goom)
  {
    kodi::Log(ADDON_LOG_FATAL, "CVisualizationGoom: Goom could not be initialized!");
    return;
  }

  int16_t audioData[NUM_AUDIO_SAMPLES][AUDIO_SAMPLE_LEN];
  const char* title = nullptr;

  while (!m_threadExit)
  {
    bool bExit;
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      if (!m_threadExit && FillBuffer(reinterpret_cast<int16_t*>(audioData)) != true)
        m_wait.wait(lock);

      if (m_titleChange || m_showTitleAlways)
      {
        title = m_currentSongName.c_str();
        m_titleChange = false;
      }
      else
        title = nullptr;

      bExit = m_threadExit;
    }

    if (bExit)
      break;

    if (m_activeQueue.size() > 10)
      continue;

    std::shared_ptr<uint32_t> pixels;
    if (!m_storedQueue.empty())
    {
      pixels = m_storedQueue.front();
      m_storedQueue.pop();
    }
    else
    {
      std::shared_ptr<uint32_t> sp(new uint32_t[m_tex_width * m_tex_height], std::default_delete<uint32_t[]>());
      pixels = sp;
    }

    goom_set_screenbuffer(m_goom, pixels.get());
    goom_update(m_goom, audioData, 0, 0.0f, title, "Kodi");
    m_activeQueue.push(pixels);
  }

  goom_close(m_goom);
}

void CVisualizationGoom::InitQuadData()
{
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

bool CVisualizationGoom::InitGLObjects()
{
  m_projModelMatrix = glm::ortho(0.0f, float(Width()), 0.0f, float(Height()));

  // Setup vertex attributes
#ifdef HAS_GL
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_vertexVBO);
  glGenVertexArrays(1, &m_vaoObject);
  glBindVertexArray(m_vaoObject);
  glGenBuffers(1, &m_vertexVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glEnableVertexAttribArray(m_aPositionLoc);
  glEnableVertexAttribArray(m_aCoordLoc);
  glVertexAttribPointer(m_aPositionLoc, m_componentsPerVertex, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glVertexAttribPointer(m_aCoordLoc, m_componentsPerTexel, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(m_numVertices * m_componentsPerVertex * sizeof(GLfloat)));
  glBufferData(GL_ARRAY_BUFFER, m_numElements*sizeof(GLfloat), m_quadData, GL_STATIC_DRAW);
  glBindVertexArray(0);
#endif

  // Create texture.
  glGenTextures(1, &m_textureId);
  if (!m_textureId)
  {
    kodi::Log(ADDON_LOG_ERROR, "InitGLObjects: Could not do glGenTextures.");
    return false;
  }
  glClear(GL_COLOR_BUFFER_BIT);

  glBindTexture(GL_TEXTURE_2D, m_textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#ifdef HAS_GL
  glGenerateMipmap(GL_TEXTURE_2D);
#endif
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

#ifdef HAS_GL
  if (!m_usePixelBufferObjects)
  {
    kodi::Log(ADDON_LOG_NOTICE, "InitGLObjects: Not using pixel buffer objects.");
  }
  else
  {
    kodi::Log(ADDON_LOG_NOTICE, "InitGLObjects: Using pixel buffer objects.");
    m_currentPboIndex = 0;

    glGenBuffers(g_numPbos, m_pboIds);
    for (int i = 0; i < g_numPbos; i++)
    {
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[i]);
      glBufferData(GL_PIXEL_UNPACK_BUFFER, m_goomBufferSize, 0, GL_STREAM_DRAW);
      glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[i]);
      glBufferData(GL_PIXEL_UNPACK_BUFFER, m_goomBufferSize, 0, GL_STREAM_DRAW);
      m_pboGoomBuffer[i] = static_cast<unsigned char*>(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY));
      if (!m_pboGoomBuffer[i])
      {
        kodi::Log(ADDON_LOG_ERROR, "InitGLObjects: Could not do glMapBuffer for pbo %d.", i);
        return false;
      }
    }
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
  }
#endif

  return true;
}

ADDONCREATOR(CVisualizationGoom) // Don't touch this!
