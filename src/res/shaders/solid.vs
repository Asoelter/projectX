#version 330 core

const mat4 identity = mat4(1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoords;

uniform vec2  translation;

uniform float xLimit = 200;
uniform float yLimit = 200;

uniform mat4 scale = identity;
uniform mat4 view = identity;
uniform mat4 projection = identity;

out uniforms
{
    vec2 position;
    vec2 tCoords;
} outUniforms;

void main()
{
    float xPos = pos.x + translation.x;
    float yPos = pos.y + translation.y;

    float transX = (((2.0 / (xLimit)) * xPos) - 1);
    float transY = (((2.0 / (yLimit)) * yPos) - 1);

    outUniforms.position = vec2(transX, transY);
    outUniforms.tCoords = texCoords;

    gl_Position = projection * view * scale * vec4(transX, transY, 0.0, 1);
}
