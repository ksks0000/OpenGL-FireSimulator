#pragma once
#include "pch.h"
#include "CGLRenderer.h"
#include "DImage.h"
#include "Billboard.h"
#include "math.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#define DEG_TO_RAD 0.01745329251994329
#define RAD_TO_DEG 57.2957795130823208
#define DOUBLE_PI 6.28318530717958

// flagovi G_TEX_FLAG i G_ANIMATED_TEX_FLAG se podesavaju u Utility.h

// za izbor flipbook teksture
#define I 0

CGLRenderer::CGLRenderer()
{
	m_hrc = NULL;

	m_angleX = 30.0f;
	m_angleY = 0.0f;
	m_zoom = -60.0f;

	m_timestep = 0.3f; 

	textures = new FlipbookTexParams[3];
	textures[0] = FlipbookTexParams("./res/flipbook_tex_1.png", 72, 8, 9);
	textures[1] = FlipbookTexParams("./res/flipbook_tex_2.png", 15, 3, 5);
	textures[2] = FlipbookTexParams("./res/flipbook_tex_3.png", 10, 2, 5);

	m_currentFrame = 0;
	m_frameCount = textures[I].frameCount;
}

CGLRenderer::~CGLRenderer()
{
	delete[] textures;
	textures = NULL;
}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);

	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f); 

	m_woodTex.LoadTexture("./res/wood_tex_1.png");
	m_groundTex.LoadTexture("./res/ground_tex_1.png");
	if (G_TEX_FLAG && !G_ANIMATED_TEX_FLAG)
		m_fireTexTransparent.LoadTexture("./res/fire_tex_transparent_2.png"); //fire_tex_transparent_4.png
	if (G_ANIMATED_TEX_FLAG)
		m_fireFlipbookTex.LoadTexture(textures[I].filePath);
 
	m_particleSystem = ParticleSystem(8000, { 0.0f, 0.0f, 0.0f }, 1.0f);  
	m_particleSystem.Initialize();


	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	wglMakeCurrent(NULL, NULL);

	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::AddCameraAngleX(float angleInDegrees)
{
	m_angleX += angleInDegrees;
	m_angleX = fmod(m_angleX, 360.0f);
	if (m_angleX < 0.0f)
		m_angleX += 360.0f;
}

void CGLRenderer::AddCameraAngleY(float angleInDegrees)
{
	m_angleY += angleInDegrees;
	m_angleY = fmod(m_angleY, 360.0f);
	if (m_angleY < 0.0f)
		m_angleY += 360.0f;
}

void CGLRenderer::DrawAxes()
{
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);

	glEnd();
}

void CGLRenderer::DrawGround()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glColor3f(0.8f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	m_groundTex.SelectTexture();

	glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-100.0, -1.0, -100.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(100.0, -1.0, -100.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(100.0, -1.0, 100.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-100.0, -1.0, 100.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_CULL_FACE);
}

void CGLRenderer::DrawFirewood(float h, float r1, float r2, int nSeg)
{	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	float delta = 360.0 / nSeg;
	float beta = 0.0;
	double x1, y1, z1;
	double x2, y2, z2;

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	m_woodTex.SelectTexture();
	
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);

		for (int i = 0; i <= nSeg; i++, beta += delta)
		{
			glTexCoord2f(cos(beta * DEG_TO_RAD), sin(beta * DEG_TO_RAD) + 0.25f);
			glVertex3f(r1 * cos(beta * DEG_TO_RAD), 0, r1 * sin(beta * DEG_TO_RAD));
		}
	glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, h, 0.0);
		beta = 360.0;

		for (int i = 0; i <= nSeg; i++, beta -= delta)
		{
			glTexCoord2f(cos(beta * DEG_TO_RAD) + 0.5f, sin(beta * DEG_TO_RAD) + 0.25f);
			glVertex3f(r2 * cos(beta * DEG_TO_RAD), h, r2 * sin(beta * DEG_TO_RAD));
		}
	glEnd();

	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= nSeg; i++)
		{
			x1 = r1 * cos(beta * DEG_TO_RAD);
			y1 = 0;
			z1 = r1 * sin(beta * DEG_TO_RAD);

			x2 = r2 * cos(beta * DEG_TO_RAD);
			y2 = h;
			z2 = r2 * sin(beta * DEG_TO_RAD);

			glTexCoord2f(x1 / r1, 1.0f);
			glVertex3f(x1, y1, z1);

			glTexCoord2f(x2 / r2, 0.0f);
			glVertex3f(x2, y2, z2);

			beta += delta;
		}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	
	glDisable(GL_CULL_FACE);
}

void CGLRenderer::DrawCampfire(Vector3f position, float radius)
{
	glPushMatrix();
	glPushMatrix();

	float radiusFactor = radius * 3.4;
	float halfRadiusFactor = radiusFactor / 2;

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -halfRadiusFactor, 0.0f);
	DrawFirewood(radiusFactor, radius / 3, radius / 3, 6);
	glTranslatef(0.0f, halfRadiusFactor, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -halfRadiusFactor, 0.0f);
	DrawFirewood(radiusFactor, radius / 3, radius / 3, 6);

	glPopMatrix();
	glTranslatef(0.0f, 0.8f, 0.0f);

	if (G_TEX_FLAG)
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		m_fireTexTransparent.SelectTexture();
	}

	m_particleSystem.Update(m_timestep);

	if (G_TEX_FLAG)
	{
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}

	glPopMatrix();
}

