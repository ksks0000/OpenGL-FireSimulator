#pragma once
class CGLTexture
{
protected:
	UINT m_ID;
public:
	CGLTexture();
	~CGLTexture();

	UINT GetTextureID() { return m_ID; }
	UINT LoadTexture(char* fileName);

	void SelectTexture();
	static void PrepareTexturing(bool isLightnihEnabled = true);
};

