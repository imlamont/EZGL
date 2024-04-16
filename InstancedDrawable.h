#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Drawable.h"

namespace EZGL {

	class InstancedDrawable : public Drawable {
	protected:
		int numInstances;
		GLuint bufPosOffset;
		GLuint bufColOffset;

		bool posOffsetGenerated;
		bool colOffsetGenerated;

	public:
		InstancedDrawable();
		//~InstancedDrawable();

		virtual void destoryVBO();

		int getInstances() const;

		void generatePosOffset();
		void generateColOffset();

		bool bindPosOffset();
		bool bindColOffset();
	};
}