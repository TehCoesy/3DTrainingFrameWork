#include "stdafx.h"
#include "Shaders.h"

Shaders::Shaders() {
}

Shaders::~Shaders()
{
	for (int i = 0; i < m_aPrograms.size(); i++) {
		glDeleteProgram(m_aPrograms.at(i));
		glDeleteShader(m_aVertexShaders.at(i));
		glDeleteShader(m_aFragmentShaders.at(i));
	}
}

void Shaders::Init()
{
	for (int i = 0; i < m_iShaderCount; i++) {
		std::string strVSFile = ResourcesFolder + m_aVSFiles[i];
		std::string strFSFile = ResourcesFolder + m_aFSFiles[i];

		char* strBuffer = new char[250];

		std::strcpy(strBuffer, strVSFile.c_str());

		GLuint vertexShader = esLoadShader(GL_VERTEX_SHADER, strBuffer);

		m_aVertexShaders.push_back(vertexShader);

		// TODO: Handle esLoadShader failure

		std::strcpy(strBuffer, strFSFile.c_str());

		GLuint fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, strBuffer);

		m_aFragmentShaders.push_back(fragmentShader);

		GLuint program = esLoadProgram(vertexShader, fragmentShader);

		m_aPrograms.push_back(program);
	}
}

void Shaders::LoadProgramAttribute(GLuint program) {
	// Finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	iTextureLoc = glGetUniformLocation(program, "u_sampler2D");
	iCubeTextureLoc = glGetUniformLocation(program, "u_samplerCube");
	iWVPLoc = glGetUniformLocation(program, "u_WVP");
}

GLuint Shaders::GetProgram(int iID) {
	for (int i = 0; i < m_iShaderCount; i++) {
		if (m_aShaderID[i] == iID) {
			return m_aPrograms[i];
		}
	}
}

int* Shaders::GetShadersCount() {
	return &m_iShaderCount;
}

std::vector<int>* Shaders::GetShadersID() {
	return &m_aShaderID;
}

std::vector<std::string>* Shaders::GetVSFiles() {
	return &m_aVSFiles;
}

std::vector<std::string>* Shaders::GetFSFiles() {
	return &m_aFSFiles;
}