#include "pch.h"
#include "CGLTexture.h"
#include "DImage.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#include <GL\gl.h>
#include <GL\glu.h>

CGLTexture::CGLTexture()
	: m_ID(0)
{}

UINT CGLTexture::LoadTexture(char* fileName)
{
	DImage img;
	img.Load(CString(fileName));
	PrepareTexturing();

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	BYTE* imgBits = img.GetDIBBits();
	int totalBits = img.Height() * img.Width() * img.BPP();

	//for (int i = 0; i < totalBits; i += 4)
	//{
	//	BYTE tmp = imgBits[i];
	//	imgBits[i] = imgBits[i + 2];
	//	imgBits[i + 2] = tmp;
	//}

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, img.Width(), img.Height(),
		GL_RGBA, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return m_ID;
}

CGLTexture::~CGLTexture()
{
	glDeleteTextures(1, &m_ID);
	m_ID = 0;
}

void CGLTexture::SelectTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void CGLTexture::PrepareTexturing(bool isLightningEnabled)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (isLightningEnabled)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

