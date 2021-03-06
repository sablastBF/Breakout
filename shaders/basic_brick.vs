
#version 330 core
layout (location = 0) in vec4 vec; // the position variable has attribute position 0

out vec2 texCoord;

uniform mat4 projection, model;

void main()
{
    texCoord = vec.zw;
    gl_Position = projection*model*vec4(vec.xy, 0.1, 1.0); // see how we directly give a vec3 to vec4's constructor
}

