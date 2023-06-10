#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
std::string readFile(const char*);
class Shader {
private:
	GLuint id;
public:
	GLuint getId();
	Shader(const char*, const char*);
	~Shader();
	void activate();
	void remove();
};

#endif