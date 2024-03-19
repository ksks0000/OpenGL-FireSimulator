#pragma once
#include "GL\gl.h"
#include "GL\glu.h"
#include "Billboard.h"
#include <vector>

class ParticleSystem
{
public:
	ParticleSystem();
	ParticleSystem(unsigned int numberOfParticles, Vector3f centerPosition, float radius = 1.0f);

	void Initialize();
	void ActivateParticle(ParticleProps& particleProps);
	void Render(float timestep);
	void Update(float timestep);

protected:
	unsigned int m_NumberOfParticles;
	Vector3f m_CenterPosition;
	float m_Radius;

	std::vector<Billboard> m_ParticlePool;
	unsigned int m_PoolIndex; 
	ParticleProps props;
	//float* m_VertexArray;
};

