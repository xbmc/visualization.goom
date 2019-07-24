// Compile with
//
//  g++ -o opengl_test opengl_test.cpp -I/usr/local/include -I/home/greg/Prj/Python/visualization.goom/lib -I/home/greg/Prj/Python/visualization.goom/build/build/depends/include -L/usr/local/lib  -lX11 -lm -lGL -lGLEW -lglut

#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

#include <stdio.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <unistd.h>


using namespace std;

#define GOOM_TEXTURE_WIDTH  1280
#define GOOM_TEXTURE_HEIGHT 720
//#define GOOM_TEXTURE_WIDTH  512
//#define GOOM_TEXTURE_HEIGHT 256


class CVisualizationTest: kodi::gui::gl::CShaderProgram {
public:
  CVisualizationTest();
  virtual ~CVisualizationTest();
  
  bool Start();
  void Stop();
  bool Render();
  bool OnEnabled() override { return true; }
private:
//  const static int g_tex_width = 374;
//  const static int g_tex_height = 500;
  const static int g_startBuffNum = 192;
  const static int g_finishBuffNum = 200;
  const static int g_sleepTimeInMicroseconds = 1000*1000;
  const static int g_tex_width = GOOM_TEXTURE_WIDTH;
  const static int g_tex_height = GOOM_TEXTURE_HEIGHT;

  const static GLchar* vert;
  const static GLchar* frag;

  unsigned long* m_goom_tags;
  unsigned char** m_goom_buffers;
  inline size_t NumGoomBufferElements() { return 4 * g_tex_width * g_tex_height; }
  inline size_t GoomBufferSize() { return NumGoomBufferElements() * sizeof(unsigned char); }
  int max_num_saved_buffers;
  int num_saved_buffers;
  int buff_num;
  bool UpdateGoomBuffer(unsigned char* ptr);
  bool ReadSavedBuffers();

  float m_window_width;
  float m_window_height;
  float m_window_xpos;
  float m_window_ypos;
  GLuint m_texid;
  GLuint m_pboIds[2]; // IDs of PBO

  GLint m_componentsPerVertex;
  GLint m_componentsPerTexel;
  int numVertices;
  GLfloat* quad_data;
  int numElements;

  GLuint m_prog = 0;
  GLuint m_vaoObject = 0;
  GLuint m_vertexVBO = 0;
  GLint m_uProjModelMatLoc = -1;
  glm::mat4 m_projModelMatrix;
private:
  void gl_init();
  GLuint CreateProgram( const string& aVertexShader, const string& aFragmentShader );
  GLuint CreateShader( const GLenum aType, const string& aSource );
  void CheckStatus( const GLenum id );

  static CVisualizationTest* currentInstance;

  static void RenderCallback()
  {
    currentInstance->Render();
  }

public:
  void SetupRenderCallback()
  {
    printf("Start render callback.\n");
    currentInstance = this;
    ::glutDisplayFunc(CVisualizationTest::RenderCallback);
  }
};


CVisualizationTest* CVisualizationTest::currentInstance = 0;

int main(int argc, char *argv[])
{
    glutInit( &argc, argv );
    glutInitWindowSize(1280, 720);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow( "2D Texture Test" );

    CVisualizationTest visTest;
    if (!visTest.Start()) {
        printf("ERROR: Start returned false.\n");
        exit(EXIT_FAILURE);
    }

    visTest.SetupRenderCallback();

    glutMainLoop();

    visTest.Stop();

    printf("Finished.\n");
    exit(EXIT_SUCCESS);
}


CVisualizationTest::CVisualizationTest()
: m_texid(0)
{
  printf("Start CVisualizationTest constructor.\n");
  m_window_width = 1280.0;
  m_window_height = 720.0;
  m_window_xpos = 0.0;
  m_window_ypos = 0.0;

  max_num_saved_buffers = 10000;
  m_goom_tags = new unsigned long [max_num_saved_buffers];
  m_goom_buffers = new unsigned char* [max_num_saved_buffers];
  for (int i = 0; i < max_num_saved_buffers; i++) {
    m_goom_buffers[i] = (unsigned char*)malloc(GoomBufferSize());
    if (!m_goom_buffers[i]) {
      printf("Could not allocate buffer %d\n", i);
      exit(1);
    }
  }
  buff_num = 0;
  num_saved_buffers = 0;

  GLfloat x0 = m_window_xpos;
  GLfloat y0 = m_window_ypos;
  GLfloat x1 = m_window_xpos + m_window_width;
  GLfloat y1 = m_window_ypos + m_window_height;
  const GLfloat temp_quad_data[] =
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
    /**
      0.0, 0.0,
      0.0, 1.0,
      1.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
    **/  
  };
  numElements = sizeof(temp_quad_data)/sizeof(GLfloat);
  quad_data = new GLfloat[numElements];
  for (int i = 0; i < numElements; i++)
  {
    quad_data[i] = temp_quad_data[i];
  };
  m_componentsPerVertex = 2; 
  m_componentsPerTexel = 2; 
  numVertices = 2 * 3; // 2 triangles
}

