#include "pch.h"
#include "Billboard.h"

#define DOUBLEPI 6.28318530717

Billboard::Billboard()
{
	m_Position = { 0.0f, 0.0f, 0.0f };
	m_StartPosition = { 0.0f, 0.0f, 0.0f };
	m_Rotation = 0.0f;
	m_Speed = { 0.0f, 0.0f, 0.0f };
	m_StartSpeed = { 0.0f, 0.0f, 0.0f };
	m_Acceleration = { 0.0f, 0.0f, 0.0f };
	m_ColorBegin = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_ColorEnd = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_Color = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_SizeBegin = 2.0f;
	m_SizeEnd = 0.0f;
	m_Size = 2.0f;
	m_Lifetime = 1.0f;
	m_LifeRemaining = 0.0f;
	m_Active = false;
}

Billboard::Billboard(ParticleProps& particleProps)
{
	SetParticleProps(particleProps);
}

void Billboard::SetParticleProps(ParticleProps& particleProps)
{
	m_Position = particleProps.startingPosition;
	m_StartPosition = particleProps.startingPosition;
	m_Rotation = Utility::GetRandomFloat() * DOUBLEPI;

	m_Speed = particleProps.speed;
	m_StartSpeed = particleProps.speed;
	m_Acceleration = particleProps.acceleration;

	m_ColorBegin = particleProps.colorBegin;
	m_ColorEnd = particleProps.colorEnd;
	m_Color = particleProps.colorBegin;

	m_SizeBegin = particleProps.sizeBegin;
	m_SizeEnd = particleProps.sizeEnd;
	m_Size = particleProps.sizeBegin;

	m_Lifetime = particleProps.lifetime;
	m_LifeRemaining = particleProps.lifetime;
	m_Active = false;
}

void Billboard::DrawBillboard(GLenum mode = GL_TRIANGLES)
{
	glPushMatrix();

	const float HALF_SIZE = m_Size / 2.0f;

	if (G_TEX_FLAG)
		glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	else
	{
		if (Utility::CalculateDistance(m_Position, m_StartPosition) < 1.0f)
			if (Utility::GetRandomFloat() > 0.35f)
				glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
			else
				glColor4f(1.0f, 0.55f, 0.0f, m_Color.w);
		else
			if (Utility::GetRandomFloat() > 0.9f)
				glColor4f(1.0f, 0.25f, 0.0f, m_Color.w);
			else
				glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	if (mode == GL_QUADS)
	{
		//xy
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(m_Position.x - HALF_SIZE, m_Position.y + HALF_SIZE, m_Position.z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(m_Position.x + HALF_SIZE, m_Position.y + HALF_SIZE, m_Position.z);
			/*if (Utility::GetRandomFloat() > 0.6f)
				glColor4f(1.0f, 0.5f, 0.0f, m_Color.w);*/
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_Position.x + HALF_SIZE, m_Position.y - HALF_SIZE, m_Position.z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_Position.x - HALF_SIZE, m_Position.y - HALF_SIZE, m_Position.z);

		glEnd();

		glTranslatef(m_Position.x, m_Position.y, m_Position.z);
		glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);

		//yz
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(m_Position.x, m_Position.y + HALF_SIZE, m_Position.z - HALF_SIZE);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(m_Position.x, m_Position.y - HALF_SIZE, m_Position.z - HALF_SIZE);
			/*if (Utility::GetRandomFloat() > 0.6f)
				glColor4f(1.0f, 0.5f, 0.0f, m_Color.w);*/
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_Position.x, m_Position.y - HALF_SIZE, m_Position.z + HALF_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_Position.x, m_Position.y + HALF_SIZE, m_Position.z + HALF_SIZE);

		glEnd();

		/*
		glTranslatef(m_Position.x, m_Position.y, m_Position.z);
		glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);

		//xz
		glBegin(GL_QUADS);

			glVertex3f(m_Position.x - HALF_SIZE, m_Position.y, m_Position.z - HALF_SIZE);
			glVertex3f(m_Position.x + HALF_SIZE, m_Position.y, m_Position.z - HALF_SIZE);
			glVertex3f(m_Position.x + HALF_SIZE, m_Position.y, m_Position.z + HALF_SIZE);
			glVertex3f(m_Position.x - HALF_SIZE, m_Position.y, m_Position.z + HALF_SIZE);

		glEnd();
		*/
	}
	else
	{
		//xy
		glBegin(GL_TRIANGLES);

			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(m_Position.x, m_Position.y + HALF_SIZE, m_Position.z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_Position.x + HALF_SIZE, m_Position.y - HALF_SIZE, m_Position.z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_Position.x - HALF_SIZE, m_Position.y - HALF_SIZE, m_Position.z);

		glEnd();

		glTranslatef(m_Position.x, m_Position.y, m_Position.z);
		glRotatef(90, 1.0, 0.0, 0.0);
		glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);

		//yz
		glBegin(GL_TRIANGLES);

			glTexCoord2f(0.5f, 0.0f); 
			glVertex3f(m_Position.x, m_Position.y + HALF_SIZE, m_Position.z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(m_Position.x, m_Position.y - HALF_SIZE, m_Position.z + HALF_SIZE);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(m_Position.x, m_Position.y - HALF_SIZE, m_Position.z - HALF_SIZE);

		glEnd();
	}

	glPopMatrix();
}

void Billboard::RednerOnTime(float timestep)
{
	glPushMatrix();

	/*glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	glRotatef(m_Rotation, 0.0f, 1.0f, 0.0f);
	glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);*/

	CalculateProps(timestep);

	glScalef(m_Size, m_Size * 1.5f, m_Size);
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);

	DrawBillboard(/*GL_QUADS*/);

	glPopMatrix();
}

void Billboard::CalculateProps(float timestep = 0.4f)
{
	if (m_LifeRemaining <= 0.0f)
	{
		m_LifeRemaining = m_Lifetime;
		m_Position = m_StartPosition;
		m_Speed = m_StartSpeed;
	}
	else
	{
		float life = m_LifeRemaining / m_Lifetime; //[0-1]

		float halft2 = timestep * timestep / 2;

		//m_Speed = m_Speed + m_Acceleration;

		m_Position = m_Position + m_Speed * timestep + m_Acceleration * halft2;
		m_Rotation += 5.1f * timestep;

		m_Color = Utility::VectorLinearInterpolation(m_ColorEnd, m_ColorBegin, life);
		m_Color.w *= (life * G_TEX_FLAG ? 0.4f : 0.6f);

		m_Size = Utility::FloatLinearInterpolation(m_SizeEnd, m_SizeBegin, life);
	}

	m_LifeRemaining -= timestep;



}
