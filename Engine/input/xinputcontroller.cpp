// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   xinputcontroller.cpp
//  Description :   xinputcontroller.cppfor implementation of xinputcontroller.h
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes
#include <climits>

// Local Includes

// This Includes
#include "xinputcontroller.h"

// Static Variables

// Static Function Prototypes


// Implementation

CXInputController::CXInputController()
{
	memset(this, 0, sizeof(*this));
}
CXInputController::~CXInputController()
{
}

/**
*
* This function Initialises the Controller and sets the controller and the deadzones
*
* @Author Carsten Scholz
* @_uiController is the controller number
* @return Returns true if both classes initialised successfully
* 
*/
bool 
CXInputController::Initialise(uint32 _uiController)
{
	m_uiController = _uiController;

	m_iLeftThumbStickDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	m_iRightThumbStickDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

	m_iRightTriggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

	m_iLeftTriggerDeadZone = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

    m_pActiveButtons = &m_uiButtonsA;
    m_pInactiveButtons = &m_uiButtonsB;

	SetVibration(0.0f, MOTOR_BOTH);

	return true;
}
/**
*
* This function updates the controller in order to see if buttons are being pushed
*
* @Author Carsten Scholz
* @return Returns true if the update was successful
* 
*/
bool 
CXInputController::Update()
{
	DWORD dwResult;

	XINPUT_STATE ControllerState;

	dwResult = XInputGetState(m_uiController, &ControllerState);

	if(dwResult == ERROR_SUCCESS)
	{
		m_bIsConnected = true;
	}
	else if(ERROR_DEVICE_NOT_CONNECTED == dwResult)
	{
		m_bIsConnected = false;
        return (false);
	}

	uint32* pTemp = m_pActiveButtons;
	m_pActiveButtons = m_pInactiveButtons;
	m_pInactiveButtons = pTemp;

	*m_pActiveButtons = ControllerState.Gamepad.wButtons;

	//LEFT ANALOG STICK
    if (abs(ControllerState.Gamepad.sThumbLX) > m_iLeftThumbStickDeadZone)
    {
        m_fLeftThumbStickX = (float32)ControllerState.Gamepad.sThumbLX / (float32)(SHRT_MAX - m_iLeftThumbStickDeadZone);
    }
    else
    {
        m_fLeftThumbStickX = 0.0f;
    }

    if (abs(ControllerState.Gamepad.sThumbLY) > m_iLeftThumbStickDeadZone)
    {
        m_fLeftThumbStickY = (float32)ControllerState.Gamepad.sThumbLY / (float32)(SHRT_MAX - m_iLeftThumbStickDeadZone);
    }
    else
    {
        m_fLeftThumbStickY = 0.0f;
    }

	//RIGHT ANALOG STICK
	int32 iRightThumbStickTotal = abs(ControllerState.Gamepad.sThumbRX) + abs(ControllerState.Gamepad.sThumbRY);
	if(iRightThumbStickTotal > m_iRightThumbStickDeadZone)
	{
		m_fRightThumbStickX = (float32)ControllerState.Gamepad.sThumbRX / (float32)(SHRT_MAX - m_iRightThumbStickDeadZone);
		m_fRightThumbStickY = (float32)ControllerState.Gamepad.sThumbRY / (float32)(SHRT_MAX - m_iRightThumbStickDeadZone);
	}
	else
	{
		m_fRightThumbStickX = 0.0f;
		m_fRightThumbStickY = 0.0f;
	}

	if(ControllerState.Gamepad.bRightTrigger < m_iRightTriggerDeadZone)
	{
		m_fRightTrigger = 0.0f;
	}
	else
	{
        m_fRightTrigger = (float32)ControllerState.Gamepad.bRightTrigger / (float32)(UCHAR_MAX - m_iRightTriggerDeadZone);
	}

	if(ControllerState.Gamepad.bLeftTrigger < m_fLeftTrigger)
	{
		m_fLeftTrigger = 0.0f;
	}
	else
	{
        m_fLeftTrigger = (float32)ControllerState.Gamepad.bLeftTrigger / (float32)(UCHAR_MAX - m_iLeftTriggerDeadZone);
	}

	return true;
}
/**
*
* This function Checks if a Xbox control is being triggered
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it is being pressed
* @return Returns true if the button was triggered
* 
*/
bool 
CXInputController::IsControlTriggered(EControl _eControl)
{
	switch(_eControl)
	{
		case CONTROL_EMP:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_RIGHT_SHOULDER));
		}
		break;
		case CONTROL_MINE:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_LEFT_SHOULDER));
		}
		break;
		case CONTROL_PAUSE:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_START) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_START));
		}
		break;
		case CONTROL_EXIT:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_BACK) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_BACK));
		}
		break;

		// Menu controls...
		case CONTROL_SELECT:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_A) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_A));
		}
		break;

		case CONTROL_BACK:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_B) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_B));
		}
		break;

		default:
		break;
	}

	return false;
}
/**
*
* This function Checks if a Xbox control is being Held
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it is being pressed
* @return Returns true if the button was Held
* 
*/
bool 
CXInputController::IsControlHeld(EControl _eControl)
{
	switch(_eControl)
	{
		case CONTROL_EMP:
		{
			return (((*m_pActiveButtons) & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
		}
		break;
		case CONTROL_MINE:
		{
			return (((*m_pActiveButtons) & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
		}
		break;
		case CONTROL_PAUSE:
		{
			return (((*m_pActiveButtons) & XINPUT_GAMEPAD_START) != 0);
		}
		break;

		case CONTROL_EXIT:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_BACK) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_BACK));
		}
		break;

		// Menu controls...
		case CONTROL_SELECT:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_A) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_A));
		}
		break;

		case CONTROL_BACK:
		{
			return ((((*m_pActiveButtons) & XINPUT_GAMEPAD_B) != 0) &&
				!((*m_pInactiveButtons) & XINPUT_GAMEPAD_B));
		}
		break;

		default:
		break;
	}

	return false;
}

