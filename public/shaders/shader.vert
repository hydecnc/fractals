// vertex shader
out vec2 FracCoord;

uniform float zoom;
uniform vec2 center;

void main() {
    // vec4 modelViewPosition = modelViewMatrix * vec4(position, 1.0);
    // gl_Position = projectionMatrix * modelViewPosition;

    // Make the plane fullscreen
    gl_Position = vec4(position, 1.0f);

    // set appropriate range for fractal rendering
    float fracX = position.x * 5.0;
    float fracY = position.y * 2.0;

    if (zoom != 0.0) {
        fracX = fracX / zoom + center.x;
        fracY = fracY / zoom + center.y;
    }
    FracCoord = vec2(fracX, fracY);
}
