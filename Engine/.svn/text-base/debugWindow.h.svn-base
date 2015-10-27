// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   debugwindow.h
//  Description :   Declaration for Cdebugwindow
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//
#ifdef _DEBUG

#ifndef __IGFEB10_MODULE_DEBUGWINDOW_H__
#define __IGFEB10_MODULE_DEBUGWINDOW_H__

// Library Includes
#include <windows.h>
#include <windowsx.h>
// Local Includes
#include "../resource.h"
// Types

// Prototypes


class CDebugWindow
{
	// Member Functions
public:
	CDebugWindow();
	~CDebugWindow();

	void OpenDebugWindow();
	bool IsWindowOpen();
	void CloseWindow();

	void SetWindowHandle(HWND _hwnd);
	bool HasAWindowHandle();

	void ChangeValues(float32 _fMove, float32 _fPlasma, float32 _fEMP, 
		float32 _fCharge, float32 _fRate, float32 _fMax);

protected:

private:

	// Member Variables
public:

protected:
	bool m_bIsOpen;
	HWND m_hDebugWindow;

private:

}; 

#endif // __IGFEB10_MODULE_DEBUGWINDOW_H__

#endif //_DEBUG