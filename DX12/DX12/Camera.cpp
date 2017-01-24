//--------------------------------------------------//
// Filename: Camera.cpp								//
//--------------------------------------------------//

#include "Camera.h"

Camera::Camera()
{
	xPosition = 0.0f;
	yPosition = 0.0f;
	zPosition = 0.0f;

	xRotation = 0.0f;
	yRotation = 0.0f;
	zRotation = 0.0f;

	sensitivity = 0.05f;
}

Camera::Camera(const Camera& other)
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	xPosition = x;
	yPosition = y;
	zPosition = z;
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	xRotation = x;
	yRotation = y;
	zRotation = z;
	return;
}

XMFLOAT3 Camera::GetPosition()
{
	return XMFLOAT3(xPosition, yPosition, zPosition);
}

XMFLOAT3 Camera::GetRotation()
{
	return XMFLOAT3(xRotation, yRotation, zRotation);
}

void Camera::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	// Setup the up vector
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load the up vector into an XMVECTOR structure
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world
	position = XMFLOAT3(xPosition, yPosition, zPosition);

	// Load the position vector into an XMVECTOR structure
	positionVector = XMLoadFloat3(&position);

	// Setup the default camera look at
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into	an XMVECTOR structure
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = xRotation * 0.0174532925f;
	yaw = yRotation * 0.0174532925f;
	roll = zRotation * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}

// TODO - Figure out if this is correct
void Camera::GetViewMatrix(XMMATRIX& viewMatrix_)
{
	viewMatrix_ = viewMatrix;
	return;
}

void Camera::UpdateFrameTime(float frameTime_)
{
	frameTime = frameTime_;
}

void Camera::MoveForward()
{
	float radians;

	// Update the forward movement based on the frame time
	speed = frameTime * sensitivity;

	// Convert degrees to radians.
	radians = yRotation * 0.0174532925f;

	// Update the position.
	xPosition += sinf(radians) * speed;
	zPosition += cosf(radians) * speed;
}


void Camera::MoveBackward()
{
	float radians;

	// Update the backward movement based on the frame time
	speed = frameTime * sensitivity;

	// Convert degrees to radians.
	radians = yRotation * 0.0174532925f;

	// Update the position.
	xPosition -= sinf(radians) * speed;
	zPosition -= cosf(radians) * speed;
}


void Camera::MoveUpward()
{
	// Update the upward movement based on the frame time
	speed = frameTime * sensitivity;

	// Update the height position.
	yPosition += speed;
}


void Camera::MoveDownward()
{
	// Update the downward movement based on the frame time
	speed = frameTime * sensitivity;

	// Update the height position.
	yPosition -= speed;
}


void Camera::TurnLeft()
{
	// Update the left turn movement based on the frame time 
	speed = frameTime * sensitivity;

	// Update the rotation.
	yRotation -= speed;

	// Keep the rotation in the 0 to 360 range.
	if (yRotation < 0.0f)
	{
		yRotation += 360.0f;
	}
}


void Camera::TurnRight()
{
	// Update the right turn movement based on the frame time
	speed = frameTime * sensitivity;

	// Update the rotation.
	yRotation += speed;

	// Keep the rotation in the 0 to 360 range.
	if (yRotation > 360.0f)
	{
		yRotation -= 360.0f;
	}

}


void Camera::TurnUp()
{
	// Update the upward rotation movement based on the frame time
	speed = frameTime * sensitivity;

	// Update the rotation.
	xRotation -= speed;

	// Keep the rotation maximum 90 degrees.
	if (xRotation > 90.0f)
	{
		xRotation = 90.0f;
	}
}


void Camera::TurnDown()
{
	// Update the downward rotation movement based on the frame time
	speed = frameTime * sensitivity;

	// Update the rotation.
	xRotation += speed;

	// Keep the rotation maximum 90 degrees.
	if (xRotation < -90.0f)
	{
		xRotation = -90.0f;
	}
}

void Camera::StrafeRight()
{
	float radians;

	// Update the forward movement based on the frame time
	speed = frameTime * sensitivity;

	// Convert degrees to radians.
	radians = yRotation * 0.0174532925f;

	// Update the position.
	zPosition -= sinf(radians) * speed;
	xPosition += cosf(radians) * speed;

}

void Camera::StrafeLeft()
{
	float radians;

	// Update the forward movement based on the frame time
	speed = frameTime * sensitivity;

	// Convert degrees to radians.
	radians = yRotation * 0.0174532925f;

	// Update the position.
	zPosition += sinf(radians) * speed;
	xPosition -= cosf(radians) * speed;
}