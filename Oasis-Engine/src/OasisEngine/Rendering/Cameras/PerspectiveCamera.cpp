#include "OasisPCH.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {
	PerspectiveCamera::PerspectiveCamera(float fov, float farPlane) 
		: projectionMatrix(glm::perspective(fov, 1.7777777f, 0.01f, farPlane)), viewMatrix(1.0f), position(0.0f), rotation(0.0f) {}

	void PerspectiveCamera::RecalculateViewMatrix() {
		viewMatrix = glm::lookAt(position, glm::vec3(rotation.x / 360, rotation.y / 360, rotation.z / 360), glm::vec3(0.0f, 1.0f, 0.0f));
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}