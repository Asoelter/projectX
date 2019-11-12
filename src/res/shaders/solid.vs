#version 330 core

layout(location = 0) in vec2 pos;

uniform vec2  translation;
uniform float xLimit = 200;
uniform float yLimit = 200;

void main()
{
    float xPos = pos.x + translation.x;
    float yPos = pos.y + translation.y;

    float transX = (((2.0 / xLimit) * xPos) - 1);
    float transY = (((2.0 / yLimit) * yPos) - 1);

    gl_Position = vec4(transX, transY, 0, 1);
}
