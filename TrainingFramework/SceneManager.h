#pragma once

#include "stdafx.h"
#include "ResourceManager.h"
#include "Singleton.h"
#include "Object.h"
#include "Camera.h"

#define RMInstance ResourceManager::GetInstance()

class SceneManager : public Singleton<SceneManager> {
public:
	SceneManager();
	~SceneManager();

	void InitWithFile(std::string strFilePath);

	Camera m_Camera;

	void Update(float fDeltaTime);
	void Draw();
private:
	int m_iObjectCount = 0;
	std::vector<Object> m_aObjects;
};