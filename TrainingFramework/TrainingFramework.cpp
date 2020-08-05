// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Globals.h"
#include "Shaders.h"
#include "ResourceManager.h";
#include "SceneManager.h";

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

#include <conio.h>

#define RMInstance ResourceManager::GetInstance()
#define SMInstance SceneManager::GetInstance()

// Variables
Shaders myShaders;

Camera* graCamera;
unsigned int uiKeysPressed;

int Init ( ESContext *esContext )
{	
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	
	RMInstance->InitWithFile("../Resources/RM.txt");
	SMInstance->InitWithFile("../Resources/SM.txt");

	graCamera = &SMInstance->m_Camera;

	return 0;
}

void Draw ( ESContext *esContext )
{
	SMInstance->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

// Input booleans manipulations
void ClearBit(unsigned int *uiKeysPressed, int iPosition) {
	*uiKeysPressed &= ~(1 << iPosition);
}

void SetBit(unsigned int *uiKeysPressed, int iPosition) {
	*uiKeysPressed |= 1 << iPosition;
}

bool GetBit(unsigned int *uiKeysPressed, int iPosition) {
	unsigned int bBit = *uiKeysPressed & (1 << iPosition);
	if (bBit == 0) {
		return false;
	}
	else {
		return true;
	}
}

void Update ( ESContext *esContext, float deltaTime )
{
	if (GetBit(&uiKeysPressed, 0)) {
		ClearBit(&uiKeysPressed, 0);
		graCamera->MoveForward(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 1)) {
		ClearBit(&uiKeysPressed, 1);
		graCamera->MoveBack(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 2)) {
		ClearBit(&uiKeysPressed, 2);
		graCamera->MoveLeft(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 3)) {
		ClearBit(&uiKeysPressed, 3);
		graCamera->MoveRight(deltaTime);
	}
	if (GetBit(&uiKeysPressed, 4)) {
		ClearBit(&uiKeysPressed, 4);
		graCamera->RotateUp();
	}
	if (GetBit(&uiKeysPressed, 5)) {
		ClearBit(&uiKeysPressed, 5);
		graCamera->RotateDown();
	}
	if (GetBit(&uiKeysPressed, 6)) {
		ClearBit(&uiKeysPressed, 6);
		graCamera->RotateLeft();
	}
	if (GetBit(&uiKeysPressed, 7)) {
		ClearBit(&uiKeysPressed, 7);
		graCamera->RotateRight();
	}

	graCamera->Recalculate();

	SMInstance->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	// Up Key: Move Forward
	if (key == VK_UP && bIsPressed && !GetBit(&uiKeysPressed, 0)) {
		SetBit(&uiKeysPressed, 0);
	}

	// Down Key: Move Back
	if (key == VK_DOWN && bIsPressed && !GetBit(&uiKeysPressed, 1)) {
		SetBit(&uiKeysPressed, 1);
	}

	// Left Key: Move Left
	if (key == VK_LEFT && bIsPressed && !GetBit(&uiKeysPressed, 2)) {
		SetBit(&uiKeysPressed, 2);
	}

	// Right Key: Move Right
	if (key == VK_RIGHT && bIsPressed && !GetBit(&uiKeysPressed, 3)) {
		SetBit(&uiKeysPressed, 3);
	}

	// W Key: Look Up
	if (key == 0x57 && bIsPressed && !GetBit(&uiKeysPressed, 4)) {
		SetBit(&uiKeysPressed, 4);
	}

	// S Key: Look Down
	if (key == 0x53 && bIsPressed && !GetBit(&uiKeysPressed, 5)) {
		SetBit(&uiKeysPressed, 5);
	}

	// A Key: Look Left
	if (key == 0x41 && bIsPressed && !GetBit(&uiKeysPressed, 6)) {
		SetBit(&uiKeysPressed, 6);
	}

	// D Key: Look Right
	if (key == 0x44 && bIsPressed && !GetBit(&uiKeysPressed, 7)) {
		SetBit(&uiKeysPressed, 7);
	}
}

void CleanUp()
{
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

