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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>
extern "C" {
#include "goom.h"
}
#include "goom_config.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

using namespace std;

class CVisualizationGoom
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceVisualization
{
public:
  CVisualizationGoom();
  virtual ~CVisualizationGoom();

  virtual bool Start(int channels, int samplesPerSec, int bitsPerSample, std::string songName) override;
  virtual void Stop() override;
  virtual void Render() override;
  virtual void AudioData(const float* audioData, int audioDataLength, float *freqData, int freqDataLength) override;

private:
  const static int g_tex_width = GOOM_TEXTURE_WIDTH;
  const static int g_tex_height = GOOM_TEXTURE_HEIGHT;

  PluginInfo* m_goom;
  unsigned char* m_goom_buffer;
  short m_audio_data[2][512];
  int m_window_width;
  int m_window_height;
  int m_window_xpos;
  int m_window_ypos;
  GLuint m_texid;
};

CVisualizationGoom::CVisualizationGoom()
  : m_texid(0)
{
  m_goom = goom_init(g_tex_width, g_tex_height);
  if (!m_goom)
  {
    kodi::Log(ADDON_LOG_FATAL, "Goom could not be inited!");
    return;
  }

  m_goom_buffer = (unsigned char*)malloc(g_tex_width * g_tex_height * 4);
  goom_set_screenbuffer( m_goom, m_goom_buffer );
  memset(m_audio_data, 0, sizeof(m_audio_data) );
  m_window_width = Width();
  m_window_height = Height();
  m_window_xpos = X();
  m_window_ypos = Y();
}

//-- Destroy -------------------------------------------------------------------
// Do everything before unload of this add-on
// !!! Add-on master function !!!
//-----------------------------------------------------------------------------
CVisualizationGoom::~CVisualizationGoom()
{
  if ( m_goom )
  {
    goom_close( m_goom );
    m_goom = nullptr;
  }
  if ( m_goom_buffer )
  {
    free( m_goom_buffer );
    m_goom_buffer = nullptr;
  }
}

//-- Start --------------------------------------------------------------------
// Called when a new soundtrack is played
//-----------------------------------------------------------------------------
bool CVisualizationGoom::Start(int iChannels, int iSamplesPerSec, int iBitsPerSample, std::string szSongName)
{
  if ( m_goom )
  {
    goom_update( m_goom, m_audio_data, 0, 0, (char*)szSongName.c_str(), (char*)"Kodi" );
  }
  return true;
}

//-- Stop ---------------------------------------------------------------------
// Called when the visualisation is closed by Kodi
//-----------------------------------------------------------------------------
void CVisualizationGoom::Stop()
{
  if (m_texid)
  {
    glDeleteTextures( 1, &m_texid );
    m_texid = 0;
  }
}

//-- Audiodata ----------------------------------------------------------------
// Called by Kodi to pass new audio data to the vis
//-----------------------------------------------------------------------------
void CVisualizationGoom::AudioData( const float* pAudioData, int iAudioDataLength, float *pFreqData, int iFreqDataLength)
{
  int copysize = iAudioDataLength < (int)sizeof( m_audio_data ) >> 1 ? iAudioDataLength : (int)sizeof( m_audio_data ) >> 1;
  int ipos, i;
  for(ipos = 0, i = 0; i < copysize; i += 2, ++ipos)
  {
    m_audio_data[0][ipos] = (int)(pAudioData[i  ] * (INT16_MAX+.5f));
    m_audio_data[1][ipos] = (int)(pAudioData[i+1] * (INT16_MAX+.5f));
  }
}


//-- Render -------------------------------------------------------------------
// Called once per frame. Do all rendering here.
//-----------------------------------------------------------------------------
void CVisualizationGoom::Render()
{
  if ( m_goom )
  {
    goom_set_screenbuffer( m_goom, m_goom_buffer );
    if (!m_texid)
    {
      // initialize the texture we'll be using
      glGenTextures( 1, &m_texid );
      if (!m_texid)
        return;
      goom_update( m_goom, m_audio_data, 0, 0, nullptr, (char*)"Kodi" );
      glEnable(GL_TEXTURE_2D);
      glBindTexture( GL_TEXTURE_2D, m_texid );
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexImage2D( GL_TEXTURE_2D, 0, 4, g_tex_width, g_tex_height, 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, m_goom_buffer );
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
    else
    {
      // update goom frame and copy to our texture
      goom_update( m_goom, m_audio_data, 0, 0, nullptr, (char*)"Kodi" );
      glEnable(GL_TEXTURE_2D);
      glBindTexture( GL_TEXTURE_2D, m_texid );
      glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, g_tex_width, g_tex_height,
                       GL_RGBA, GL_UNSIGNED_BYTE, m_goom_buffer );
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    glDisable(GL_BLEND);
    glBegin( GL_QUADS );
    {
      glColor3f( 1.0, 1.0, 1.0 );
      glTexCoord2f( 0.0, 0.0 );
      glVertex2f( m_window_xpos, m_window_ypos );

      glTexCoord2f( 0.0, 1.0 );
      glVertex2f( m_window_xpos, m_window_ypos + m_window_height );

      glTexCoord2f( 1.0, 1.0 );
      glVertex2f( m_window_xpos + m_window_width, m_window_ypos + m_window_height );

      glTexCoord2f( 1.0, 0.0 );
      glVertex2f( m_window_xpos + m_window_width, m_window_ypos );
    }
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
  }
}

ADDONCREATOR(CVisualizationGoom) // Don't touch this!
