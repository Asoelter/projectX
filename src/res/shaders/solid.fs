#version 330 core

in uniforms
{
    vec2 position;
    vec2 tCoords;
} inUniforms;

out vec4 color;
uniform vec4 inColor =  vec4(0, 0, 1, 1);

uniform int textureCount = 0;

#if __VERSION__ == 450
layout (binding = 0) uniform sampler2D texture1;
layout (binding = 1) uniform sampler2D texture2;
layout (binding = 2) uniform sampler2D texture3;
#else
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
#endif 

void main(void)
{
    if(textureCount > 0)
    {
        color = texture(texture1, inUniforms.tCoords);

        if (color.a < 0.1) {
            if(textureCount > 1)
            {
                vec4 color2 = texture(texture2, inUniforms.tCoords);
                color += color2;
            }

            if(textureCount > 2)
            {
                vec4 color3 = texture(texture3, inUniforms.tCoords);
                color += color3;
            }

            if(color.a <= 0.1)
            {
                discard;
            }
        }
    }
    else
    {
        color = inColor;
    }
}
