#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main() {
    // Outputs the interpolated vertex colors perfectly
    FragColor = vec4(ourColor, 1.0);
}
