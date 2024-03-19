
// RG_FireSimulation.h : main header file for the RG_FireSimulation application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGFireSimulationApp:
// See RG_FireSimulation.cpp for the implementation of this class
//

class CRGFireSimulationApp : public CWinApp
{
public:
	CRGFireSimulationApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGFireSimulationApp theApp;
