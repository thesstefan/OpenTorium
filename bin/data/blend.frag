#version 430

uniform sampler2DRect tex0;

in vec2 texCoord;
in vec4 vertexColor;

out vec4 outColor;

float max_vec3(vec3 vec) {
    return max(max(vec.x, vec.y), vec.z);
}

void main() {
    vec4 texColor = texture(tex0, texCoord);

    if (max_vec3(vertexColor.xyz) > max_vec3(texColor.xyz))
        outColor = vertexColor;
    else
        outColor = texColor;
}
