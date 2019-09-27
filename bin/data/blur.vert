#version 430 core

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
/*
in vec2 texcoord;

out vec2 texCoord;
*/

void main() {
    gl_Position = modelViewProjectionMatrix * position;

//    texCoord = texcoord;
}
