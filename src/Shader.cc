#include "Shader.h"
#include <GL/glew.h>
#include <spdlog/spdlog.h>
#include <memory>
Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
{

}

GLuint Shader::compile(const char* str, GLenum type)
{
	GLuint shader_obj = glCreateShader(type);
	if (!shader_obj) 
	{
		spdlog::error("Failed to create shader.");
		throw "Failed to create shader.";
	}

	glShaderSource(shader_obj, 1, &str, NULL);
	glCompileShader(shader_obj);

	GLint status;
	glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) 
	{
		const int IL_SIZE = 4096;
		;
		GLsizei length;
		std::shared_ptr<GLchar[]> message(new GLchar[IL_SIZE]);
		glGetShaderInfoLog(shader_obj, IL_SIZE, NULL, message.get());

		std::string str_type;
		if (type == GL_VERTEX_SHADER) {
			str_type = "VERTEX";
		} else if(type == GL_FRAGMENT_SHADER) {
			str_type = "FRAGMENT";
		}
		spdlog::error("SHADER COMPILATION ERROR ({}): \n {}", str_type, message);
	}
	return shader_obj;
}
