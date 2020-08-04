#include "stdafx.h"
#include "Camera.h"

Camera::Camera() {
	Recalculate();
}

Camera::Camera(float fFov, float fAspectRatio, float fNear, float fFar, float fSpeed) {
	m_fFOV = fFov;
	m_fAspectRatio = fAspectRatio;
	m_fNear = fNear;
	m_fFar = fFar;
	m_fCameraSpeed = fSpeed;
	Recalculate();
}

Camera::~Camera() {
}

void Camera::Recalculate() {

	// Projection Matrix
	m_ProjectionMatrix.SetPerspective(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
	
	// Inverse of Camera Translation Matrix (T^-1)
	m_CameraTranslationMatrix.SetTranslation(-m_CameraPosition);

	// Inverse of Camera Rotation Matrix (R^-1)
	Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
	RotationMatrixX.SetRotationAngleAxis(-m_CameraRotation.x * (3.14f / 180.0f), 0, 1, 0); // Yaw (Rotate around Y)
	RotationMatrixY.SetRotationAngleAxis(-m_CameraRotation.y * (3.14f / 180.0f), 1, 0, 0); // Pitch (Rotate around X)
	RotationMatrixZ.SetRotationAngleAxis(-m_CameraRotation.z * (3.14f / 180.0f), 0, 0, 1); // Roll (Rotate around Z) 
	m_CameraRotationMatrix = RotationMatrixZ * RotationMatrixX * RotationMatrixY;

	// View Matrix
	m_ViewMatrix.SetIdentity();
	m_ViewMatrix = m_ViewMatrix * m_CameraTranslationMatrix * m_CameraRotationMatrix;
}

void Camera::MoveForward(float fFrameTime) {
	m_CameraPosition.x -= std::sinf(m_CameraRotation.x * (3.14f / 180.0f)) * m_fCameraSpeed * fFrameTime * 10.0f;
	m_CameraPosition.z -= std::cosf(m_CameraRotation.x * (3.14f / 180.0f)) * m_fCameraSpeed * fFrameTime * 10.0f;
}

void Camera::MoveBack(float fFrameTime) {
	m_CameraPosition.x += std::sinf(m_CameraRotation.x * (3.14f / 180.0f)) * m_fCameraSpeed * fFrameTime * 10.0f;
	m_CameraPosition.z += std::cosf(m_CameraRotation.x * (3.14f / 180.0f)) * m_fCameraSpeed * fFrameTime * 10.0f;
}

void Camera::MoveLeft(float fFrameTime) {
	m_CameraPosition.x -= m_fCameraSpeed * fFrameTime * 10;
}

void Camera::MoveRight(float fFrameTime) {
	m_CameraPosition.x += m_fCameraSpeed * fFrameTime * 10;
}

void Camera::RotateUp() {
	m_CameraRotation.y += 10.0f;
}

void Camera::RotateDown() {
	m_CameraRotation.y -= 10.0f;
}

void Camera::RotateLeft() {
	
	float fRotation = 10.0f;
	if (m_CameraRotation.x + fRotation > 360.0f) {
		m_CameraRotation.x = 0.0f + fRotation;
	}
	else {
		m_CameraRotation.x += 10.0f;
	}
}

void Camera::RotateRight() {
	float fRotation = 10.0f;
	if (m_CameraRotation.x - fRotation < 0.0f) {
		m_CameraRotation.x = 360.0f - fRotation;
	}
	else {
		m_CameraRotation.x -= 10.0f;
	}
}

Matrix* Camera::GetViewMatrix() {
	return &m_ViewMatrix;
}

Matrix* Camera::GetProjectionMatrix() {
	return &m_ProjectionMatrix;
}