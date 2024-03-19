#pragma once
#include "GL\gl.h"
#include "GL\glu.h"
#include "Utility.h"

struct ParticleProps
{
	Vector3f startingPosition = { 0.0f, 0.0f, 0.0f };
	Vector3f speed  = {
		(Utility::GetRandomFloat() - 0.5f) * 1.25f,
		(Utility::GetRandomFloat() - 0.05f) * 2.0f,
		(Utility::GetRandomFloat() - 0.5f) * 1.25f 
	};
	Vector3f acceleration = { 
		Utility::GetRandomFloat(),
		Utility::GetRandomFloat() * 1.3f,
		Utility::GetRandomFloat() 
	};
	Vector4f colorBegin = { 1.0f, 1.0f, 0.0f, 1.0f };
	Vector4f colorEnd = { 1.0f, 0.0f, 0.0f, 1.0f };
	float sizeBegin = 1.0f;
	float sizeEnd = 0.4f;
	float lifetime = 5.0f;
};

class Billboard
{
public: 
	Billboard();
	Billboard(ParticleProps& particleProps);

	void SetParticleProps(ParticleProps& particleProps);

	void DrawBillboard(GLenum mode);
	void RednerOnTime(float timestep);

	bool m_Active;

protected:
	void CalculateProps(float timestep);

	Vector3f m_Position, m_StartPosition;
	Vector3f m_Speed, m_StartSpeed, m_Acceleration;
	Vector4f m_ColorBegin, m_ColorEnd, m_Color;
	float m_Rotation;
	float m_SizeBegin, m_SizeEnd, m_Size;
	float m_Lifetime;
	float m_LifeRemaining;
};

