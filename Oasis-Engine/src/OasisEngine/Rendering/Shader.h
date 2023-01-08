#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Oasis {
	class Shader {
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Generate(std::string& vertexSrc, std::string fragmentSrc);
	};
}