CVisualizationTest::~CVisualizationTest()
{
  delete[] quad_data;
  for (int i = 0; i < max_num_saved_buffers; i++) {
    free(m_goom_buffers[i]);
  }
  delete[] m_goom_buffers;
  delete[] m_goom_tags;
}


void CVisualizationTest::gl_init()
{
    printf("Start CVisualizationTest gl_init.\n");

    GLenum glewError = glewInit();
    if( GLEW_OK != glewError )
        throw runtime_error( (char*)glewGetErrorString(glewError) );

    cout << "GL_VERSION   : " << glGetString(GL_VERSION) << endl;
    cout << "GL_VENDOR    : " << glGetString(GL_VENDOR) << endl;
    cout << "GL_RENDERER  : " << glGetString(GL_RENDERER) << endl;    
    cout << "GLEW_VERSION : " << glewGetString(GLEW_VERSION) << endl;
    cout << "GLSL VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    if( !GLEW_VERSION_2_1 )
        throw runtime_error( "OpenGL 2.1 or better required for GLSL support." ); 

    // load shaders
    m_prog = CreateProgram( vert, frag );

    printf("Finish CVisualizationTest gl_init.\n");
}

void CVisualizationTest::CheckStatus( const GLenum id )
{
    GLint status = GL_FALSE, loglen = 10;
    if( glIsShader(id) )    glGetShaderiv( id, GL_COMPILE_STATUS, &status ); 
    if( glIsProgram(id) )   glGetProgramiv( id, GL_LINK_STATUS, &status );
    if( GL_TRUE == status ) return;
    if( glIsShader(id) )    glGetShaderiv( id, GL_INFO_LOG_LENGTH , &loglen);
    if( glIsProgram(id) )   glGetProgramiv( id, GL_INFO_LOG_LENGTH , &loglen);
    vector< char > log( loglen, 'E' );
    if( glIsShader(id) )    glGetShaderInfoLog( id, loglen, NULL, &log[0] );
    if( glIsProgram(id) )   glGetProgramInfoLog( id, loglen, NULL, &log[0] );
    throw logic_error( string( log.begin(), log.end() ) ); 
}

GLuint CVisualizationTest::CreateShader( const GLenum aType, const string& aSource )
{
    GLuint shader = glCreateShader( aType );
    const GLchar* shaderString = aSource.c_str();
    glShaderSource( shader, 1, &shaderString, NULL );
    glCompileShader( shader );
    CheckStatus( shader );
    return shader;
}

GLuint CVisualizationTest::CreateProgram( const string& aVertexShader, const string& aFragmentShader )
{
    GLuint vert = CreateShader( GL_VERTEX_SHADER, aVertexShader );
    GLuint frag = CreateShader( GL_FRAGMENT_SHADER, aFragmentShader );
    GLuint program = glCreateProgram();
    glAttachShader( program, vert );
    glAttachShader( program, frag );
    glLinkProgram( program );
    glDeleteShader( vert );
    glDeleteShader( frag );
    CheckStatus( program );
    return program;
}

const GLchar* CVisualizationTest::vert =
"#version 140\n"
"#extension GL_ARB_explicit_attrib_location : require\n"
"uniform mat4 u_projModelMat;"
"layout (location = 0) in vec2 in_position;"
"layout (location = 1) in vec2 in_tex_coord;"
"smooth out vec2 vs_tex_coord;"
"void main()"
"{"
"   gl_Position = u_projModelMat * vec4( in_position, 0.0, 1.0 );"
"   vs_tex_coord = in_tex_coord;"
"}"
;

// fragment shader
const GLchar* CVisualizationTest::frag = 
"#version 140\n"
"#extension GL_ARB_explicit_attrib_location : require\n"
"#extension GL_ARB_explicit_uniform_location : require\n"
"#extension GL_EXT_gpu_shader4 : enable\n"
"uniform sampler2D tex;"
"smooth in vec2 vs_tex_coord;"
"layout (location = 0) out vec4 color;"
"void main()"
"{"
"   color = texture(tex, vs_tex_coord);"
"}"
;


void PrintByteBGRABuffer(size_t num, const unsigned char BGRA_Buffer[]) {
//    kodi::Log(ADDON_LOG_DEBUG, "Unsigned Byte Buffer (size %lu):", num);
    int j = 0;
    for (size_t i = 0; i < num; i++) {
//        kodi::Log(ADDON_LOG_DEBUG, "%f %f %f %f", 
//          float(BGRA_Buffer[j])/255.0, float(BGRA_Buffer[j+1])/255.0, 
//          float(BGRA_Buffer[j+2])/255.0, float(BGRA_Buffer[j+3])/255.0);
        j += 4;
    }
}

