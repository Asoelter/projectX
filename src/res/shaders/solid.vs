#version 330 core

layout(location = 0) in vec2 pos;

uniform vec2 translation;

void main()
{
    float xPos = pos.x + translation.x;
    float yPos = pos.y + translation.y;

    float transX = (1.0 / 50.0 * xPos) - 1;
    float transY = (1.0 / 50.0 * yPos) - 1;

    //gl_Position = vec4(xPos, yPos, 0, 1);
    gl_Position = vec4(transX, transY, 0, 1);
}
