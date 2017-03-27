#include "Frustum.h"



Frustum::Frustum()
{
}

Frustum::Frustum(const Frustum& other)
{
}

Frustum::~Frustum()
{
}

void Frustum::ConstructFrustum(float screenDepth, XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	float zMinimum, r;
	XMMATRIX matrix;

	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	//D3DXMatrixMultiply(&matrix, &viewMatrix, &projectionMatrix);

	matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);
	
	// Calculate near plane of frustum.
	plane[0].x = matrix._14 + matrix._13;
	plane[0].y = matrix._24 + matrix._23;
	plane[0].z = matrix._34 + matrix._33;
	plane[0].w = matrix._44 + matrix._43;
	XMStoreFloat4(&plane[0], XMPlaneNormalize(XMLoadFloat4(&plane[0])));

	// Calculate far plane of frustum.
	plane[1].x = matrix._14 - matrix._13;
	plane[1].y = matrix._24 - matrix._23;
	plane[1].z = matrix._34 - matrix._33;
	plane[1].w = matrix._44 - matrix._43;
	XMStoreFloat4(&plane[1], XMPlaneNormalize(XMLoadFloat4(&plane[1])));

	// Calculate left plane of frustum.
	plane[2].x = matrix._14 + matrix._11;
	plane[2].y = matrix._24 + matrix._21;
	plane[2].z = matrix._34 + matrix._31;
	plane[2].w = matrix._44 + matrix._41;
	XMStoreFloat4(&plane[2], XMPlaneNormalize(XMLoadFloat4(&plane[2])));

	// Calculate right plane of frustum.
	plane[3].x = matrix._14 - matrix._11;
	plane[3].y = matrix._24 - matrix._21;
	plane[3].z = matrix._34 - matrix._31;
	plane[3].w = matrix._44 - matrix._41;
	XMStoreFloat4(&plane[3], XMPlaneNormalize(XMLoadFloat4(&plane[3])));

	// Calculate top plane of frustum.
	plane[4].x = matrix._14 - matrix._12;
	plane[4].y = matrix._24 - matrix._22;
	plane[4].z = matrix._34 - matrix._32;
	plane[4].w = matrix._44 - matrix._42;
	XMStoreFloat4(&plane[4], XMPlaneNormalize(XMLoadFloat4(&plane[4])));

	// Calculate bottom plane of frustum.
	plane[5].x = matrix._14 + matrix._12;
	plane[5].y = matrix._24 + matrix._22;
	plane[5].z = matrix._34 + matrix._32;
	plane[5].w = matrix._44 + matrix._42;
	XMStoreFloat4(&plane[5], XMPlaneNormalize(XMLoadFloat4(&plane[5])));
}

bool Frustum::CheckPoint(float x, float y, float z)
{
	// Check if the point is inside all six planes of the view frustum.
	for (int i = 0; i<6; i++)
	{
		XMVECTOR vector = XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4(x, y, z, 0.0f)));

		if (vector.vector4_f32[0] < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	// Check if any one point of the cube is in the view frustum.
	for (int i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter - radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter - radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter - radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - radius), (yCenter + radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + radius), (yCenter + radius), (zCenter + radius), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	// Check if the radius of the sphere is inside the view frustum.
	for (int i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4(xCenter, yCenter, zCenter, 1.0f))).vector4_f32[0] < -radius)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (int i = 0; i<6; i++)
	{
		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter - xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		if (XMPlaneDotCoord(XMLoadFloat4(&plane[i]), XMLoadFloat4(&XMFLOAT4((xCenter + xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))).vector4_f32[0] >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}