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
		fscanf(FileStream, " MODEL %d\n", NewObject.GetModelID());

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

		// Determine Object's TextureMode
		if (iTexturesCount > 1) {
			NewObject.strTextureMode = "MULTI";
		}
		else if (iTexturesCount == 1) {
			NewObject.strTextureMode = "SINGLE";
		}
		else if (iCubeTexturesCount == 1) {
			NewObject.strTextureMode = "CUBE";
		}

		// Loading ShaderID;
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
		Object CurrentObject = m_aObjects.at(i);

		// Loading Shader
		int iShaderID = *CurrentObject.GetShaderID();
		Shaders* MyShader = RMInstance->GetShaders();
		glUseProgram(MyShader->GetProgram(iShaderID));

		//	Loading Model
		int ObjectModelID = *CurrentObject.GetModelID();

		Model ObjectModel = RMInstance->GetModel(ObjectModelID);

		GLuint VBOId = *ObjectModel.GetVBOId();
		GLuint IBOId = *ObjectModel.GetIBOId();

		int iIndicesCount = *ObjectModel.GetIndicesCount();

		// Loading Object's WVP
		Matrix WorldMatrix = CurrentObject.GetWorldMatrix();
		Matrix ViewMatrix = *m_Camera.GetViewMatrix();
		Matrix ProjectionMatrix = *m_Camera.GetProjectionMatrix();

		Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);

		glActiveTexture(GL_TEXTURE0);
		if (CurrentObject.strTextureMode == "SINGLE") {
			Texture ObjectTexture = RMInstance->GetTexture(CurrentObject.GetTextureID()->at(0));
			GLuint TextureID = *ObjectTexture.GetTextureID();

			glBindTexture(GL_TEXTURE_2D, TextureID);
		}
		else if (CurrentObject.strTextureMode == "CUBE") {
			Texture ObjectTexture = RMInstance->GetCubeTexture(*CurrentObject.GetCubeTextureID());
			GLuint TextureID = *ObjectTexture.GetTextureID();

			glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
		}
		
		MyShader->LoadProgramAttribute(MyShader->GetProgram(iShaderID));

		// Position attribute
		if (MyShader->positionAttribute != -1)
		{
			glEnableVertexAttribArray(MyShader->positionAttribute);
			glVertexAttribPointer(MyShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}

		// UV attribute
		if (MyShader->uvAttribute != -1) {
			glEnableVertexAttribArray(MyShader->uvAttribute);
			glVertexAttribPointer(MyShader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
		}

		// Texture Uniform
		if (MyShader->iTextureLoc != -1)
		{
			glUniform1i(MyShader->iTextureLoc, 0);
		}

		if (MyShader->iCubeTextureLoc != -1)
		{
			glUniform1i(MyShader->iCubeTextureLoc, 0);
		}

		// WVP Uniform
		if (MyShader->iWVPLoc != -1) {
			glUniformMatrix4fv(MyShader->iWVPLoc, 1, GL_FALSE, &WVP.m[0][0]);
		}

		glDrawElements(GL_TRIANGLES, iIndicesCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		if (CurrentObject.strTextureMode == "SINGLE") {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (CurrentObject.strTextureMode == "CUBE") {
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}