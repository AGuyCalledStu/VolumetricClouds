//--------------------------------------------------//
// Filename: Graphics.h								//
//--------------------------------------------------//

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// Includes
#include <Windows.h>

// My Class Includes
#include "D3DClass.h"
#include "Camera.h"
#include "Model.h"
#include "ColourShader.h"
#include "TextureShader.h"
#include "ParticleShader.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "ModelList.h"
#include "Frustum.h"

#include "Input.h"

// Globals
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

using namespace DirectX;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Init(int, int, HWND, Input*);
	void CleanUp();
	bool Update(int, int, float);

private:
	bool Render();
	void CameraUpdate(float);
	void ToggleControls();

	D3DClass* direct3D;
	Camera* mainCamera;
	Model* model, model2;
	ColourShader* colourShader;
	TextureShader* textureShader;
	ParticleShader* m_ParticleShader;
	ParticleSystem* m_ParticleSystem;
	Input* input;
	Text* text;
	ModelList* m_ModelList;
	Frustum* m_Frustum;

	bool isFrustumCulling;
};
#endif