/**
*
* This function Checks if a Xbox magnitude button has been moved or pressed
*
* @Author Carsten Scholz
* @_eControl is the control which is being checked if it is being pressed
* @return Returns > 0 if the button has been moved 0 if it has not
* 
*/
float32 
CXInputController::GetControlMagnitude(EControl _eControl)
{
	switch(_eControl)
	{		
		case CONTROL_MOVEUP:
		{
			return (m_fLeftThumbStickY);
		}
		break;

		case CONTROL_MOVEDOWN:
		{
			return (m_fLeftThumbStickY);
		}
		break;

		case CONTROL_MOVELEFT:
		{
			return (m_fLeftThumbStickX);
		}
		break;

		case CONTROL_MOVERIGHT:
		{
			return (m_fLeftThumbStickX);
		}
		break;

		case CONTROL_TURRETRIGHT:
		{
			return (m_fRightThumbStickX);
		}
		break;

		case CONTROL_TURRETLEFT:
		{
			return (m_fRightThumbStickY);
		}
		break;

		case CONTROL_SHOOT:
		{
			return (m_fRightTrigger);
		}
		break;

		case CONTROL_SCOUT:
		{
			return (m_fLeftTrigger);
		}
		break;
		// Menu controls...
		case CONTROL_NAVIGATEUP:
		{
			return (m_fLeftThumbStickY);
		}
		break;

		case CONTROL_NAVIGATEDOWN:
		{
			return (m_fLeftThumbStickY);
		}
		break;

		case CONTROL_NAVIGATELEFT:
		{
			return (m_fLeftThumbStickX);
		}
		break;

		case CONTROL_NAVIGATERIGHT:
		{
			return (m_fLeftThumbStickX);
		}
		break;

		default:break;
	}

	return(0.0f);
}
/**
*
* This function Sets the vibration of the Xbox controller
*
* @Author Carsten Scholz
* @_fMagnitude is the strength of the vibration
* @_eMotor is the motor which you want to vibrate
* 
*/
void 
CXInputController::SetVibration(float32 _fMagnitude, EMotor _eMotor)
{
	if (_eMotor & MOTOR_LEFT)
	{
		m_Vibration.wLeftMotorSpeed = static_cast<uint16>(_fMagnitude * (float32)VIBRATION_MODIFIER);
	}
	if (_eMotor & MOTOR_RIGHT)
	{
		m_Vibration.wRightMotorSpeed = static_cast<uint16>(_fMagnitude * (float32)VIBRATION_MODIFIER);
	}

	XInputSetState(m_uiController, &m_Vibration);
}

/**
* 
* Returns true if the controller is connected.
* 
* @author Rebeccah Cox
* @return true
*/
bool
CXInputController::IsControllerConnected()
{
	return (m_bIsConnected);
}