bool CVisualizationTest::Start() {
  gl_init();

  m_projModelMatrix = glm::ortho(0.0f, float(m_window_width), 0.0f, float(m_window_height));
  m_uProjModelMatLoc = glGetUniformLocation(m_prog, "u_projModelMat");


  // Create VAO and VBO.
  glGenVertexArrays(1, &m_vaoObject);
  glBindVertexArray(m_vaoObject);
  glGenBuffers(1, &m_vertexVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);  
  glVertexAttribPointer(0, m_componentsPerVertex, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glVertexAttribPointer(1, m_componentsPerTexel, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(numVertices * m_componentsPerVertex * sizeof(GLfloat)));
  glBufferData(GL_ARRAY_BUFFER, numElements*sizeof(GLfloat), quad_data, GL_STATIC_DRAW);
  glBindVertexArray(0);

  // Create texture.
  glGenTextures(1, &m_texid);
  if (!m_texid) {
      printf("Could not do glGenTextures\n");
      exit(1);
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
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_tex_width, g_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenBuffers(2, m_pboIds);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[0]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, GoomBufferSize(), 0, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[1]);
  glBufferData(GL_PIXEL_UNPACK_BUFFER, GoomBufferSize(), 0, GL_STREAM_DRAW);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);


  if (!ReadSavedBuffers()) {
    return false;
  }

  return true;
}


void CVisualizationTest::Stop()
{
  printf("Calling Stop.\n");

  if (m_texid)
  {
    glDeleteTextures(1, &m_texid);
    m_texid = 0;
  }
}

bool CVisualizationTest::Render() {
  printf("Start Render.\n");

  static int index = 0;
  int nextIndex = 0;   // pbo index used for next frame

  index = (index + 1) % 2;
  nextIndex = (index + 1) % 2;

  glUseProgram(m_prog);

  printf("Buffer %d -- tag: %lu\n", g_startBuffNum + buff_num, m_goom_tags[buff_num]);
  if (buff_num >= num_saved_buffers) {
    printf("Finished, buff_num = %d >= num_saved_buffers = %d\n", buff_num, num_saved_buffers);
    return true;
  }

  // Setup vertex attributes
  glBindVertexArray(m_vaoObject);

  // Setup texture
  glBindTexture(GL_TEXTURE_2D, m_texid);
//  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_tex_width, g_tex_height, GL_RGBA, GL_UNSIGNED_BYTE, m_goom_buffer);
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[index]);

  // copy pixels from PBO to texture object
  // Use offset instead of ponter.
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, g_tex_width, g_tex_height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

  // bind PBO to update pixel values
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pboIds[nextIndex]);

  // map the buffer object into client's memory
  // Note that glMapBuffer() causes sync issue.
  // If GPU is working with this buffer, glMapBuffer() will wait(stall)
  // for GPU to finish its job. To avoid waiting (stall), you can call
  // first glBufferData() with NULL pointer before glMapBuffer().
  // If you do that, the previous data in PBO will be discarded and
  // glMapBuffer() returns a new allocated pointer immediately
  // even if GPU is still working with the previous data.
  glBufferData(GL_PIXEL_UNPACK_BUFFER, GoomBufferSize(), 0, GL_STREAM_DRAW);
  unsigned char* goom_buffer = (unsigned char*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
  if (!goom_buffer) {
    printf("Could not do glMapBuffer.\n");
    exit(1);
  }
  if (!UpdateGoomBuffer(goom_buffer)) {
    printf("Could not update goom buffer.\n");
    exit(1);
  }
////    PrintByteBGRABuffer(numTexels, goom_buffer);
  // update data directly on the mapped buffer
  glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);  // release pointer to mapping buffer
  glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

  glBindTexture(GL_TEXTURE_2D, m_texid);
  glEnable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glActiveTexture(GL_TEXTURE0);

  glUniformMatrix4fv(m_uProjModelMatLoc, 1, GL_FALSE, glm::value_ptr(m_projModelMatrix));
  glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

  glEnable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);

  glutSwapBuffers();

  glutPostRedisplay();

  if (g_sleepTimeInMicroseconds > 0) {
    usleep(g_sleepTimeInMicroseconds);
  }

  return true;
}

bool CVisualizationTest::UpdateGoomBuffer(unsigned char* ptr) {
  memcpy(ptr, m_goom_buffers[buff_num], GoomBufferSize());
  buff_num++;
  return true;
}

bool CVisualizationTest::ReadSavedBuffers() {
  num_saved_buffers = 0;
  for (int i = g_startBuffNum; i < g_finishBuffNum; i++) {
    char filename[200];
    sprintf(filename, "/tmp/goom_buffer_%05d", i);
    FILE* file = fopen(filename, "rb");
    if (file == 0) {
      printf("Could not open file \"%s\".\n", filename);
      break;
    }
    int n = fread(&(m_goom_tags[num_saved_buffers]), sizeof(unsigned long), 1, file);
    if (n == 0) {
      printf("Could not read tag for file \"%s\".\n", filename);
      return false;
    }
    n = fread(m_goom_buffers[num_saved_buffers], sizeof(unsigned char), NumGoomBufferElements(), file);
    if (n == 0) {
      printf("Could not read buffer for file \"%s\".\n", filename);
      return false;
    }
    fclose(file);
    num_saved_buffers++;
  }

  return true;
}

/**
    const char* filename = "/tmp/last_test_buffer";
    FILE* file = fopen(filename, "wb");
    fwrite(m_goom_buffer, sizeof(unsigned char), NumGoomBufferElements(), file);
    fclose(file);
    printf("Wrote file \"%s\".\n", filename);
**/