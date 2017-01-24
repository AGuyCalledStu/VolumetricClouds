//--------------------------------------------------//
// Filename: ParticleSystem.h						//
//--------------------------------------------------//

#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

// Includes
#include <d3d11.h>
#include <DirectXMath.h>

// My Class Includes
#include "Texture.h"

// Namespaces
using namespace DirectX;

class ParticleSystem
{
private:
	struct Particle
	{
		float positionX, positionY, positionZ;
		float red, green, blue;
		float velocity;
		bool active;
	};

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 colour;
	};

public:
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	~ParticleSystem();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, WCHAR*);
	void Shutdown();
	bool Frame(float, ID3D11DeviceContext*);
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();

private:
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, WCHAR*);
	void ReleaseTexture();

	bool InitializeParticleSystem();
	void ShutdownParticleSystem();

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	void EmitParticles(float);
	void UpdateParticles(float);
	void KillParticles();

	bool UpdateBuffers(ID3D11DeviceContext*);

	void RenderBuffers(ID3D11DeviceContext*);

	// RasterTek comment
	// The following private class variables are the ones used for the particle properties
	// They define how the particle system will work and changing each of them has a unique effect on how the particle system will react
	// If you plan to add more functionality to the particle system you would add it here by using additional variables for modifying the particles

	float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	float m_particleVelocity, m_particleVelocityVariation;
	float m_particleSize, m_particlesPerSecond;
	int m_maxParticles;

	// We require a count and an accumulated time variable for timing the emission of particles
	int m_currentParticleCount;
	float m_accumulatedTime;

	// We use a single texture for all the particles in this tutorial
	Texture* m_Texture;

	// The particle system is an array of particles made up from the Particle structure
	Particle* m_particleList;

	// The particle system is rendered using a single vertex and index buffer. Note that the vertex buffer will be dynamic
	int m_vertexCount, m_indexCount;
	Vertex* m_vertices;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
};
#endif