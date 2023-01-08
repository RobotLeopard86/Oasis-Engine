#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

namespace Oasis {
	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(float fov);

		const glm::vec3& GetPosition() const override { return position; }
		void SetPosition(const glm::vec3& pos) override { position = pos; position.y *= -1; RecalculateViewMatrix(); }
		const glm::vec3& GetRotation() const override { return rotation; }
		void SetRotation(const glm::vec3& rot) override { rotation = rot; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const override { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const override { return viewProjectionMatrix; }
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;
		glm::vec3 rotation;

		glm::vec3 lookTarget;

		void RecalculateViewMatrix();
		void RecalculateLookTarget();
	};
}