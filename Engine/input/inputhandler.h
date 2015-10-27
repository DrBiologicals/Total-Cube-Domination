// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   inputhandler.h
//  Description :   Declaration for Cinputhandler
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_INPUTHANDLER_H__
#define __IGFEB10_MODULE_INPUTHANDLER_H__

// Library Includes

// Local Includes
#include "input.h"

// Types

// Prototypes
#ifdef _DEBUG
class CDirectInputHandler;
#endif // _DEBUG

class CXInputHandler;

class CInputHandler
{
	// Member Functions
public:
	static CInputHandler& GetInstance();
	static void DestroyInstance();

	bool Initialise(HINSTANCE _hAppInstance, HWND _hWnd);
	void Update();

	bool IsControlTriggered(EControl _eControl, uint32 _uiController = -1);
	bool IsControlHeld(EControl _eControl, uint32 _uiController = -1);

	float32 GetControlMagnitude(EControl _eControl, uint32 _uiController = -1);

	bool IsControllerConnected(uint32 _uiController = -1);

	uint32 GetMaxNumControllers();

protected:

private:
	CInputHandler();
	CInputHandler(const CInputHandler& _kr);
	~CInputHandler();
	CInputHandler& operator=(const CInputHandler& _kr);

	// Member Variables
public:

protected:
	HINSTANCE m_AppInstance;
	HWND m_hWnd;

#ifdef _DEBUG
	CDirectInputHandler* m_pDirectInput;
#endif // _DEBUG

	CXInputHandler* m_pXInputHandler;

	static CInputHandler* s_pInputHandler;

private:

}; 

#endif // __IGFEB10_MODULE_INPUTHANDLER_H__

