#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Drawable.h"
#include "InstancedDrawable.h"

namespace EZGL {
	class ShaderProgram
	{
	private:
		GLuint vertShader;
		GLuint fragShader;
		GLuint prog;

		int attrPos;
		int attrNor;
		int attrCol;
		int attrUV;
		int attrPosOffset;
		int attrColOffset;

		int unifModel;
		int unifModelInvTr;
		int unifViewProj;
		int unifTexture;

	public:
		ShaderProgram();
		void create(const char* vertFile, const char* fragFile);

		void useThis();
		void setModelMatrix(const glm::mat4& model);
		void setViewProjMatrix(const glm::mat4& vp);
		void setTextureSlot(int slot);

		void draw(Drawable& d);
		void draw(InstancedDrawable& d);
	};

	void printShaderInfoLog(int shader);
	void printLinkInfoLog(int prog);
	void printGLErrorLog();
}