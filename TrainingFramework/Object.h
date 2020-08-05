#pragma once

#include "stdafx.h"
#include "Model.h"
#include "Texture.h"

class Object {
private:
	int m_iID = -1;
	bool m_bIsAttributeChanged = false;

	int m_iModelID = -1;
	std::vector<int> m_aTextureID;
	int m_iCubeTextureID = -1;
	int m_iShaderID = -1;

	Matrix m_WorldMatrix;
	Matrix m_ScaleMatrix, m_RotationMatrix, m_TranslationMatrix;

	Vector3 m_WorldLocation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_ObjectRotation = Vector3(0.0f, 0.0f, 0.0f); // Angles in degrees
	Vector3 m_ObjectScale = Vector3(1.0f, 1.0f, 1.0f);
public:
	Object();
	Object(const Object& CopyObject);
	~Object();

	void FlagChanges();
	void Update();

	std::string strTextureMode = "";

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