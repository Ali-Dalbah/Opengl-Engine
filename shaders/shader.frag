#version 330 core
out vec4 fragColor;
in vec3 color;
in vec2 textureCoord;
in vec3 normal;
in vec3 currentPos;
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
float depth(float d) {
	return (20.f/(100.1f - (d*2-1)*(99.9)));
}
void main() {
	vec3 vector = lightPos - currentPos;
	float ambient = 0.20f;
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(vector);
	float dist = length(vector);
	float intensity = 1.f/(3.f*dist*dist + 0.5*dist + 1);
	float diffuse = max(dot(Normal, lightDirection), 0.0f);
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;
	fragColor = (texture(diffuse0, textureCoord) * (diffuse * intensity + ambient) + texture(specular0, textureCoord).r * specular * intensity) * vec4(1.f,1.f,1.f,1.f);
}
