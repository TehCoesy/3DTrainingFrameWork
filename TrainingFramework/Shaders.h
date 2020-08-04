#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h"

class Shaders 
{
private:
	int m_iID = 0;
	std::string m_strVSFile, m_strFSFile;
public:
	Shaders();
	~Shaders();

	GLuint program = 0, vertexShader = 0, fragmentShader = 0;
	GLint positionAttribute = 0;
	GLint uvAttribute = 0;
	GLint iTextureLoc = 0;
	GLint iCubeTextureLoc = 0;
	GLint iWVPLoc = 0;

	int Init(std::string strVSFile, std::string strFSFile);
	
	int* GetID();
	std::string GetVSFileStr();
	std::string GetFSFileStr();
};