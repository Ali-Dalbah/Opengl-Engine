#include "../include/Mesh.h"
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;
	vao.bind();
	VBO vbo(vertices);
	EBO ebo(indices);
	vao.linkVBOAttribute(vbo, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*) 0);
	vao.linkVBOAttribute(vbo, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*) (3 * sizeof(float)));
	vao.linkVBOAttribute(vbo, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*) (6 * sizeof(float)));
	vao.linkVBOAttribute(vbo, 3, 2, GL_FLOAT, 11 * sizeof(float), (void*) (9 * sizeof(float)));
	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

void Mesh::render(Shader& shader, Camera& camera) {
    shader.activate();
    vao.bind();
    unsigned int diffuseTextures = 0;
    unsigned int specularTextures = 0;
    for (int i=0;i<textures.size();i++) {
        std::string textureType = textures[i].type;
        std::string textureNumber;
        if (textureType == "diffuse") textureNumber = std::to_string(diffuseTextures++);
        else if (textureType == "specular") textureNumber = std::to_string(specularTextures++);
        textures[i].linkToShader(shader, (textureType + textureNumber).c_str(), i);
        textures[i].bind();
    }

	glUniform3f(glGetUniformLocation(shader.getId(), "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
	camera.linkToShader(shader, "camera");
    glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);
	trans = glm::translate(trans, translation);
	sca = glm::scale(sca, scale);
	glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
	glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
	glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
	glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	
}

void Mesh::rotate(float theta, axis a) {
	float cosTheta = (float)cos(glm::radians(theta));
	float sinTheta = (float)sin(glm::radians(theta));
	glm::mat4 r(1.f);
	if (a == X_AXIS) {
		r[1][1] = cosTheta;
		r[2][1] = sinTheta;
		r[2][2] = cosTheta;
		r[1][2] = -sinTheta;
	} else if (a == Z_AXIS) {
		r[0][0] = cosTheta;
		r[0][2] = sinTheta;
		r[2][2] = cosTheta;
		r[2][0] = -sinTheta;
	} else if (a == Y_AXIS) {
		r[0][0] = cosTheta;
		r[1][0] = sinTheta;
		r[1][1] = cosTheta;
		r[0][1] = -sinTheta;
	} else return;
	rot *= r;
}

void Mesh::translate(float displacement, axis a) {
	if (a == X_AXIS) translation.x += displacement;
	else if (a == Y_AXIS) translation.y += displacement;
	else if (a == Z_AXIS) translation.z += displacement;
	else return;
}

void Mesh::setScale(float scale) {
	this->scale.x = scale;
	this->scale.y = scale;
	this->scale.z = scale;
}