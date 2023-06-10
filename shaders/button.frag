#version 330 core
out vec4 fragColor;
uniform vec3 buttonColor;
uniform int mouseOn;
void main() {
    fragColor = vec4(buttonColor + mouseOn * vec3(0.0, 1.0, 0.0), 1.0);
}