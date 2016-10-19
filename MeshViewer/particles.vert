#version 330 core


void main() {

    //GeomShader
    gl_Position = vec4(position, 1.0f);
    gl_PointSize = 1;
}