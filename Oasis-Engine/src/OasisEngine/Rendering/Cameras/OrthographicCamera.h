#pragma once

#include <glm/glm.hpp>

namespace Oasis {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		const glm::vec3& GetPosition() const { return position; }
		void SetPosition(const glm::vec3& pos) { position = pos; position.y *= -1; RecalculateViewMatrix(); }
		float GetRotation() const { return rotation; }
		void SetRotation(float rot) { rotation = rot; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;
		float rotation;

		void RecalculateViewMatrix();
	};
}