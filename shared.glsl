#version 410

#define M_PI 3.1415926535897932384626433832795f

const int totalFrames = 65536;
uniform int frameNumber;
uniform int numPrimitives;
float sfn = float(frameNumber) / totalFrames; // Specific frame number.

// Uniform distributed random values from [0, 1] range.
uniform sampler1D urandom01;

vec2 rotate(const in float freq, const in float phase,
    const in float radius, const in vec2 center) {
    float phi = fma(freq, sfn, phase); // Circle argument.
    return vec2(sin(phi), cos(phi)) * radius + center;
}

float rand(const in float seed) {
    return texture(urandom01, seed).r;
}

float urandomab(const in float x, const in float a, const in float b) {
    return fma(texture(urandom01, x).r, b-a, a);
}
