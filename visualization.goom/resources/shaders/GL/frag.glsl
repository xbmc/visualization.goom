#version 140

#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require
#extension GL_EXT_gpu_shader4 : enable


uniform sampler2D tex;
smooth in vec2 vs_tex_coord;
layout (location = 0) out vec4 color;


void main()
{
  color = texture(tex, vs_tex_coord);
}
