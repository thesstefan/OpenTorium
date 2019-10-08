#version 430

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec2 texCoord;
out vec4 vertexColor;

void main() {
    gl_Position = modelViewProjectionMatrix * position;

    texCoord = texcoord;
    vertexColor = color;
}
