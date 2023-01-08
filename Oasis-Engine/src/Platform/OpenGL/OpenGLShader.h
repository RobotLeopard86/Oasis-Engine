#pragma once

#include "OasisEngine/Rendering/Shader.h"

namespace Oasis {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(std::string& vertexSrc, std::string fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	private:
		uint32_t renderId;
	};
}