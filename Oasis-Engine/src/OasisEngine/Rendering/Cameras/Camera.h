#pragma once

#include <glm/glm.hpp>

namespace Oasis {
	class Camera {
	public:
		virtual const glm::vec3& GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& pos) = 0;
		virtual const glm::vec3& GetRotation() const = 0;
		virtual void SetRotation(const glm::vec3& rot) = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
	};
}