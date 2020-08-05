#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h"

#define ResourcesFolder "../Resources/"

class Shaders 
{
private:
	int m_iShaderCount = 0;
	std::vector<std::string> m_aVSFiles, m_aFSFiles;
	std::vector<int> m_aShaderID;
	std::vector<GLuint> m_aPrograms;
	std::vector<GLuint> m_aVertexShaders;
	std::vector<GLuint> m_aFragmentShaders;
public:
	Shaders();
	~Shaders();

	GLint positionAttribute = -1;
	GLint uvAttribute = -1;
	GLint iCubeTextureLoc = -1;
	GLint iTextureLoc = -1;
	GLint iWVPLoc = -1;

	void Init();
	void LoadProgramAttribute(GLuint program);
	
	int* GetShadersCount();
	std::vector<int>* GetShadersID();
	std::vector<std::string>* GetVSFiles();
	std::vector<std::string>* GetFSFiles();
	
	GLuint GetProgram(int iID);
};