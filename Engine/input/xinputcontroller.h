// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   xinputcontroller.h
//  Description :   Declaration for CXInputController
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_XINPUTCONTROLLER_H__
#define __IGFEB10_MODULE_XINPUTCONTROLLER_H__

// Library Includes
#include <xinput.h>

// Local Includes
#include "input.h"

// Types

// Prototypes


//class CInputHandler;
class CXInputController
{
	// Member Functions
public:
	CXInputController();
	~CXInputController();

	bool Initialise(uint32 _uiController);
	bool Update();

	bool IsControlTriggered(EControl _eControl);
	bool IsControlHeld(EControl _eControl);

	float32 GetControlMagnitude(EControl _eControl);
	void SetVibration(float32 _fMagnitude, EMotor _eMotor);

	bool IsControllerConnected();

protected:

private:

	// Member Variables
public:

protected:
	uint32 m_uiController;

	XINPUT_VIBRATION m_Vibration;

	float32 m_fLeftThumbStickX;
	float32 m_fLeftThumbStickY;
	int32 m_iLeftThumbStickDeadZone;

	float32 m_fRightThumbStickX;
	float32 m_fRightThumbStickY;
	int32 m_iRightThumbStickDeadZone;

	float32 m_fRightTrigger;
	int32 m_iRightTriggerDeadZone;

	float32 m_fLeftTrigger;
	int32 m_iLeftTriggerDeadZone;

	uint32 m_uiButtonsA;
	uint32 m_uiButtonsB;

	uint32* m_pActiveButtons;
	uint32* m_pInactiveButtons;

	uint32 m_uiLastPacket;

	bool m_bIsConnected;

private:

}; 

#endif // __IGFEB10_MODULE_XINPUTCONTROLLER_H__

