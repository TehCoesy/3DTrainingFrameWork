#include "stdafx.h"
#include "Texture.h"

Texture::Texture() {
}

Texture::~Texture() {
}

int* Texture::GetID() {
	return &m_iID;
}

std::string* Texture::GetTextureName() {
	return &m_strTextureName;
}

std::string* Texture::GetTiling() {
	return &m_strTiling;
}

GLuint* Texture::GetTextureID() {
	return &m_uiTextureID;
}