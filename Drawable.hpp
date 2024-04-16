#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace EZGL {
	class Drawable {
	protected:
		int numElems;

		GLuint bufIdx;
		GLuint bufPos;
		GLuint bufNor;
		GLuint bufCol;
		GLuint bufUV;

		bool idxGenerated;
		bool posGenerated;
		bool norGenerated;
		bool colGenerated;
		bool uvGenerated;

	public:
		Drawable();
		//~Drawable();

		virtual void createVBO() = 0;
		virtual void destoryVBO();

		int getElems() const;
		virtual GLenum drawMode() const;

		void generateIdx();
		void generatePos();
		void generateNor();
		void generateCol();
		void generateUV();

		bool bindIdx();
		bool bindPos();
		bool bindNor();
		bool bindCol();
		bool bindUV();
	};
}