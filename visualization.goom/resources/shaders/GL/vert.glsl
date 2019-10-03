#version 140

#extension GL_ARB_explicit_attrib_location : require


uniform mat4 u_projModelMat;

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_tex_coord;
smooth out vec2 vs_tex_coord;


void main()
{
  gl_Position = u_projModelMat * vec4(in_position.x, in_position.y, 0.0, 1.0); 

  vs_tex_coord = in_tex_coord;
}
