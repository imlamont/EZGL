#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace EZGL {
	Camera::Camera(glm::vec3 pos, glm::vec3 look, unsigned int w, unsigned int h, float fov, float near, float far) 
	: pos(pos), look(look), w(w), h(h), aspect((float)w / (float)h), fov(fov), nearClip(near), farClip(far) {

	}

	glm::mat4 Camera::getViewProj() const {
		return glm::perspective(glm::radians(fov), aspect, nearClip, farClip) * glm::lookAt(pos, pos + look, glm::vec3(0.f, 1.f, 0.f));
	}

	void Camera::setPos(glm::vec3 posVec) {
		pos = posVec;
	}

	void Camera::setLook(glm::vec3 lookVec) {
		look = lookVec;
	}

	void Camera::setPosLook(glm::vec3 posVec, glm::vec3 lookVec) {
		pos = posVec;
		look = lookVec;
	}
}