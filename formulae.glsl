/* Mathematical code snippets. Not for compilation. */

// Coordinatewise cubic bezier
position.x = -p0x*pow(t-1.0,3.0)+p3x*(t*t*t)+p1x*t*pow(t-1.0,2.0)*3.0-p2x*(t*t)*(t-1.0)*3.0;
position.y = -p0y*pow(t-1.0,3.0)+p3y*(t*t*t)+p1y*t*pow(t-1.0,2.0)*3.0-p2y*(t*t)*(t-1.0)*3.0;

// Computational normal for sqrt curve
vec3 rd = vec3(a/(2.0*sqrt(a*stX)), 1.0, 0.0); // x is a function
vec3 rdd = vec3((-(a*a))/(4.0*pow(a*stX,1.5)), 0.0, 0.0); // x is function derivative
normal = normalize(circDistribution * cross(rd, cross(rd, rdd)));

// Precomputed analytical normal for cubic bezier
normal = normalize(circDistribution * vec3(
    p0y*pow(t-1.0,2.0)*-3.0+p1y*pow(t-1.0,2.0)*3.0-p2y*(t*t)*3.0+p3y*(t*t)*3.0-p2y*t*(t-1.0)*6.0+p1y*t*(t*2.0-2.0)*3.0,
    p0x*pow(t-1.0,2.0)* 3.0-p1x*pow(t-1.0,2.0)*3.0+p2x*(t*t)*3.0-p3x*(t*t)*3.0+p2x*t*(t-1.0)*6.0-p1x*t*(t*2.0-2.0)*3.0,
    0.0
);

/** Generates Julia set texture based on "texture coordinates" of current fragment.
 * Julia set is generated for well-known complex function f(z) = z^2 + c,
 * where c is selected from a circle based on current frame number.
 * Cicrle center and radius were selected empirically using a plot of Mandelbrot set as a map.
 * Area boundaries (see z.x and z.y assignment) were selected empirically to produce almost
 * seamless texture.
 * Returns: point color.
 */
vec4 juliaTextureColor() {
    const int iter = 512;
    vec2 c = rotate(2048.0f + urandomab(stemIdxFrag, -512.0f, 512.0f),
        rand(stemIdxFrag) * 2.0f * M_PI, 0.08f, vec2(-1.4f, 0.25f));
    vec2 z;
    // Area boundaries.
    z.x = fragAlong * 2.25f - 1.125f;
    z.y = fragAround * 1.5f - 0.75f;

    int i = 0;
    for(; i < iter; i++) {
        float x = (z.x * z.x - z.y * z.y) + c.x;
        float y = (2.0f * z.y * z.x) + c.y;
        if((x * x + y * y) > 4.0f)
            break;
        z.x = x;
        z.y = y;
    }
    return clamp(vec4(0.4f, 0.0f, 0.7f, 1.0f) * (float(i)/iter) * 40.0f, 0.0f, 1.0f);
}
