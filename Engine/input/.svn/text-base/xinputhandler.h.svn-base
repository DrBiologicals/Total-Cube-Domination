// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   xinputhandler.h
//  Description :   Declaration for Cxinputhandler
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_XINPUTHANDLER_H__
#define __IGFEB10_MODULE_XINPUTHANDLER_H__

// Library Includes
#include <xinput.h>

// Local Includes
#include "input.h"

// Types

// Prototypes
class CXInputController;

class CXInputHandler
{
	// Member Functions
public:
	CXInputHandler();
	~CXInputHandler();

	bool Initialise();
	void Update();

	bool IsControlTriggered(EControl _eControl, uint32 _uiController = -1);
	bool IsControlHeld(EControl _eControl, uint32 _uiController = -1);

	float32 GetControlMagnitude(EControl _eControl, uint32 _uiController = -1);

	bool IsControllerConnected(uint32 _uiController = -1);

	void SetVibration(uint32 _uiController, float32 _fMagnitude, EMotor _eMotor); 

	static uint32 GetMaxNumControllers();

protected:

private:

	// Member Variables
public:

protected:
	CXInputController* m_apControllers[4];
	static const uint32 MAX_NUM_CONTROLLERS;

private:

}; 

#endif // __IGFEB10_MODULE_XINPUTHANDLER_H__

