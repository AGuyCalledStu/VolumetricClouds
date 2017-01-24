//--------------------------------------------------//
// Filename: ShaderManager.h						//
//--------------------------------------------------//

#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

// My class includes (include any shader classes needed)
#include "D3DClass.h"

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Init(ID3D11Device*, HWND);
	void Shutdown();

	// Create a render function for each shader used

private:
	// Create a pointer object for each shader used
};
#endif