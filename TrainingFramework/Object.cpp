#include "stdafx.h"
#include "Object.h"

Object::Object() {
}

Object::Object(const Object& oCopy) {
	m_iID = oCopy.m_iID;

	m_iModelID = oCopy.m_iModelID;
	m_aTextureID = oCopy.m_aTextureID;

	m_WorldLocation.x = oCopy.m_WorldLocation.x;	m_WorldLocation.y = oCopy.m_WorldLocation.y;	m_WorldLocation.z = oCopy.m_WorldLocation.z;
	m_ObjectRotation.x = oCopy.m_ObjectRotation.x;	m_ObjectRotation.y = oCopy.m_ObjectRotation.y;	m_ObjectRotation.z = oCopy.m_ObjectRotation.z;
	m_ObjectScale.x = oCopy.m_ObjectScale.x;	m_ObjectScale.y = oCopy.m_ObjectScale.y;	m_ObjectScale.z = oCopy.m_ObjectScale.z;

	FlagChanges();
	Update();
}

Object::~Object() {
}

int* Object::GetID() {
	return &m_iID;
}

int* Object::GetModelID() {
	return &m_iModelID;
}

std::vector<int>* Object::GetTextureID() {
	return &m_aTextureID;
}

int* Object::GetCubeTextureID() {
	return &m_iCubeTextureID;
}

int* Object::GetShaderID() {
	return &m_iShaderID;
}

Matrix Object::GetWorldMatrix() {
	return m_WorldMatrix;
}

void Object::FlagChanges() {
	if (!m_bIsAttributeChanged) m_bIsAttributeChanged = true;
}

void Object::Update() {
	if (m_bIsAttributeChanged) {
		m_ScaleMatrix.SetScale(m_ObjectScale);

		Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
		RotationMatrixX.SetRotationAngleAxis(m_ObjectRotation.x * (3.14f / 180.0f), 1, 0, 0);
		RotationMatrixY.SetRotationAngleAxis(m_ObjectRotation.y * (3.14f / 180.0f), 0, 1, 0);
		RotationMatrixZ.SetRotationAngleAxis(m_ObjectRotation.z * (3.14f / 180.0f), 0, 0, 1);
		m_RotationMatrix = RotationMatrixZ * RotationMatrixX * RotationMatrixY;

		m_TranslationMatrix.SetTranslation(m_WorldLocation);

		m_WorldMatrix.SetIdentity();
		m_WorldMatrix = m_WorldMatrix * m_ScaleMatrix * m_RotationMatrix * m_TranslationMatrix;

		m_bIsAttributeChanged = false;
	}
}

Vector3* Object::GetLocation() {
	return &m_WorldLocation;
}

Vector3* Object::GetRotation() {
	return &m_ObjectRotation;
}

Vector3* Object::GetScale() {
	return &m_ObjectScale;
} 