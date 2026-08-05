#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal; // Modern attribute slot for mesh surface normals

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main() {
    gl_Position = vec4(aPos, 1.0);
    FragPos = aPos; // Pass position vector straight to the fragment shader
    Normal = aNormal; // Pass structural normals
    TexCoord = aTexCoord;
}
