#include <fstream>
#include <iostream>
#include <vector>

#include "ShaderProgram.hpp"

namespace EZGL {
	ShaderProgram::ShaderProgram()
		: vertShader(), fragShader(), prog(),
		attrPos(-1), attrNor(-1), attrCol(-1), attrUV(-1), attrPosOffset(-1), attrColOffset(-1),
		unifModel(-1), unifModelInvTr(-1), unifViewProj(-1), unifTexture(-1) {

	}

	void printShaderInfoLog(int shader)
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar* infoLog;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

		if (infoLogLen > 0)
		{
			infoLog = new GLchar[infoLogLen];
			glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
			std::cout << "ShaderInfoLog:" << "\n" << infoLog << "\n";
			delete[] infoLog;
		}
	}

	void printGLErrorLog()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cerr << "OpenGL error " << error << ": ";
		}
	}

	void printLinkInfoLog(int prog)
	{
		int infoLogLen = 0;
		int charsWritten = 0;
		GLchar* infoLog;

		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogLen);

		// should additionally check for OpenGL errors here

		if (infoLogLen > 0) {
			infoLog = new GLchar[infoLogLen];
			// error check for fail to allocate memory omitted
			glGetProgramInfoLog(prog, infoLogLen, &charsWritten, infoLog);
			std::cout << "LinkInfoLog:" << "\n" << infoLog << "\n";
			delete[] infoLog;
		}
	}

	void loadShaderFile(GLuint shader, const char* file) {
		std::vector<char> vec;
		int size = 0;
		std::ifstream fs(file);

		if (!fs.is_open()) {
			std::cerr << "unable to open shader file: " << file;
		}

		while (!fs.eof()) {
			size++;
			vec.push_back(fs.get());
		}

		vec.push_back('\0');
		size++;

		const char* str = vec.data();

		glShaderSource(shader, 1, &str, (const int*)&size);

		fs.close();
		return;
	}

	void ShaderProgram::create(const char* vertFile, const char* fragFile) {
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		prog = glCreateProgram();

		// load and compile
		loadShaderFile(vertShader, vertFile);
		loadShaderFile(fragShader, fragFile);
		glCompileShader(vertShader);
		glCompileShader(fragShader);

		// check compile status
		GLint compiled;
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			printShaderInfoLog(vertShader);
		}
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			printShaderInfoLog(fragShader);
		}

		// link
		glAttachShader(prog, vertShader);
		glAttachShader(prog, fragShader);
		glLinkProgram(prog);

		// check link status
		GLint linked;
		glGetProgramiv(prog, GL_LINK_STATUS, &linked);
		if (!linked) {
			printLinkInfoLog(prog);
		}

		// get all attributes
		attrPos = glGetAttribLocation(prog, "vPos");
		attrNor = glGetAttribLocation(prog, "vNor");
		attrCol = glGetAttribLocation(prog, "vCol");
		attrUV = glGetAttribLocation(prog, "vUV");
		attrPosOffset = glGetAttribLocation(prog, "vPosOffset");
		attrColOffset = glGetAttribLocation(prog, "vColOffset");

		unifModel = glGetUniformLocation(prog, "uModel");
		unifModelInvTr = glGetUniformLocation(prog, "uModelInvTr");
		unifViewProj = glGetUniformLocation(prog, "uViewProj");
		unifTexture = glGetUniformLocation(prog, "uTexture");

	}

	void ShaderProgram::useThis() {
		glUseProgram(prog);
	}

	void ShaderProgram::setModelMatrix(const glm::mat4& model)
	{
		useThis();

		if (unifModel != -1) {
			glUniformMatrix4fv(unifModel, 1, GL_FALSE, &model[0][0]);
		}

		if (unifModelInvTr != -1) {
			glm::mat4 modelinvtr = glm::inverse(glm::transpose(model));
			glUniformMatrix4fv(unifModelInvTr, 1, GL_FALSE, &modelinvtr[0][0]);
		}
	}

	void ShaderProgram::setViewProjMatrix(const glm::mat4& vp)
	{
		useThis();

		if (unifViewProj != -1) {
			glUniformMatrix4fv(unifViewProj, 1, GL_FALSE, &vp[0][0]);
		}
	}

	void ShaderProgram::setTextureSlot(int slot) {
		useThis();

		if (unifTexture != -1) {
			glUniform1i(unifTexture, slot);
		}
	}

	void ShaderProgram::draw(Drawable& d) {
		useThis();

		if (d.getElems() < 0) return;

		if (attrPos != -1 && d.bindPos()) {
			glEnableVertexAttribArray(attrPos);
			glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrNor != -1 && d.bindNor()) {
			glEnableVertexAttribArray(attrNor);
			glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrCol != -1 && d.bindCol()) {
			glEnableVertexAttribArray(attrCol);
			glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrUV != -1 && d.bindUV()) {
			glEnableVertexAttribArray(attrUV);
			glVertexAttribPointer(attrUV, 2, GL_FLOAT, false, 0, NULL);
		}

		d.bindIdx();
		glDrawElements(d.drawMode(), d.getElems(), GL_UNSIGNED_INT, 0);

		if (attrPos != -1) glDisableVertexAttribArray(attrPos);
		if (attrNor != -1) glDisableVertexAttribArray(attrNor);
		if (attrCol != -1) glDisableVertexAttribArray(attrCol);
		if (attrUV != -1) glDisableVertexAttribArray(attrUV);

		printGLErrorLog();
	}

	void ShaderProgram::draw(InstancedDrawable& d) {
		useThis();

		if (d.getElems() < 0) return;

		if (attrPos != -1 && d.bindPos()) {
			glEnableVertexAttribArray(attrPos);
			glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrNor != -1 && d.bindNor()) {
			glEnableVertexAttribArray(attrNor);
			glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrCol != -1 && d.bindCol()) {
			glEnableVertexAttribArray(attrCol);
			glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, 0, NULL);
		}

		if (attrUV != -1 && d.bindUV()) {
			glEnableVertexAttribArray(attrUV);
			glVertexAttribPointer(attrUV, 2, GL_FLOAT, false, 0, NULL);
		}

		if (attrPosOffset != -1 && d.bindPosOffset()) {
			glEnableVertexAttribArray(attrPosOffset);
			glVertexAttribPointer(attrPosOffset, 4, GL_FLOAT, false, 0, NULL);
			glVertexAttribDivisor(attrPosOffset, 1);
		}

		if (attrColOffset != -1 && d.bindColOffset()) {
			glEnableVertexAttribArray(attrColOffset);
			glVertexAttribPointer(attrColOffset, 4, GL_FLOAT, false, 0, NULL);
			glVertexAttribDivisor(attrColOffset, 1);
		}

		d.bindIdx();
		glDrawElementsInstanced(d.drawMode(), d.getElems(), GL_UNSIGNED_INT, 0, d.getInstances());

		if (attrPos != -1) glDisableVertexAttribArray(attrPos);
		if (attrNor != -1) glDisableVertexAttribArray(attrNor);
		if (attrCol != -1) glDisableVertexAttribArray(attrCol);
		if (attrUV != -1) glDisableVertexAttribArray(attrUV);
		if (attrPosOffset != -1) glDisableVertexAttribArray(attrPosOffset);
		if (attrColOffset != -1) glDisableVertexAttribArray(attrColOffset);

		printGLErrorLog();
	}
}