#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_sampler;
uniform vec3 lightDir; // Global directional sun vector
uniform vec3 lightColor; // Diffuse spectrum color
uniform vec3 viewPos; // Camera coordinate location

void main() {
    // 1. Ambient lighting channel calculation
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    
    // 2. Diffuse lighting channel calculation via normalized dot products
    vec3 norm = normalize(Normal);
    vec3 lightDirNorm = normalize(-lightDir);
    float diff = max(dot(norm, lightDirNorm), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // 3. Specular highlighting channel calculation
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDirNorm, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 is shininess multiplier
    vec3 specular = specularStrength * spec * lightColor;
    
    // Combine all shading calculations into a final pixel value
    vec4 texColor = texture(texture_sampler, TexCoord);
    vec3 lightingResult = (ambient + diffuse + specular) * texColor.rgb;
    
    FragColor = vec4(lightingResult, 1.0);
}
