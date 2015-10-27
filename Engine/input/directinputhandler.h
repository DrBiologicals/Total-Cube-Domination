// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   directinputhandler.h
//  Description :   Declaration for Cdirectinputhandler
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_DIRECTINPUTHANDLER_H__
#define __IGFEB10_MODULE_DIRECTINPUTHANDLER_H__

// Library Includes
#ifdef _DEBUG
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// Local Includes
#include "input.h"

// Types

// Prototypes
class CKeyboard;

class CDirectInputHandler
{
	// Member Functions
public:
	CDirectInputHandler();
	~CDirectInputHandler();

	bool Initialise(HINSTANCE _hAppInstance, HWND _Hwnd);
	void Update();

	bool IsControlTriggered(EControl _eControl);
	bool IsControlHeld(EControl _eControl);

protected:

private:

	// Member Variables
public:

protected:
	LPDIRECTINPUT8 m_pDirectInput;
	CKeyboard* m_pKeyboard;

private:

}; 

#endif // _DEBUG
#endif // __IGFEB10_MODULE_DIRECTINPUTHANDLER_H__

