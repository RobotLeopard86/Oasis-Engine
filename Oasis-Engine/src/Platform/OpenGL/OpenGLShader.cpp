#include "OasisPCH.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Oasis {
	Shader* Shader::Generate(std::string& vertexSrc, std::string fragmentSrc) {
		return new OpenGLShader(vertexSrc, fragmentSrc);
	}

	OpenGLShader::OpenGLShader(std::string& vertexSrc, std::string fragmentSrc) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = vertexSrc.c_str();

		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);
			OE_CORE_ERROR("Info log: {0}", infoLog.data());
			OE_COREASSERT(false, "Vertex shader failed to compile!", (unsigned int)renderId);
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = fragmentSrc.c_str();

		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);
			OE_CORE_ERROR("Info log: {0}", infoLog.data());
			OE_COREASSERT(false, "Fragment shader failed to compile!");
			return;
		}

		renderId = glCreateProgram();
		GLuint program = renderId;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			OE_CORE_ERROR("Info log: {0}", infoLog.data());
			OE_COREASSERT(false, "Shader program failed to compile!", (unsigned int)renderId);
			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {}

	void OpenGLShader::Bind() const {
		glUseProgram(renderId);
	}

	void OpenGLShader::Unbind() const {
		glDeleteProgram(renderId);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint uniformLocation = glGetUniformLocation(renderId, name.c_str());
		if (uniformLocation == -1) {
			OE_COREASSERT(false, "Cannot upload data to nonexistent uniform!");
			return;
		}
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}