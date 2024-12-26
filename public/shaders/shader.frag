// fragment shader
in vec2 FracCoord;

uniform float zoom;
uniform int maxIter;
uniform vec2 juliaConstant;

// colors
uniform vec3 darkRed;
uniform vec3 amber;

float norm(vec2 c) {
    return c.x * c.x + c.y * c.y;
}

vec2 mult(vec2 v1, vec2 v2) {
    return vec2(
        v1.x * v2.x - v1.y * v2.y,
        v1.x * v2.y + v1.y * v2.x
    );
}

int computeIterations(vec2 z) {
    int iteration = 0;

    while (norm(z) < 4.0f && iteration < maxIter) {
        z = mult(z, z).xy + juliaConstant.xy;
        ++iteration;
    }

    return iteration;
}

void main() {
    int iter = computeIterations(FracCoord);

    float val = float(iter) / float(maxIter);

    gl_FragColor = vec4(val, val, val, 1.0f);
}
