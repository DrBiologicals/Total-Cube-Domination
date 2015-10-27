// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   keyboard.h
//  Description :   Declaration for Ckeyboard
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_KEYBOARD_H__
#define __IGFEB10_MODULE_KEYBOARD_H__

// Library Includes
#ifdef _DEBUG
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

// Local Includes
#include "input.h"

// Types

// Prototypes
class CKeyboard
{
	// Member Functions
public:
	CKeyboard();
	~CKeyboard();

	bool Initialise(LPDIRECTINPUT8 _pDirectInput, HWND _Hwnd);
	bool Update();

	bool IsControlTriggered(EControl _eControl);
	bool IsControlHeld(EControl _eControl);

protected:

private:

	// Member Variables
public:
	LPDIRECTINPUTDEVICE8 m_pDirectInputDevice;

	char m_acBufferA[256];
	char m_acBufferB[256];
	char* m_pActiveBuffer;
	char* m_pInactiveBuffer;

protected:

private:

}; 

#endif // _DEBUG
#endif // __IGFEB10_MODULE_KEYBOARD_H__

