// Dynamic_Extended_Library_Applications.h : main header file for the Dynamic_Extended_Library_Applications DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDynamicExtendedLibraryApplicationsApp
// See Dynamic_Extended_Library_Applications.cpp for the implementation of this class
//

class CDynamicExtendedLibraryApplicationsApp : public CWinApp
{
public:
	CDynamicExtendedLibraryApplicationsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
