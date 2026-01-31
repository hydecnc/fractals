// FRAGMENT SHADER
#version 330 core

precision highp float;

in vec2 FracCoord;

out vec4 FragColor;

uniform int max_iter;

vec2 mult(vec2 v1, vec2 v2) {
    return vec2(
        v1.x * v2.x - v1.y * v2.y, // Real part
        v1.x * v2.y + v1.y * v2.x // Imaginary part
    );
}

float compute_iterations(vec2 c) {
    const float B = 256.0f;
    float n = 0.0f;
    vec2 z = vec2(0.0f);

    for (int i = 0; i < max_iter; i++) {
        z = mult(z, z) + c;
        if (dot(z, z) > B * B) break;
        n += 1.0f;
    }

    float sn = n - log2(log2(dot(z,z))) + 4.0;
    return sn;
}

void main()
{
    float iter = compute_iterations(FracCoord);

    vec3 col = (iter < 0.5) ? vec3(0.0,0.0,0.0) : 
        0.5 + 0.5 * cos( 3.0 + iter * 0.15 + vec3(0.2, 0.8, 0.4));

    FragColor = vec4(col, 1.0);
}
