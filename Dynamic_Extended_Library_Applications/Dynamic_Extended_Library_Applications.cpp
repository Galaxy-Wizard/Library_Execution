// Dynamic_Extended_Library_Applications.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Dynamic_Extended_Library_Applications.h"
#include "Dynamic_Extended_Library_Execution_Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef WCHAR * PWCHAR;

typedef PWCHAR(FAR WINAPI *FAR_FUNCTION_RESULT_POINTER)(PWCHAR);

#define LIBRARY_EXPORT __declspec(dllexport)


//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CDynamicExtendedLibraryApplicationsApp

BEGIN_MESSAGE_MAP(CDynamicExtendedLibraryApplicationsApp, CWinApp)
END_MESSAGE_MAP()


// CDynamicExtendedLibraryApplicationsApp construction

CDynamicExtendedLibraryApplicationsApp::CDynamicExtendedLibraryApplicationsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDynamicExtendedLibraryApplicationsApp object

CDynamicExtendedLibraryApplicationsApp theApp;

const GUID CDECL _tlid = {0xd2fa8109,0x3b08,0x4c8c,{0x93,0x2e,0x70,0xe7,0x76,0x33,0x57,0x84}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CDynamicExtendedLibraryApplicationsApp initialization

BOOL CDynamicExtendedLibraryApplicationsApp::InitInstance()
{
	AfxOleInit();
	CWinApp::InitInstance();

	// Register all OLE server (factories) as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();

	return TRUE;
}

// DllGetClassObject - Returns class factory

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - Allows COM to unload DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}



typedef WCHAR * PWCHAR;

typedef PWCHAR(FAR WINAPI *FAR_FUNCTION_RESULT_POINTER)(PWCHAR);

#define LIBRARY_EXPORT __declspec(dllexport)


const WCHAR ResultDone[] = L"Done.";
const WCHAR ResultNotDone[] = L"Not done.";

const size_t ResultDoneLength = wcslen(ResultDone);
const size_t ResultNotDoneLength = wcslen(ResultNotDone);

const WCHAR PieceNamesFigureSymbols[2][6]{
	{wchar_t(0x2659), wchar_t(0x2658), wchar_t(0x2657), wchar_t(0x2656), wchar_t(0x2655), wchar_t(0x2654)},
	{wchar_t(0x265F), wchar_t(0x265E), wchar_t(0x265D), wchar_t(0x265C), wchar_t(0x265B), wchar_t(0x265A)},
};


EXTERN_C_START
PWCHAR LIBRARY_EXPORT WINAPI Main(PWCHAR p)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WCHAR *w = p;

	const size_t result_size = 100;
	WCHAR *result = new WCHAR[result_size];
	if (result != nullptr)
	{
		memset(result, 0, result_size * sizeof(WCHAR));

		//	TO DO: add your application code here.
		CLibraryExecutionDialog LibraryExecutionDialogVariable;

		if (LibraryExecutionDialogVariable.DoModal() == IDOK)
		{
			wcscpy_s(result, result_size, ResultDone);
		}
		else
		{
			wcscpy_s(result, result_size, ResultNotDone);
		}
	}

	return result;
}
EXTERN_C_END

EXTERN_C_START
PWCHAR LIBRARY_EXPORT WINAPI GetChessFigures(PWCHAR p)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WCHAR *w = p;

	const size_t result_size = 100;
	WCHAR *result = new WCHAR[result_size];
	if (result != nullptr)
	{
		memset(result, 0, result_size * sizeof(WCHAR));

		for (int color = 0; color < 2; color++)
		{
			for (int symbol = 0; symbol < 6; symbol++)
			{
				result[color * 6 + symbol] = PieceNamesFigureSymbols[color][symbol];
			}
		}
	}

	return result;
}
EXTERN_C_END

