#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"

class Model {
private:
	int m_iID = 0;
	std::string m_strModelName;

	std::vector<Vertex> m_aVerticesData;
	std::vector<GLuint> m_aIndicesData;

	GLuint m_uiVBOId = 0;
	GLuint m_uiIBOId = 0;

	int m_iVerticesCount = 0;
	int m_iIndicesCount = 0;
public:
	Model();
	~Model();

	int* GetID();
	std::string* GetModelName();

	std::vector<Vertex>* GetVerticesData();
	std::vector<GLuint>* GetIndicesData();

	GLuint* GetVBOId();
	GLuint* GetIBOId();

	int* GetVerticesCount();
	int* GetIndicesCount();
};