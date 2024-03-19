#include "pch.h"
#include "ParticleSystem.h"


ParticleSystem::ParticleSystem()
{
	m_NumberOfParticles = 1;
	m_CenterPosition = { 0.0f, 0.0f, 0.0f };
	m_Radius = 1.0f;
	
	m_ParticlePool.resize(m_NumberOfParticles);
	m_PoolIndex = m_NumberOfParticles - 1; 
}

ParticleSystem::ParticleSystem(unsigned int numberOfParticles, Vector3f centerPosition, float radius)
{
	m_NumberOfParticles = numberOfParticles;
	m_CenterPosition = centerPosition;
	m_Radius = radius;

	m_ParticlePool.resize(m_NumberOfParticles);
	m_PoolIndex = m_NumberOfParticles - 1;
}

void ParticleSystem::Initialize()
{

	for (unsigned int i = 0; i < m_NumberOfParticles/2 ; i++)
	{
		props.speed = {
			(Utility::GetRandomFloat() - 0.5f) * /*0.6f*/ m_Radius / 3,
			(Utility::GetRandomFloat() - 0.01f) * 2.0f,
			(Utility::GetRandomFloat() - 0.5f) * /*0.6f*/ m_Radius / 3
		};
		props.acceleration = {
			(Utility::GetRandomFloat() - 0.5f) * 0.2f,
			Utility::GetRandomFloat() * 0.5f,
			(Utility::GetRandomFloat() - 0.5f) * 0.2f
		};
		props.sizeBegin = Utility::GetRandomFloat() * m_NumberOfParticles / 8000;
		props.sizeEnd = Utility::GetRandomFloat() * 0.3f * m_NumberOfParticles / 8000;
		props.lifetime = Utility::GetRandomFloat() * 5.0f;

		ActivateParticle(props);
	}
}

void ParticleSystem::ActivateParticle(ParticleProps& particleProps)
{
	Billboard& particle = m_ParticlePool[m_PoolIndex];

	bool coordinatesInCircle = false;
	float r2 = m_Radius * m_Radius;
	float x, y, z;

	y = (Utility::GetRandomFloat() + 0.01f) * 0.4f * m_Radius;

	while (!coordinatesInCircle)
	{
		x = (Utility::GetRandomFloat() - 0.5f) * 2 * m_Radius;
		z = (Utility::GetRandomFloat() - 0.5f) * 2 * m_Radius;
		if (x * x / r2 + z * z / r2 <= 1)
			coordinatesInCircle = true;
	}
	
	particleProps.startingPosition = {
		m_CenterPosition.x + x,
		m_CenterPosition.y + y,  
		m_CenterPosition.z + z 
	};

	particle.SetParticleProps(particleProps);
	particle.m_Active = true;

	m_PoolIndex = --m_PoolIndex % m_NumberOfParticles;
}

void ParticleSystem::Render(float timestep)
{
	for (unsigned int i = 0; i < m_NumberOfParticles; i++)
	{
		Billboard& particle = m_ParticlePool[i];
		if (!particle.m_Active) continue;

		particle.RednerOnTime(timestep);
	}
}

void ParticleSystem::Update(float m_timestep)
{
	Render(m_timestep);

	for (unsigned int i = 0; i < 50; i++)
	{
		props.speed = {
			(Utility::GetRandomFloat() - 0.5f) * 0.6f,
			(Utility::GetRandomFloat() - 0.01f) * 2.0f,
			(Utility::GetRandomFloat() - 0.5f) * 0.6f
		};
		props.acceleration = {
			(Utility::GetRandomFloat() - 0.5f) * 0.2f,
			Utility::GetRandomFloat() * 0.5f + 0.2f,
			(Utility::GetRandomFloat() - 0.5f) * 0.2f
		};
		props.sizeBegin = Utility::GetRandomFloat();
		props.sizeEnd = Utility::GetRandomFloat() * 0.3;
		props.lifetime = Utility::GetRandomFloat() * 5.0f;

		ActivateParticle(props);
	}
}
