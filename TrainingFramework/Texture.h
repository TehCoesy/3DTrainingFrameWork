#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Texture {
private:
	int m_iID = 0;
	std::string m_strTextureName;
	std::string m_strTiling;

	GLuint m_uiTextureID = 0;
public:
	Texture();
	~Texture();

	int* GetID();
	std::string* GetTextureName();
	std::string* GetTiling();

	GLuint* GetTextureID();
};