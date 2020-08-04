#pragma once

#include "stdafx.h"
#include "Model.h"
#include "Texture.h"

class Object {
private:
	int m_iID = 0;
	bool m_bIsAttributeChanged = false;

	int m_iModelID = 0;
	std::vector<int> m_aTextureID;
	int m_iCubeTextureID = 0;
	int m_iShaderID = 0;

	Matrix m_WorldMatrix;
	Matrix m_ScaleMatrix, m_RotationMatrix, m_TranslationMatrix;

	Vector3 m_WorldLocation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_ObjectRotation = Vector3(0.0f, 0.0f, 0.0f); // Angles in degrees
	Vector3 m_ObjectScale = Vector3(1.0f, 1.0f, 1.0f);
public:
	Object();
	Object(const Object& oCopy);
	~Object();

	void FlagChanges();
	void Update();

	int* GetID();
	int* GetModelID();
	std::vector<int>* GetTextureID();
	int* GetCubeTextureID();
	int* GetShaderID();

	Vector3* GetLocation();
	Vector3* GetRotation();
	Vector3* GetScale();

	Matrix GetWorldMatrix();
};