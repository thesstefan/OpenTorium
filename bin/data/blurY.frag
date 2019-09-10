#version 430

layout (std430, binding = 1) buffer kernel {
    float data[];
} kernelY;

uniform sampler2DRect tex0;

in vec2 texCoord;
out vec4 outColor;

void main() {
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    uint bound = kernelY.data.length() / 2;

    for (uint kernelIndex = -bound; kernelIndex < bound; kernelIndex++)
        color += kernelY.data[kernelIndex] * 
            texture(tex0, texCoord + vec2(0.0, kernelIndex));

    outColor = color;
}
