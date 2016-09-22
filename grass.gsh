#ifdef VERSION_410_NOT_DEFINED
#version 410
#endif

// Stem circular precision
#define numSectors 24

layout(lines) in;
layout(triangle_strip, max_vertices = 256) out;

uniform highp mat4 viewProjectionMatrix;

in vec3 normal[];
in vec3 binormal[];
in float stemThickness[];
in float along[];
flat in float stemIdx[];

out vec3 fragPosition;
out vec3 fragNormal;
out float fragAlong;
out float fragAround;
flat out float stemIdxFrag;

void main() {
    float stemRadius = urandomab(stemIdx[0], 0.03f, 0.1f); // Maximal stem radius
    for(int i = 0; i < numSectors + 1; ++i) { // Segments loop
        float around = i / float(numSectors);
        float alpha = (around) * 2.0f * M_PI;
        for(int j = 0; j < 2; ++j) { // Input vertex loop
            // Generating geometry.
            vec3 r = cos(alpha) * normal[j] + sin(alpha) * binormal[j];
            vec3 vertexPosition = r * stemRadius * stemThickness[j] + gl_in[j].gl_Position.xyz;
            fragPosition = vertexPosition;
            fragNormal = r;
            fragAlong = along[j];
            fragAround = around;
            stemIdxFrag = stemIdx[j];
            gl_Position = viewProjectionMatrix * vec4 (vertexPosition, gl_in[j].gl_Position.w);
            EmitVertex();
        }
    }
    EndPrimitive();
}
