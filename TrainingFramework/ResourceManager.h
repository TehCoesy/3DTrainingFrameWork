#pragma once

#include "stdafx.h"
#include "Singleton.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

#define ResourcesFolder "../Resources/"

class ResourceManager : public Singleton<ResourceManager> {
public:
	ResourceManager();
	~ResourceManager();
	
	void InitWithFile(std::string strFilePath);

	Model GetModel(int iID);
	Texture GetTexture(int iID);
	Texture GetCubeTexture(int iID);
	Shaders* GetShaders();
private:
	int m_iModelsCount = 0, m_iTexturesCount = 0, m_iCubeTexturesCount = 0, m_iShadersCount = 0;
	std::vector<Model> m_aModels;
	std::vector<Texture> m_aTextures;
	std::vector<Texture> m_aCubeTextures;
	Shaders m_Shaders;

	Model LoadModel(int iModelID, std::string strFile);
	Texture LoadTexture(int iTextureID, std::string strFile, std::string strTiling);
	Texture LoadCubeTexture(int iTextureID, std::vector<std::string> strFiles, std::string strTiling);
};