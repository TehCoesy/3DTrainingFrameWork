#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Texture {
private:
	int m_iID = 0;

	GLuint m_uiTextureID = 0;
public:
	Texture();
	Texture(const Texture& CopyTexture);
	~Texture();

	int* GetID();

	GLuint* GetTextureID();
};