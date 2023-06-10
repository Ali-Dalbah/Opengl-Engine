#version 330 core
out vec4 fragColor;
in vec3 color;
in vec2 textureCoord;
in vec3 normal;
uniform sampler2D diffuse0;
uniform int mouseOn;
void main() {
	vec3 Normal = normalize(normal);
    vec4 blue = vec4(1.f,1.f,1.f,1.f);
    if (mouseOn == 1) {
        blue = vec4(0.13f, 0.07f, 0.25f, 1.f);
    }
	fragColor = (texture(diffuse0, textureCoord)) * blue;
}
