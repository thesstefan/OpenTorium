#version 430

uniform sampler2DRect tex0;

uniform float backgroundThreshold;
uniform vec4 backgroundColor;

in vec2 texCoord;
in vec4 vertexColor;

out vec4 outColor;

void main() {
    vec4 texColor = texture(tex0, texCoord);
    vec3 difference = vertexColor.xyz - backgroundColor.xyz;

    if (max(max(abs(difference.x), abs(difference.y)), abs(difference.z)) > 
            backgroundThreshold)
        outColor = vertexColor;
    else
        outColor = texColor;
}
