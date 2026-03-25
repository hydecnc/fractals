// FRAGMENT SHADER
#version 460 core

precision mediump float;

in vec2 FracCoord;
out vec4 FragColor;

uniform int max_iter;
uniform vec2 center;

layout(std430, binding = 0) readonly buffer ReferenceOrbit {
  vec2 orbit[];
};

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

float compute_iterations_ref(vec2 dc) {
    const float B = 256.0f;
    vec2 dz = vec2(0.0f);
    int iter;
    int reference_iter = 0;
    int max_reference_iter = orbit.length();
    for (iter = 0; iter < max_iter; iter++) {
        dz = 2.0f * mult(orbit[reference_iter], dz) + mult(dz, dz) + dc;
        reference_iter++;

        vec2 z = orbit[reference_iter] + dz;
        if (dot(z, z) > B * B) break;
        if (dot(z, z) < dot(dz, dz) || reference_iter == max_reference_iter) {
            dz = z;
            reference_iter = 0;
        }
    }
    // if (iter == max_reference_iter)
    //     return 0.0f;
    float sn = float(iter) - log2(log2(dot(orbit[iter] + dz, orbit[iter] + dz))) + 4.0;
    return sn;
}

void main()
{
    float iter = compute_iterations_ref(FracCoord);
    // float iter = compute_iterations(FracCoord + center);

    vec3 col = (iter < 0.5) ? vec3(0.0,0.0,0.0) : 
        0.5 + 0.5 * cos( 3.0 + iter * 0.15 + vec3(0.2, 0.8, 0.4));

    FragColor = vec4(col, 1.0);
}
