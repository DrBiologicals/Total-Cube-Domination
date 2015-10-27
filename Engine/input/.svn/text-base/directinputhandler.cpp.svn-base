// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   directinputhandler.cpp
//  Description :   directinputhandler.cppfor implementation of directinputhandler.h
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes
#ifdef _DEBUG

// Local Includes
#include "../../igutils.h"
#include "keyboard.h"

// This Includes
#include "directinputhandler.h"

// Static Variables

// Static Function Prototypes

// Implementation
CDirectInputHandler::CDirectInputHandler()
{

}
CDirectInputHandler::~CDirectInputHandler()
{
	delete m_pKeyboard;
	m_pKeyboard = 0;
}
/**
*
* This function Initialises the DirectInput8Create and fills in the LPDIRECTINPUT8
*
* @Author Carsten Scholz
* @_hAppInstance is the application instance
* @_Hwnd is the handle to the window
* @return Returns true if the LPDIRECTINPUT8 pointer was filled in correctly otherwise false.
* 
*/
bool 
CDirectInputHandler::Initialise(HINSTANCE _hAppInstance, HWND _Hwnd)
{
	HRESULT hr = DirectInput8Create( _hAppInstance,       // App instance handle
									 DIRECTINPUT_VERSION, // DIRECTINPUT_VERSION
									 IID_IDirectInput8,	  // IID_IDirectInput8
									 (void**)&m_pDirectInput,  // Pointer to new object
									 NULL);				  // NULL
	if(FAILED(hr))
	{
		return (false);
	}

	m_pKeyboard = new CKeyboard();
	VALIDATE(m_pKeyboard->Initialise(m_pDirectInput, _Hwnd));

	return (true);
}
/**
*
* This function calls update on CKeyboard
*
* @Author Carsten Scholz
* 
*/
void 
CDirectInputHandler::Update()
{
	m_pKeyboard->Update();
}
/**
*
* This function calls the CKeyboard IsControlTriggered to check if a button is pushed
*
* @Author Carsten Scholz
* @param _eControl Is the button which is being checked if it is being triggered
* @returns a bool, if true then the button is pressed if false the button is not pressed..
* 
*/
bool 
CDirectInputHandler::IsControlTriggered(EControl _eControl)
{
	return (m_pKeyboard->IsControlTriggered(_eControl));
}
/**
*
* This function calls the CKeyboard IsControlHeld to check if a button is pushed
*
* @Author Carsten Scholz
* @param _eControl Is the button which is being checked if it is being held
* @returns a bool, if true then the button is pressed if false the button is not pressed..
* 
*/
bool 
CDirectInputHandler::IsControlHeld(EControl _eControl)
{
	return (m_pKeyboard->IsControlHeld(_eControl));
}

#endif // _DEBUG