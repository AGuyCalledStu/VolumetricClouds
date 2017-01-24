//--------------------------------------------------//
// Filename: Camera.h								//
//--------------------------------------------------//

#ifndef _CAMERA_H_
#define _CAMERA_H_

// Includes
#include <DirectXMath.h>

// Namespaces
using namespace DirectX;

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	void UpdateFrameTime(float frameTime_);

	void MoveForward();
	void MoveBackward();
	void MoveUpward();
	void MoveDownward();
	void TurnLeft();
	void TurnRight();
	void TurnUp();
	void TurnDown();
	void StrafeRight();
	void StrafeLeft();

private:
	float xPosition, yPosition, zPosition;
	float xRotation, yRotation, zRotation;
	XMMATRIX viewMatrix;
	float speed, frameTime, sensitivity;
};
#endif