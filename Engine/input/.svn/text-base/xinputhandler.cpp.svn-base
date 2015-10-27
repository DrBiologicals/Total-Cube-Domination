// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   xinputhandler.cpp
//  Description :   xinputhandler.cppfor implementation of xinputhandler.h
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "xinputcontroller.h"

// This Includes
#include "xinputhandler.h"

// Static Variables
const uint32 CXInputHandler::MAX_NUM_CONTROLLERS = 4;

// Static Function Prototypes

// Implementation

CXInputHandler::CXInputHandler()
{
    memset(m_apControllers, 0, sizeof(m_apControllers));
}
CXInputHandler::~CXInputHandler()
{
	for(int32 i = 0; i < 4; ++i)
	{
		delete m_apControllers[i];
		m_apControllers[i] = 0;
	}
}
/**
*
* This function Checks how many controllers are plugged in then calls Initialise 
* on CXinputController depends on how many controllers are plugged in.
*
* @Author Carsten Scholz
* @return Returns true if initialised successfully
* 
*/
bool 
CXInputHandler::Initialise()
{
	DWORD dwResult;

	for( DWORD i = 0; i < 4; i++)
	{
		m_apControllers[i] = new CXInputController;

		XINPUT_STATE xstate;

		ZeroMemory(&xstate, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &xstate);

		m_apControllers[i]->Initialise(i);
	}

	return true;
}
/**
*
* This function calls update on the CXInputController function
*
* @Author Carsten Scholz
* 
*/
void 
CXInputHandler::Update()
{
	for(int32 i = 0; i < 4; ++i)
	{
		m_apControllers[i]->Update();
	}
}
/**
*
* This function calls IsControlTriggered on the CXInputController function
*
* @Author Carsten Scholz
* @param _eControl is the control which is being checked if it has been triggered
* @param _uiController is the controller which is being checked
* @return Returns true if the button has been pushed
* 
*/
bool 
CXInputHandler::IsControlTriggered(EControl _eControl, uint32 _uiController)
{
	bool bTriggered = m_apControllers[_uiController]->IsControlTriggered(_eControl);

	return bTriggered;
}
/**
*
* This function calls IsControlHeld on the CXInputController function
*
* @Author Carsten Scholz
* @param _eControl is the control which is being checked if it has been Held
* @param _uiController is the controller which is being checked
* @return Returns true if the button has been pushed
* 
*/
bool 
CXInputHandler::IsControlHeld(EControl _eControl, uint32 _uiController)
{
	bool bHeld = m_apControllers[_uiController]->IsControlHeld(_eControl);

	return bHeld;
}

/**
*
* This function calls GetControlMagnitude on the CXInputController function
*
* @Author Carsten Scholz
* @param _eControl is the control which is being checked if it has been moved
* @param _uiController is the controller which is being checked
* @return Returns more than 0 if the button has been moved
* 
*/
float32 
CXInputHandler::GetControlMagnitude(EControl _eControl, uint32 _uiController)
{
	float32 fMagnitude = m_apControllers[_uiController]->GetControlMagnitude(_eControl);

	return fMagnitude;
}

/**
* 
* Calls the IsControllerConnected function in the controller passed in.
* 
* @author Rebeccah Cox
* @param uint32 _uiController - ID for which controller to check
* @return bool
*/
bool
CXInputHandler::IsControllerConnected(uint32 _uiController)
{
	return(m_apControllers[_uiController]->IsControllerConnected());
}

void 
CXInputHandler::SetVibration(uint32 _uiController, float32 _fMagnitude, EMotor _eMotor)
{
	m_apControllers[_uiController]->SetVibration(_fMagnitude, _eMotor);
}

/**
* 
* Returns the maximum number of controllers.
* 
* @author Rebeccah Cox
* @return uint32 MAX_NUM_CONTROLLERS
*/
uint32
CXInputHandler::GetMaxNumControllers()
{
	return (MAX_NUM_CONTROLLERS);
}
