
// Library_Execution.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLibraryExecutionApplication:
// See Library_Execution.cpp for the implementation of this class
//

class CLibraryExecutionApplication : public CWinApp
{
public:
	CLibraryExecutionApplication();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLibraryExecutionApplication theApp;
