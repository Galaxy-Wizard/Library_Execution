// Dynamic_Library_Applications.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "MainApplicationDialog.h"


typedef WCHAR * PWCHAR;

typedef PWCHAR(FAR WINAPI *FAR_FUNCTION_RESULT_POINTER)(PWCHAR);

#define LIBRARY_EXPORT __declspec(dllexport)


EXTERN_C_START
PWCHAR LIBRARY_EXPORT WINAPI Main(PWCHAR p);
PWCHAR LIBRARY_EXPORT WINAPI GetChessFigures(PWCHAR p);
EXTERN_C_END


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
	WCHAR *w = p;

	const size_t result_size = 100;
	WCHAR *result = new WCHAR[result_size];
	if (result != nullptr)
	{
		memset(result, 0, result_size * sizeof(WCHAR));

		//	TO DO: add your application code here.
		MainApplicationDialog MainApplicationDialogVariable;

		if (MainApplicationDialogVariable.DoModal() == ID_BUTTON_DONE)
		{
			wcscpy_s(result, result_size, ResultDone);
		}
		else
		{
		//	wcscpy_s(result, result_size, ResultNotDone);
		}
	}

	return 0;
}
EXTERN_C_END

EXTERN_C_START
PWCHAR LIBRARY_EXPORT WINAPI GetChessFigures(PWCHAR p)
{
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

