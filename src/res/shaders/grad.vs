#version 330 core

layout(location = 0) in vec2 pos;

out vec4 gradPos;

void main()
{
    gradPos = vec4(pos.x, pos.y, 0, 1);
    gl_Position = gradPos;
}