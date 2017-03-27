#ifndef _MODELLIST_H_
#define _MODELLIST_H_

// Includes
#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>

// Namespaces
using namespace DirectX;

class ModelList
{
private:
	struct ModelInfoType
	{
		XMFLOAT4 colour;
		float positionX, positionY, positionZ;
	};

public:
	ModelList();
	ModelList(const ModelList&);
	~ModelList();

	bool Init(int);
	void CleanUp();

	int GetModelCount();
	void GetData(int, float&, float&, float&, XMFLOAT4&);

private:
	int modelCount;
	ModelInfoType* modelInfoList;
};
#endif