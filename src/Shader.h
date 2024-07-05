#ifndef SATRS_SHADER_H_
#define SATRS_SHADER_H_

#include <GL/glew.h>

#include <string>

class Shader {
public:
	Shader() = delete;
	Shader(const std::string &vertex_shader, const std::string &fragment_shader);
private:
	GLuint compile(const char *str, GLenum type);
};

#endif