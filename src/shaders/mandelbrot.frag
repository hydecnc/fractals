// FRAGMENT SHADER
#version 330 core
in vec2 FracCoord;

out vec4 FragColor;

uniform int max_iter;

vec2 mult(vec2 v1, vec2 v2) {
    return vec2(
        v1.x * v2.x - v1.y * v2.y, // Real part
        v1.x * v2.y + v1.y * v2.x // Imaginary part
    );
}

int compute_iterations(vec2 c) {
    vec2 z = vec2(0.0f, 0.0f);
    int iteration = 0;

    while (dot(z, z) < 4.0f && iteration < max_iter) {
        z = mult(z, z) + c;
        ++iteration;
    }

    return iteration;
}

void main()
{
    int iter = compute_iterations(FracCoord);

    float val = float(iter) / float(max_iter);

    FragColor = vec4(vec3(val), 1.0);
}
