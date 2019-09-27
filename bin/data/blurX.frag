#version 430

/*
layout (std430, binding = 0) buffer kernel{
    float data[];
} kernelX;

uniform sampler2DRect tex0;

in vec2 texCoord;
*/

out vec4 outColor;

void main() {
    vec4 color = vec4(1.0f, 0.0f, 0.0f, 0.0f);

    /*
    int bound = kernelX.data.length() / 2;

    for (int kernelIndex = -bound; kernelIndex <= bound; kernelIndex++)
        color += kernelX.data[kernelIndex + bound] * 
            texture(tex0, texCoord + vec2(kernelIndex, 0.0));
    */

    outColor = color;
}
