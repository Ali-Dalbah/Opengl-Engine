#include "../include/Shader.h"
std::string readFile(const char* file) {
	// FILE* f = fopen(file,  "rb");
	// fseek(f, 0, SEEK_END);
	// long size = ftell(f);
	// fseek(f, 0, SEEK_SET);
	// char *str = (char*) malloc(size + 1);
	// freadFile(str, size, 1, f);
	// fclose(f);
	// *(str + size) = '\000';
	// return str;
	std::ifstream in(file, std::ios::binary);
	if (in)  {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
Shader::Shader(const char* vertexFile, const char* fragFile) {
	std::string v = readFile(vertexFile);
	std::string f = readFile(fragFile);
	const char* vSrc = v.c_str();
	const char* fSrc = f.c_str();
	int success;
	GLchar info[512];
	//std::cout<<vSrc<<fSrc<<std::endl;
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vSrc, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, sizeof(info), NULL, info);
		std::cout<<"Shader Vertex Compile Error\n"<<info<<std::endl;
	}
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fSrc, NULL);
	glCompileShader(fShader);
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, info);
		printf("Shader Fragment Compile Error %s\n", info);
	}
	this->id = glCreateProgram();
	glAttachShader(this->id, vShader);
	glAttachShader(this->id, fShader);
	glLinkProgram(this->id);
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

GLuint Shader::getId() {return this->id;}

void Shader::activate(){ glUseProgram(this->id);}

void Shader::remove() {
	glDeleteProgram(this->id);
}

Shader::~Shader() {}