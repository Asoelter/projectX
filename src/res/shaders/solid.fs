#version 330 core

in uniforms
{
    vec2 position;
    vec2 tCoords;
} inUniforms;

out vec4 color;
uniform vec4 inColor =  vec4(0, 0, 1, 0);

uniform bool hasTexture = false;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main(void)
{
    if(hasTexture)
    {
        color = texture(texture1, inUniforms.tCoords);

        if(color.a <= 0.1)
        {
            discard;
        }
    }
    else
    {
        color = inColor;
    }
}
