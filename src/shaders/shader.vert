// VERTEX SHADER
#version 330 core
layout(location = 0) in vec2 aPos;

out vec2 FracCoord;

uniform float aspect_ratio;
uniform float zoom;
uniform vec2 center;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y * aspect_ratio, 0.0f, 1.0f);

    // set appropriate range for fractal rendering
    float FracX = aPos.x * 2.0f - 1.0f;
    float FracY = aPos.y * 2.0f - 1.0f;
    if (zoom != 0) {
      FracX = FracX / zoom + center.x;
      FracY = FracY / zoom + center.y;
    } 
    FracCoord = vec2(FracX, FracY);
}
