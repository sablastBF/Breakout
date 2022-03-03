
#version 330 core
layout (location = 0) in vec2 vec; // the position variable has attribute position 0

uniform mat4 projection;

void main()
{
    gl_Position = projection*vec4(vec.xy, 0.1, 1.0); // see how we directly give a vec3 to vec4's constructor
}

