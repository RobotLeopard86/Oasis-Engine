#include "OasisPCH.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {
	PerspectiveCamera::PerspectiveCamera(float fov, float farPlane = 1000.0f) 
		: projectionMatrix(glm::perspective(fov, 1.7777777f, 0.01f, farPlane)), viewMatrix(1.0f), position(0.0f), rotation(0.0f) {}

	void PerspectiveCamera::RecalculateViewMatrix() {
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * rotationMatrix;
		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}