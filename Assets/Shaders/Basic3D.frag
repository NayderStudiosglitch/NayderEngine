#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D texture_sampler; // Active hardware sampler mapping texture units

void main() {
    // Samples the active bound VRAM image bytes dynamically using UV inputs
    FragColor = texture(texture_sampler, TexCoord);
}
