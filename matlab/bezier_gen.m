% This script generates C code for cubic bezier curves and normals
syms t;
syms p0x p0y p1x p1y p2x p2y p3x p3y;
% Bezier curve formula:
bc3 = bernsteinMatrix(3,t) * [p0x, p0y; p1x, p1y; p2x, p2y; p3x, p3y];
% First derivative:
d1_bc3 = diff(bc3, t);
% Second derivetive
d2_bc3 = diff(d1_bc3, t);
% Normal:
n_bc3 = cross([d1_bc3 0], cross([d1_bc3 0], [d2_bc3 0]));
ccode(bc3)
ccode(n_bc3)
