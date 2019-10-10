#version 430

uniform sampler2DRect tex0;
uniform vec4 backgroundColor;

in vec2 texCoord;
in vec4 vertexColor;

out vec4 outColor;

void main() {
    vec4 texColor = texture(tex0, texCoord);

    if (texColor.xyz == backgroundColor.xyz)
        outColor = vertexColor;
    else
        outColor = texColor;
}
