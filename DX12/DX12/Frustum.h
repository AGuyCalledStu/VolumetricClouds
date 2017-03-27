#define _XM_NO_INTRINSICS_

#ifndef _FRUSTUM_H_
#define _FRUSTUM_H_

// Includes
#include <DirectXMath.h>

// Namespaces
using namespace DirectX;

class Frustum
{
public:
	Frustum();
	Frustum(const Frustum&);
	~Frustum();

	void ConstructFrustum(float, XMMATRIX, XMMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	XMFLOAT4 plane[6];	
};
#endif