#include "ModelList.h"



ModelList::ModelList()
{
	modelInfoList = NULL;
}

ModelList::ModelList(const ModelList& other)
{
}

ModelList::~ModelList()
{
}

bool ModelList::Init(int numModels)
{
	int i;
	float red, green, blue;

	// Store the number of models.
	modelCount = numModels;

	// Create a list array of the model information.
	modelInfoList = new ModelInfoType[modelCount];
	if (!modelInfoList)
	{
		return false;
	}

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	// Go through all the models and randomly generate the model color and position.
	for (i = 0; i<modelCount; i++)
	{
		// Generate a random color for the model.
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		modelInfoList[i].colour = XMFLOAT4(red, green, blue, 1.0f);

		// Generate a random position in front of the viewer for the mode.
		modelInfoList[i].positionX = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		modelInfoList[i].positionY = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		modelInfoList[i].positionZ = ((((float)rand() - (float)rand()) / RAND_MAX) * 10.0f) + 5.0f;
	}

	return true;
}

void ModelList::CleanUp()
{
	// Release the model information list.
	if (modelInfoList)
	{
		delete[] modelInfoList;
		modelInfoList = 0;
	}
}

int ModelList::GetModelCount()
{
	return modelCount;
}

void ModelList::GetData(int index, float& positionX, float& positionY, float& positionZ, XMFLOAT4& colour)
{
	positionX = modelInfoList[index].positionX;
	positionY = modelInfoList[index].positionY;
	positionZ = modelInfoList[index].positionZ;

	colour = modelInfoList[index].colour;
}
