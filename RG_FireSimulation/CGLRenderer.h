#pragma once
#include "GL\gl.h"
#include "GL\glu.h"
#include "CGLTexture.h"
#include "ParticleSystem.h"

class CGLRenderer
{
public:
	CGLRenderer();
	~CGLRenderer();

	bool CreateGLContext(CDC* pDC);			
	void PrepareScene(CDC* pDC);			
	void Reshape(CDC* pDC, int w, int h);	
	void DrawScene(CDC* pDC);				
	void DestroyScene(CDC* pDC);	

	void CameraZoom(float zoom) { m_zoom += zoom; }
	void AddCameraAngleX(float angleInDegrees); /*{ m_angleX += angleInDegrees; }*/
	void AddCameraAngleY(float angleInDegrees); /*{ m_angleY += angleInDegrees; }*/
	GLfloat GetCameraZoom() const { return m_zoom; }
	GLfloat GetCameraAngleX() const { return m_angleX; }
	GLfloat GetCameraAngleY() const { return m_angleY; }

	void DrawAxes();
	void DrawGround();
	void DrawFirewood(float h, float r1, float r2, int nSeg);
	void DrawCampfire(Vector3f position, float radius);
	void DrawCampfireAnimatedTexture(int nFlipbookRows, int nFlipbookColumns);

	void UpdateFrame() { m_currentFrame = ++m_currentFrame % m_frameCount; }

protected:
	HGLRC	 m_hrc; 

	GLfloat m_angleX;
	GLfloat m_angleY;
	GLfloat m_zoom;

	CGLTexture m_woodTex;
	CGLTexture m_groundTex;
	CGLTexture m_fireTexTransparent;
	CGLTexture m_fireFlipbookTex;

	GLfloat m_timestep;
	ParticleSystem m_particleSystem;

	int m_currentFrame;
	int m_frameCount;
	FlipbookTexParams* textures;
};

