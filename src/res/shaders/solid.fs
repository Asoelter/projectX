#version 330 core

out vec4 color;
uniform vec4 inColor;

void main(void)
{
    //color = vec4(1.0, 0.0, 0.0, 1.0);
    color = inColor;
}
