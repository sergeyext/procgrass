//  Cellular  noise  (" Worley  noise") in 2D in GLSL , simplified  version.
//  Copyright (c) Stefan  Gustavson  2011 -04 -19.  All  rights  reserved.
// This  code is  released  under  the  conditions  of the  MIT  license.
// See  LICENSE  file  for  details.

vec4 permute(vec4 x) {
    return  mod ((34.0 * x + 1.0) * x, 289.0);
}
vec2 cellular2x2(vec2 P) {
    const float K = 1.0/7.0;
    const float K2 = 0.5/7.0;
    const float jitter = 0.8; //  jitter  1.0  makes  F1  wrong  more  often
    vec2 Pi = mod(floor(P), 289.0);
    vec2 Pf = fract(P);
    vec4 Pfx = Pf.x + vec4(-0.5, -1.5, -0.5, -1.5);
    vec4 Pfy = Pf.y + vec4(-0.5, -0.5, -1.5, -1.5);
    vec4 p = permute(Pi.x + vec4 (0.0, 1.0, 0.0, 1.0));
    p = permute(p + Pi.y + vec4 (0.0, 0.0, 1.0, 1.0));
    vec4 ox = mod(p, 7.0)*K+K2;
    vec4 oy = mod(floor(p*K) ,7.0)*K+K2;
    vec4 dx = Pfx + jitter*ox;
    vec4 dy = Pfy + jitter*oy;
    vec4 d = dx * dx + dy * dy; //  distances  squared
    //  Cheat  and  pick  only F1 for  the  return  value
    d.xy = min(d.xy, d.zw);
    d.x = min(d.x, d.y);
    return d.xx; // F1  duplicated , F2 not  computed
}
