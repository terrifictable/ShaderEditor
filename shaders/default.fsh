#version 130

uniform float u_time;

void main() {
    vec4 color = vec4(1.0, 1.0, 1.0, sin(u_time));

    gl_FragColor = vec4(color);
}
