#version 330 core
layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_colors;
layout (location = 3) in vec2 in_textureCoord;
out vec3 color;
out vec2 textureCoord;
out vec3 normal;
out vec3 currentPos;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
	currentPos = vec3(model * translation * -rotation * vec4(positions, 1.0f));
	gl_Position = vec4(currentPos, 1.0);
	color = in_colors;
	textureCoord = mat2(0.0, -1.0, 1.0, 0.0) * in_textureCoord;
	normal = in_normal;
}