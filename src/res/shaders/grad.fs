#version 330 core

out vec4 color;
in vec4 gradPos;

void main(void)
{
    float green = ( gradPos.x + 1 )  / 2.0;
    float blue = ( gradPos.y + 1 )  / 2.0;
    color = vec4(0.0, green, blue, 1.0);
}
