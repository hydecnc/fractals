// FRAGMENT SHADER
#version 330 core
in vec2 FracCoord;

out vec4 FragColor;

uniform int max_iter;
uniform vec2 julia_constant;


float norm(vec2 c) {
    return c.x * c.x + c.y * c.y;
}

vec2 mult(vec2 v1, vec2 v2) {
    return vec2(
        v1.x * v2.x - v1.y * v2.y, // Real part
        v1.x * v2.y + v1.y * v2.x // Imaginary part
    );
}

vec2 add(vec2 v1, vec2 v2) {
    return vec2(v1.x + v2.x, v1.y + v2.y);
}

int compute_iterations(vec2 z) {
    int iteration = 0;

    while (norm(z) < 4.0f && iteration < max_iter) {
        z = add(mult(z, z), julia_constant);
        ++iteration;
    }

    return iteration;
}

void main()
{
    int iter = compute_iterations(FracCoord);

    float val = float(iter) / float(max_iter);
    FragColor = vec4(val, val, val, 1.0);
}
