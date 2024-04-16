#include "Drawable.h"

namespace EZGL {
	Drawable::Drawable()
		: numElems(-1), bufIdx(), bufPos(), bufNor(), bufCol(), bufUV(), idxGenerated(false), posGenerated(false), norGenerated(false), colGenerated(false), uvGenerated(false) {

	}

	void Drawable::destoryVBO() {
		glDeleteBuffers(1, &bufIdx);
		glDeleteBuffers(1, &bufPos);
		glDeleteBuffers(1, &bufNor);
		glDeleteBuffers(1, &bufCol);
		glDeleteBuffers(1, &bufUV);

		idxGenerated = false;
		posGenerated = false;
		norGenerated = false;
		colGenerated = false;
		uvGenerated = false;
		numElems = -1;
	}

	int Drawable::getElems() const {
		return numElems;
	}

	GLenum Drawable::drawMode() const {
		return GL_TRIANGLES;
	}

	void Drawable::generateIdx()
	{
		idxGenerated = true;
		glGenBuffers(1, &bufIdx);
	}

	void Drawable::generatePos()
	{
		posGenerated = true;
		glGenBuffers(1, &bufPos);
	}

	void Drawable::generateNor()
	{
		norGenerated = true;
		glGenBuffers(1, &bufNor);
	}

	void Drawable::generateCol()
	{
		colGenerated = true;
		glGenBuffers(1, &bufCol);
	}

	void Drawable::generateUV()
	{
		uvGenerated = true;
		glGenBuffers(1, &bufUV);
	}

	bool Drawable::bindIdx()
	{
		if (idxGenerated) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
		}
		return idxGenerated;
	}
	bool Drawable::bindPos()
	{
		if (posGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufPos);
		}
		return posGenerated;
	}

	bool Drawable::bindNor()
	{
		if (norGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufNor);
		}
		return norGenerated;
	}

	bool Drawable::bindCol()
	{
		if (colGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufCol);
		}
		return colGenerated;
	}

	bool Drawable::bindUV() {
		if (uvGenerated) {
			glBindBuffer(GL_ARRAY_BUFFER, bufUV);
		}
		return uvGenerated;
	}
}