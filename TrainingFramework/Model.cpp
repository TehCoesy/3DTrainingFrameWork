#include "stdafx.h"
#include "Model.h"

Model::Model() {
}

Model::~Model() {
}

int* Model::GetID() {
	return &m_iID;
}

std::string* Model::GetModelName() {
	return &m_strModelName;
}

std::vector<Vertex>* Model::GetVerticesData() {
	return &m_aVerticesData;
}

std::vector<GLuint>* Model::GetIndicesData() {
	return &m_aIndicesData;
}

GLuint* Model::GetVBOId() {
	return &m_uiVBOId;
}

GLuint* Model::GetIBOId() {
	return &m_uiIBOId;
}

int* Model::GetVerticesCount() {
	return &m_iVerticesCount;
}

int* Model::GetIndicesCount() {
	return &m_iIndicesCount;
}