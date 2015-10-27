// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   inputhandler.cpp
//  Description :   inputhandler.cppfor implementation of inputhandler.h
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../igutils.h"
#include "directinputhandler.h"
#include "xinputhandler.h"

// This Includes
#include "inputhandler.h"

// Static Variables
CInputHandler* CInputHandler::s_pInputHandler = 0;

// Static Function Prototypes


// Implementation
CInputHandler::CInputHandler()
: m_pXInputHandler(0)
#ifdef _DEBUG
, m_pDirectInput(0)
#endif // _DEBUG
{

}

CInputHandler::~CInputHandler()
{
	delete m_pXInputHandler;
	m_pXInputHandler = 0;

#ifdef _DEBUG
	delete m_pDirectInput;
	m_pDirectInput = 0;
#endif  // _DEBUG
}

/**
*
* This function Gets the CInputHandler singleton
*
* @Author Carsten Scholz
* @return Returns CInputHandler's singleton
* 
*/
CInputHandler& 
CInputHandler::GetInstance()
{
	if(s_pInputHandler == 0)
	{	
		s_pInputHandler = new CInputHandler();
	}

	return (*s_pInputHandler);
}

/**
*
* This function Destroys CInputHandler's singleton
*
* @Author Carsten Scholz
* 
*/
void 
CInputHandler::DestroyInstance()
{
	delete s_pInputHandler;
	s_pInputHandler = 0;
}

/**
*
* This function calls Initialise on both CDirectInputHandler and CXinputHandler
*
* @Author Carsten Scholz
* @_hAppInstance is the application instance
* @_hWnd is the handle to the window
* @return Returns true if both classes initialised successfully
* 
*/
bool 
CInputHandler::Initialise(HINSTANCE _hAppInstance, HWND _hWnd)
{
	m_AppInstance = _hAppInstance;
	m_hWnd = _hWnd;

#ifdef _DEBUG
	//Create keyboard input device
	m_pDirectInput = new CDirectInputHandler();
	VALIDATE(m_pDirectInput->Initialise(m_AppInstance, m_hWnd));
#endif // _DEBUG

	//Create controller input device
	m_pXInputHandler = new CXInputHandler();
	VALIDATE(m_pXInputHandler->Initialise());

	return true;
}

/**
*
* This function calls Update functions on both the CDirectInputHandler and CXinputHandler
*
* @Author Carsten Scholz
* 
*/
void 
CInputHandler::Update()
{
#ifdef _DEBUG
	m_pDirectInput->Update();
#endif // _DEBUG

	m_pXInputHandler->Update();
}

/**
*
* This function calls IsControlTriggered functions on the CXinputHandler
* If no _uiController variable is passed in then it calls CDirectInputHandler's IsControlTriggered
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it has been triggered
* @_uiController is the controller number 0-3 is Xbox360, -1(default) is the keyboard
* @return Returns true if the button has been pushed
*
*/
bool 
CInputHandler::IsControlTriggered(EControl _eControl, uint32 _uiController)
{
#ifdef _DEBUG
	if(_uiController == BAD_ID)
	{
		return (m_pDirectInput->IsControlTriggered(_eControl));
	}
#endif // _DEBUG

	if(_uiController != BAD_ID)
	{
		return (m_pXInputHandler->IsControlTriggered(_eControl, _uiController));
	}

	return (false);
}

/**
*
* This function calls IsControlHeld functions on the CXinputHandler
* If no _uiController variable is passed in then it calls CDirectInputHandler's IsControlHeld
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it has been Held
* @_uiController is the controller number 0-3 is Xbox360, -1(default) is the keyboard
* @return Returns true if the button has been pushed
*
*/
bool 
CInputHandler::IsControlHeld(EControl _eControl, uint32 _uiController)
{
#ifdef _DEBUG
	if(_uiController == BAD_ID)
	{
		return (m_pDirectInput->IsControlHeld(_eControl));
	}
#endif // _DEBUG

	if(_uiController != BAD_ID)
	{
		return (m_pXInputHandler->IsControlHeld(_eControl, _uiController));
	}

	return (false);
}

/**
*
* This function calls GetControlMagnitude functions on the CXinputHandler
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it has been Held
* @_uiController is the controller number 0-3 is Xbox360, -1(default) is the keyboard
* @If passed in keyboard nothing will happened
* @return Returns fMagnitude if above 0 then the control has been moved.
*
*/
float32 
CInputHandler::GetControlMagnitude(EControl _eControl, uint32 _uiController)
{
	if(_uiController != BAD_ID)
	{
		return (m_pXInputHandler->GetControlMagnitude(_eControl, _uiController));
	}

	return (0.0f);
}

/**
* 
* Returns true if the controller passed in is connected.
* 
* @author Rebeccah Cox
* @param uint32 _uiController - the ID of the controller to check.
* @return bool 
*/
bool
CInputHandler::IsControllerConnected(uint32 _uiController)
{
	if(_uiController != BAD_ID)
	{
		return (m_pXInputHandler->IsControllerConnected(_uiController));
	}

	return (false);
}

/**
* 
* Calls CXInputHandler's static function GetMaxNumControllers(), which returns 
*	the maximum number of controllers, usually four.
* 
* @author Rebeccah Cox
* @return uint32 - max number of controllers.
*/
uint32
CInputHandler::GetMaxNumControllers()
{
	return (CXInputHandler::GetMaxNumControllers());
}
