#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
}

void SceneManager::InitWithFile(std::string strFilePath) {
	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");

	// Loading objects;
	fscanf(FileStream, " #Objects: %d\n", &m_iObjectCount);

	for (int i = 0; i < m_iObjectCount; i++) {
		Object NewObject;

		fscanf(FileStream, " ID %d\n", NewObject.GetID());

		// Loading Model for Object
		int iModelID = -1; 
		fscanf(FileStream, " MODEL %d\n", &iModelID);

		// Loading 2D Textures
		int iTexturesCount = -1;
		fscanf(FileStream, " TEXTURES %d\n", &iTexturesCount);
		
		for (int f = 0; f < iTexturesCount; f++) {
			int iTexturesID;
			fscanf(FileStream, " TEXTURE %d\n", &iTexturesID);

			NewObject.GetTextureID()->push_back(iTexturesID);
		}

		// Loading Cube Textures
		int iCubeTexturesCount = -1;
		fscanf(FileStream, " CUBETEXTURES %d\n", &iCubeTexturesCount);

		for (int f = 0; f < iCubeTexturesCount; i++) {
			int iCubeTexturesID;
			fscanf(FileStream, " CUBETEX %d\n", &iCubeTexturesID);

			*NewObject.GetCubeTextureID() = iCubeTexturesID; // Not handling more than one CubeTex
			break;
		}

		// Loading Shaders;
		fscanf(FileStream, " SHADER %d\n", NewObject.GetShaderID());

		// Loading Object WorldLocation;
		Vector3 vPosition, vRotation, vScale;
		fscanf(FileStream, " POSITION %f, %f, %f \n", &vPosition.x, &vPosition.y, &vPosition.z);
		fscanf(FileStream, " ROTATION %f, %f, %f \n", &vRotation.x, &vRotation.y, &vRotation.z);
		fscanf(FileStream, " SCALE %f, %f, %f \n", &vScale.x, &vScale.y, &vScale.z);

		*NewObject.GetLocation() = vPosition;
		*NewObject.GetRotation() = vRotation;
		*NewObject.GetScale() = vScale;

		m_aObjects.push_back(NewObject);
	}

	// Loading Camera
	float fFov = 0.0f, fAspectRatio = 4.0f / 3.0f, fNear = 0.0f, fFar = 0.0f, fSpeed = 0.0f;
	fscanf(FileStream,"#CAMERA\n");
	fscanf(FileStream, "NEAR %f\n", &fNear);
	fscanf(FileStream, "FAR %f\n", &fFar);
	fscanf(FileStream, "FOV %f\n", &fFov);
	fscanf(FileStream, "SPEED %f\n", &fSpeed);

	m_Camera = Camera(fFov, fAspectRatio, fNear, fFar, fSpeed);
}

void SceneManager::Update(float fDeltaTime) {
	for (int i = 0; i < m_iObjectCount; i++) {
		m_aObjects[i].Update(); 
	}
}

void SceneManager::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < m_iObjectCount; i++) {
		// Loading Shader
		int iShaderID = *m_aObjects.at(i).GetShaderID();
		Shaders MyShader = RMInstance->GetShader(iShaderID);
		glUseProgram(MyShader.program);

		//	Loading Model and Textures
		int ObjectModelID = *m_aObjects.at(i).GetModelID();
		int ObjectTextureID = m_aObjects.at(i).GetTextureID()->at(0);

		Model ObjectModel = RMInstance->GetModel(ObjectModelID);
		Texture ObjectTexture = RMInstance->GetTexture(ObjectTextureID);

		GLuint VBOId = *ObjectModel.GetVBOId();
		GLuint IBOId = *ObjectModel.GetIBOId();

		GLuint TextureID = *ObjectTexture.GetTextureID();

		int iIndicesCount = *ObjectModel.GetIndicesCount();

		// Loading Object's WVP
		Matrix WorldMatrix = m_aObjects.at(i).GetWorldMatrix();
		Matrix ViewMatrix = *m_Camera.GetViewMatrix();
		Matrix ProjectionMatrix = *m_Camera.GetProjectionMatrix();

		Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		// Position attribute
		if (MyShader.positionAttribute != -1)
		{
			glEnableVertexAttribArray(MyShader.positionAttribute);
			glVertexAttribPointer(MyShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}

		// UV attribute
		if (MyShader.uvAttribute != -1) {
			glEnableVertexAttribArray(MyShader.uvAttribute);
			glVertexAttribPointer(MyShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
		}

		// Texture Uniform
		if (MyShader.iTextureLoc != -1)
		{
			glUniform1i(MyShader.iTextureLoc, 0);
		}

		// WVP Uniform
		if (MyShader.iWVPLoc != -1) {
			glUniformMatrix4fv(MyShader.iWVPLoc, 1, GL_FALSE, &WVP.m[0][0]);
		}

		glDrawElements(GL_TRIANGLES, iIndicesCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_TEXTURE_2D, 0);
	}
}