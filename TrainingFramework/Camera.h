#pragma once

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class Camera {
private:
	float m_fFOV = 1.0;
	float m_fAspectRatio = 4.0f / 3.0f;
	float m_fNear = 0.1f;
	float m_fFar = 100.0f;
	float m_fCameraSpeed = 1.0f;

	Vector3 m_CameraPosition = Vector3(0.0f, 0.0f, 0.5f);
	Vector3 m_CameraTarget = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_CameraRotation = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 m_Up = Vector3(0, 1, 0);

	Matrix m_CameraTranslationMatrix;
	Matrix m_CameraRotationMatrix;

	Matrix m_ViewMatrix;
	Matrix m_ProjectionMatrix;
public:
	Camera();
	Camera(float fFov, float fAspectRatio, float fNear, float fFar, float fSpeed);
	~Camera();

	void Recalculate();

	void MoveForward(float fFrameTime);
	void MoveBack(float fFrameTime);
	void MoveLeft(float fFrameTime);
	void MoveRight(float fFrameTime);

	void RotateUp();
	void RotateDown();
	void RotateLeft();
	void RotateRight();

	Matrix* GetViewMatrix();
	Matrix* GetProjectionMatrix();
};