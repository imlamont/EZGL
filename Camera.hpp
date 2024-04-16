#pragma once

#include <glm/glm.hpp>

namespace EZGL {
	class Camera
	{
	private:
		glm::vec3 pos;
		glm::vec3 look;

		unsigned int w;
		unsigned int h;
		float aspect;
		float fov; // y fov
		float nearClip;
		float farClip;
	public:
		Camera(glm::vec3 pos, glm::vec3 look, unsigned int w = 400, unsigned int h = 400, float fov = 45, float nearClip = 0.1f, float farClip = 1000.0f);

		glm::mat4 getViewProj() const;
		void setPos(glm::vec3 posVec);
		void setLook(glm::vec3 lookVec);
		void setPosLook(glm::vec3 posVec, glm::vec3 lookVec);
	};
}