void CGLRenderer::DrawCampfireAnimatedTexture(int nFlipbookRows, int nFlipbookColumns)
{
	glPushMatrix();
	glPushMatrix();

	float radiusFactor = 1.5 * 3.4;
	float halfRadiusFactor = radiusFactor / 2;

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -halfRadiusFactor, 0.0f);
	DrawFirewood(radiusFactor, 1.5 / 3, 1.5 / 3, 6);
	glTranslatef(0.0f, halfRadiusFactor, 0.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -halfRadiusFactor, 0.0f);
	DrawFirewood(radiusFactor, 1.5 / 3, 1.5 / 3, 6);

	glPopMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	m_fireFlipbookTex.SelectTexture();

	int row = m_currentFrame / nFlipbookColumns;
	int column = m_currentFrame % nFlipbookColumns;

	float offsetX = (float)column / nFlipbookColumns;
	float offsetY = (float)row / nFlipbookRows;

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(offsetX, offsetY, 0.0f);
	glMatrixMode(GL_MODELVIEW);

	if (G_TEX_FLAG)
		glDisable(GL_DEPTH_TEST);

	const float HEIGHT = 15.0f;
	const float HALF_HEIGHT = HEIGHT / 2;
	const float WIDTH = 10.0f;
	const float HALF_WIDTH = WIDTH / 2;

	float sCoord = 1.0f / nFlipbookColumns;
	float tCoord = 1.0f / nFlipbookRows;

	/*
	if (m_angleY < 45.0f || (m_angleY > 135.0f && m_angleY < 225.0f) || m_angleY > 315.0f)
	{
		//xy
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-HALF_WIDTH, HEIGHT, 0.0f);
			glTexCoord2f(sCoord, 0.0f);
			glVertex3f(HALF_WIDTH, HEIGHT, 0.0f);
			glTexCoord2f(sCoord, tCoord);
			glVertex3f(HALF_WIDTH, 0.0f, 0.0f);
			glTexCoord2f(0.0f, tCoord);
			glVertex3f(-HALF_WIDTH, 0.0f, 0.0f);

		glEnd();

		//yz
		glBegin(GL_QUADS);

			glTexCoord2f(sCoord, 0.0f);
			glVertex3f(0.0f, HEIGHT, -HALF_WIDTH);
			glTexCoord2f(sCoord, tCoord);
			glVertex3f(0.0f, 0.0f, -HALF_WIDTH);
			glTexCoord2f(0.0f, tCoord);
			glVertex3f(0.0f, 0.0f, HALF_WIDTH);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, HEIGHT, HALF_WIDTH);

		glEnd();
	}
	else
	{
		//yz
		glBegin(GL_QUADS);

			glTexCoord2f(sCoord, 0.0f);
			glVertex3f(0.0f, HEIGHT, -HALF_WIDTH);
			glTexCoord2f(sCoord, tCoord);
			glVertex3f(0.0f, 0.0f, -HALF_WIDTH);
			glTexCoord2f(0.0f, tCoord);
			glVertex3f(0.0f, 0.0f, HALF_WIDTH);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, HEIGHT, HALF_WIDTH);

		glEnd();

		//xy
		glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-HALF_WIDTH, HEIGHT, 0.0f);
			glTexCoord2f(sCoord, 0.0f);
			glVertex3f(HALF_WIDTH, HEIGHT, 0.0f);
			glTexCoord2f(sCoord, tCoord);
			glVertex3f(HALF_WIDTH, 0.0f, 0.0f);
			glTexCoord2f(0.0f, tCoord);
			glVertex3f(-HALF_WIDTH, 0.0f, 0.0f);

		glEnd();
	}
	*/

	//xy
	glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-HALF_WIDTH, HEIGHT, 0.0f);
		glTexCoord2f(sCoord, 0.0f);
		glVertex3f(HALF_WIDTH, HEIGHT, 0.0f);
		glTexCoord2f(sCoord, tCoord);
		glVertex3f(HALF_WIDTH, 0.0f, 0.0f);
		glTexCoord2f(0.0f, tCoord);
		glVertex3f(-HALF_WIDTH, 0.0f, 0.0f);

	glEnd();

	//yz
	glBegin(GL_QUADS);

		glTexCoord2f(sCoord, 0.0f);
		glVertex3f(0.0f, HEIGHT, -HALF_WIDTH);
		glTexCoord2f(sCoord, tCoord);
		glVertex3f(0.0f, 0.0f, -HALF_WIDTH);
		glTexCoord2f(0.0f, tCoord);
		glVertex3f(0.0f, 0.0f, HALF_WIDTH);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.0f, HEIGHT, HALF_WIDTH);

	glEnd();

	if (G_TEX_FLAG)
		glEnable(GL_DEPTH_TEST);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, m_zoom);
	glRotatef(m_angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_angleY, 0.0f, 1.0f, 0.0f);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	DrawAxes(); 
	
	if (G_ANIMATED_TEX_FLAG)
		DrawCampfireAnimatedTexture(textures[I].nRows, textures[I].nColumns);
	else
		DrawCampfire({ 0.0f, 0.0f, 0.0f }, 1.2f);

	glFlush();
	SwapBuffers(pDC->m_hDC);
	

	wglMakeCurrent(NULL, NULL);
}
