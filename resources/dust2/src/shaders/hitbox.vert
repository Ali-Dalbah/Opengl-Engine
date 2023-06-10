#version 330 core
layout (location = 0) in vec3 positions;
uniform mat4 camera;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
void main() {
	vec3 crntPos = vec3(model * translation * -rotation * scale * vec4(positions, 1.0f));
	gl_Position = camera * vec4(crntPos, 1.0);
}