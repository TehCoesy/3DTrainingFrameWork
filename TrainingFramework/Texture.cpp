#include "stdafx.h"
#include "Texture.h"

Texture::Texture() {
}

Texture::Texture(const Texture& CopyTexture) {
	m_iID = CopyTexture.m_iID;
	m_uiTextureID = CopyTexture.m_uiTextureID;
}

Texture::~Texture() {
}

int* Texture::GetID() {
	return &m_iID;
}

GLuint* Texture::GetTextureID() {
	return &m_uiTextureID;
}