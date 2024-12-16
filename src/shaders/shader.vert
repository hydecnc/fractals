// VERTEX SHADER
#version 330 core
layout(location = 0) in vec3 aPos;

out vec2 FracCoord;

uniform float zoom;
uniform vec2 center;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    // set appropriate range for fractal rendering
    float FracX = aPos.x * 2.5 - 0.5;
    float FracY = aPos.y * 2;
    if (zoom != 0) {
      FracX = FracX / zoom + center.x;
      FracY = FracY / zoom + center.y;
    } 
    FracCoord = vec2(FracX, FracY);
}
