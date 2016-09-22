#ifdef VERSION_410_NOT_DEFINED
#version 410
#endif

layout(location=0) in vec4 position;

void main(void) {
    gl_Position = position;
}
