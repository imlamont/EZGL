#include "InstancedDrawable.h"

namespace EZGL {
	InstancedDrawable::InstancedDrawable()
		: Drawable(), numInstances(-1), bufPosOffset(-1), bufColOffset(-1), posOffsetGenerated(false), colOffsetGenerated(false) {

	}

	void InstancedDrawable::destoryVBO() {
		Drawable::destoryVBO();

		glDeleteBuffers(1, &bufPosOffset);
		glDeleteBuffers(1, &bufColOffset);

		posOffsetGenerated = false;
		colOffsetGenerated = false;
		numInstances = -1;
	}

	int InstancedDrawable::getInstances() const {
		return numInstances;
	}

	void InstancedDrawable::generatePosOffset() {
		posOffsetGenerated = true;
		glGenBuffers(1, &bufPosOffset);
	}

	void InstancedDrawable::generateColOffset() {
		colOffsetGenerated = true;
		glGenBuffers(1, &bufColOffset);
	}

	bool InstancedDrawable::bindPosOffset() {
		if (posOffsetGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufPosOffset);
		}
		return posOffsetGenerated;
	}

	bool InstancedDrawable::bindColOffset() {
		if (colOffsetGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufColOffset);
		}
		return colOffsetGenerated;
	}
}