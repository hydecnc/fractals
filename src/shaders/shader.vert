// VERTEX SHADER
#version 330 core
layout(location = 0) in vec2 aPos;

out vec2 FracCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float zoom;
uniform vec2 center;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0f, 1.0f);

    vec2 ndc = gl_Position.xy / gl_Position.w;
    FracCoord  = (ndc * vec2(1.75, 1.25) / zoom) + center; 
}
