#pragma once

#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

class DImage
{
public:
	DImage(void);
	DImage(CBitmap& bmp);
	virtual ~DImage(void);

	bool	Load(CString fileName); 
	bool	Save(CString fileName); 
	void	Draw(CDC* pDC, CRect rcImg, CRect rcDC); 

	int		Width() { return m_nWidth; }	
	int		Height() { return m_nHeight; } 
	int		BPP() { return m_nBPP; }						

	bool	isValid() { return m_pBuf != NULL; }

	// Direktne izmene
	unsigned char* GetDIBBits() { return m_pBuf; } 
	void	Update();		

protected:
	void Flip();
	void Convert(int oldBPP, int newBPP);
	void Save(CFile& file);
	int m_nWidth;
	int m_nHeight;
	int m_nBPP;
	int GetScanlineWidth() { return ((m_nWidth * m_nBPP + 3) / 4) * 4; }
	unsigned char* m_pBuf;
	CBitmap* m_pBmp;
};


