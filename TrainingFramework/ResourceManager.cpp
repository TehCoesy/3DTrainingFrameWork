#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

void ResourceManager::InitWithFile(std::string strFilePath) {
	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");

	// TODO: Write handling for successful / failed fopen;

	// Loading models
	fscanf(FileStream, " #Models: %d\n", &m_iModelsCount);

	for (int i = 0; i < m_iModelsCount; i++) {
		int iModelID = 0;
		char strBuffer[50]; // fscanf really do not like std::string

		fscanf(FileStream," ID %d\n", &iModelID);
		fscanf(FileStream, " FILE %s\n", strBuffer);

		// TODO: Write handling for double-quoted FilePath string

		Model graModel = LoadModel(iModelID, ResourcesFolder + std::string(strBuffer));
		
		m_aModels.push_back(graModel);

		// Release Buffers
		//if (strBuffer) delete[] strBuffer;
	}

	// Loading 2D textures
	fscanf(FileStream, " #2D Textures: %d\n", &m_iTexturesCount);

	for (int i = 0; i < m_iTexturesCount; i++) {
		int iTextureID = 0;
		char strNameBuffer[50], strTilingBuffer[50];

		fscanf(FileStream, " ID %d\n", &iTextureID);
		fscanf(FileStream, " FILE %s\n", strNameBuffer);
		fscanf(FileStream, " TILING %s\n", strTilingBuffer);

		Texture graTexture = LoadTexture(iTextureID, ResourcesFolder + std::string(strNameBuffer), strTilingBuffer);
		
		m_aTextures.push_back(graTexture);

		// Release Buffers
		//if (strNameBuffer) delete[] strNameBuffer;
		//if (strTilingBuffer) delete[] strTilingBuffer;
	}

	// Loading Cube Textures
	fscanf(FileStream, " #Cube Textures: %d\n", &m_iCubeTexturesCount);

	for (int i = 0; i < m_iCubeTexturesCount; i++) {
		int iTextureID = 0;
		char strFileBuffer[100], strTilingBuffer[50];
		std::vector<std::string> strFiles;

		fscanf(FileStream, " ID %d\n", &iTextureID);

		fscanf(FileStream, " TOP %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));
		fscanf(FileStream, " BOTTOM %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));
		fscanf(FileStream, " FRONT %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));
		fscanf(FileStream, " BACK %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));
		fscanf(FileStream, " LEFT %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));
		fscanf(FileStream, " RIGHT %s\n", strFileBuffer);
		strFiles.push_back(std::string(strFileBuffer));

		fscanf(FileStream, " TILING %s\n", strTilingBuffer);

		Texture graTexture = LoadCubeTexture(iTextureID, strFiles, strTilingBuffer);

		m_aCubeTextures.push_back(graTexture);

		// Release Buffers
		//if (strFileBuffer) delete[] strFileBuffer;
		//if (strTilingBuffer) delete[] strTilingBuffer;
	}

	// Loading Shaders
	fscanf(FileStream, " #Shaders: %d\n", &m_iShadersCount);

	*m_Shaders.GetShadersCount() = m_iShadersCount;

	for (int i = 0; i < m_iShadersCount; i++) {
		int iShaderID = 0, iStateCount = 0;
		char strVSBuffer[100], strFSBuffer[100];

		fscanf(FileStream, " ID %d\n", &iShaderID);
		fscanf(FileStream, " VS %s\n", strVSBuffer);
		fscanf(FileStream, " FS %s\n", strFSBuffer);
		fscanf(FileStream, " STATES %d\n", &iStateCount);

		m_Shaders.GetShadersID()->push_back(iShaderID);
		m_Shaders.GetVSFiles()->push_back(std::string(strVSBuffer));
		m_Shaders.GetFSFiles()->push_back(std::string(strFSBuffer));

		for (int f = 0; f < iStateCount; f++) {
			// TODO: Handle Shaders states
		}

		// Release Buffers
		//if (strVSBuffer) delete[] strVSBuffer;
		//if (strFSBuffer) delete[] strFSBuffer;
	}

	m_Shaders.Init();
}

Model ResourceManager::LoadModel(int iModelID, std::string strFilePath) {
	Model graModel;

	*graModel.GetID() = iModelID;
	*graModel.GetModelName() = strFilePath;

	FILE* FileStream;
	FileStream = fopen(strFilePath.c_str(), "r");

	// Reading Vertices
	fscanf(FileStream, "NrVertices: %d\n", graModel.GetVerticesCount());

	for (int i = 0; i < *graModel.GetVerticesCount(); i++) {
		Vertex NewVertex;
		fscanf(FileStream, " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&NewVertex.pos.x, &NewVertex.pos.y, &NewVertex.pos.z,
			&NewVertex.normal.x, &NewVertex.normal.y, &NewVertex.normal.z,
			&NewVertex.binormal.x, &NewVertex.binormal.y, &NewVertex.binormal.z,
			&NewVertex.tangent.x, &NewVertex.tangent.y, &NewVertex.tangent.z,
			&NewVertex.uv.x, &NewVertex.uv.y
		);
		graModel.GetVerticesData()->push_back(NewVertex);
	}

	// Reading Indices
	fscanf(FileStream, "NrIndices: %d\n", graModel.GetIndicesCount());

	for (int i = 0; i < *graModel.GetIndicesCount(); i += 3) {
		GLuint NewIndex1, NewIndex2, NewIndex3;
		fscanf(FileStream, " %*d. %d, %d, %d\n",
			&NewIndex1,
			&NewIndex2,
			&NewIndex3
		);
		graModel.GetIndicesData()->push_back(NewIndex1);
		graModel.GetIndicesData()->push_back(NewIndex2);
		graModel.GetIndicesData()->push_back(NewIndex3);
	}

	// Creating VBO Buffer
	GLuint VBOid;

	glGenBuffers(1, &VBOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, *graModel.GetVerticesCount() * sizeof(Vertex), graModel.GetVerticesData()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	*graModel.GetVBOId() = VBOid;

	// Creating IBO Buffer
	GLuint IBOid;

	glGenBuffers(1, &IBOid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, *graModel.GetIndicesCount() * sizeof(GLuint), graModel.GetIndicesData()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	*graModel.GetIBOId() = IBOid;

	return graModel;
}

Texture ResourceManager::LoadTexture(int iTextureID, std::string strFilePath, std::string strTiling) {
	Texture graTexture;

	*graTexture.GetID() = iTextureID;

	GLuint uiTextureID;

	// Creating OpenGL ES texture resource and get the handle
	glGenBuffers(1, &uiTextureID);

	// Bind texture to 2D texture type
	glBindTexture(GL_TEXTURE_2D, uiTextureID);

	// Create CPU buffer and load image data
	int iWidth, iHeight, iBPP;
	char* bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);

	// Load data into OpenGL ES texture resource
	if (iBPP == 24) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
	}

	// Release memory
	//if (bufferTGA) delete[] bufferTGA;

	// Set wrapping modes
	if (strTiling == "REPEAT") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (strTiling == "CLAMP") {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	// Set filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	*graTexture.GetTextureID() = uiTextureID;

	return graTexture;
}

Texture ResourceManager::LoadCubeTexture(int iTextureID, std::vector<std::string> strFiles, std::string strTiling) {
	Texture graTexture;

	*graTexture.GetID() = iTextureID;

	GLuint uiTextureID;

	// Creating OpenGL ES texture resource and get the handle
	glGenBuffers(1, &uiTextureID);

	// Bind texture to Cube Texture type
	glBindTexture(GL_TEXTURE_CUBE_MAP, uiTextureID);

	// TOP
	std::string strFilePath = ResourcesFolder + strFiles.at(0);
	int iWidth, iHeight, iBPP;
	char* bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// BOTTOM
	strFilePath = ResourcesFolder + strFiles.at(1);
	bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// FRONT
	strFilePath = ResourcesFolder + strFiles.at(2);
	bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// BACK
	strFilePath = ResourcesFolder + strFiles.at(3);
	bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// LEFT
	strFilePath = ResourcesFolder + strFiles.at(4);
	bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// RIGHT
	strFilePath = ResourcesFolder + strFiles.at(5);
	bufferTGA = LoadTGA(strFilePath.c_str(), &iWidth, &iHeight, &iBPP);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, iHeight, iWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);

	// Release memory
	//if (bufferTGA) delete[] bufferTGA;

	// Set wrapping modes
	if (strTiling == "REPEAT") {
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (strTiling == "CLAMP") {
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	// Set filters for minification and magnification
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Unbind texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	*graTexture.GetTextureID() = uiTextureID;

	return graTexture;
}

Model ResourceManager::GetModel(int iID) {
	for (int i = 0; i < m_iModelsCount; i++) {
		if (*m_aModels.at(i).GetID() == iID) {
			return m_aModels.at(i);
		}
	}
	Model EmptyModel;
	return EmptyModel;
}

Texture ResourceManager::GetTexture(int iID) {
	for (int i = 0; i < m_iTexturesCount; i++) {
		if (*m_aTextures.at(i).GetID() == iID) {
			return m_aTextures.at(i);
		}
	}
	Texture EmptyTexture;
	return EmptyTexture;
}

Texture ResourceManager::GetCubeTexture(int iID) {
	for (int i = 0; i < m_iCubeTexturesCount; i++) {
		if (*m_aCubeTextures.at(i).GetID() == iID) {
			return m_aCubeTextures.at(i);
		}
	}
	Texture EmptyTexture;
	return EmptyTexture;
}

Shaders* ResourceManager::GetShaders() {
	return &m_Shaders;
}