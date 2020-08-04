#include "stdafx.h"
#include "Shaders.h"

Shaders::Shaders() {
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

int Shaders::Init(std::string strVSFile, std::string strFSFile)
{
	char* strBuffer = new char[250];

	std::strcpy(strBuffer, strVSFile.c_str());

	vertexShader = esLoadShader(GL_VERTEX_SHADER, strBuffer);

	if ( vertexShader == 0 )
		return -1;

	std::strcpy(strBuffer, strFSFile.c_str());

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, strBuffer);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	iTextureLoc = glGetUniformLocation(program, "u_texture");
	iWVPLoc = glGetUniformLocation(program, "m_wvp");

	m_strVSFile = strVSFile;
	m_strFSFile = strFSFile;

	return 0;
}

std::string Shaders::GetVSFileStr() {
	return m_strVSFile;
}

std::string Shaders::GetFSFileStr() {
	return m_strFSFile;
}

int* Shaders::GetID() {
	return &m_iID;
}