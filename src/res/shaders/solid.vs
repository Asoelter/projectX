#version 430 core

layout(location = 0) in vec2 pos;

uniform vec2 translation;

void main()
{
    float xPos = pos.x + translation.x;
    float yPos = pos.y + translation.y;
    gl_Position = vec4(xPos, yPos, 0, 1);
}
