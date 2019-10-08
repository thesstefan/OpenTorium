#version 430

layout (std430, binding = 1) buffer kernel {
    float data[];
} kernelY;

uniform sampler2DRect tex0;

in vec2 texCoord;
out vec4 outColor;

void main() {
    vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    int bound = kernelY.data.length() / 2;

    for (int kernelIndex = -bound; kernelIndex <= bound; kernelIndex++)
        color += kernelY.data[kernelIndex + bound] * 
            texture(tex0, texCoord + vec2(0.0, kernelIndex));

    outColor = color;
}
