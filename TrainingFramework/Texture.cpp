#include "stdafx.h"
#include "Texture.h"

Texture::Texture() {
}

Texture::~Texture() {
}

int* Texture::GetID() {
	return &m_iID;
}

GLuint* Texture::GetTextureID() {
	return &m_uiTextureID;
}