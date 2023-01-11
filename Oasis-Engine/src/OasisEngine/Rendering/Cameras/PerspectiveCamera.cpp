#include "OasisPCH.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {
	PerspectiveCamera::PerspectiveCamera(float fov) 
		: projectionMatrix(glm::infinitePerspective(fov, 1.7777777f, 0.001f)), viewMatrix(1.0f), 
		position(0.0f), rotation(0.0f), viewProjectionMatrix(0.0f) {}

	void PerspectiveCamera::RecalculateViewMatrix() {
		RecalculateLookTarget();
		viewMatrix = glm::lookAt(position, lookTarget, glm::vec3(0.0f, 1.0f, 0.0f));
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void PerspectiveCamera::RecalculateLookTarget() {
		float xRotRadians = glm::radians(rotation.x);
		float yRotRadians = glm::radians(rotation.y);

		lookTarget.x = sqrt((1 - pow(sin(xRotRadians), 2)) / (1 + pow(tan(yRotRadians), 2)));
		lookTarget.y = sin(xRotRadians);
		lookTarget.z = lookTarget.x * tan(yRotRadians);

		lookTarget += position;
	}
}