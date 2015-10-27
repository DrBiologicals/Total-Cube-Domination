// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   keyboard.cpp
//  Description :   keyboard.cppfor implementation of keyboard.h
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//


#ifdef _DEBUG
// Library Includes

// Local Includes

// This Includes
#include "keyboard.h"

// Static Variables

// Static Function Prototypes
#define KEYDOWN(name, key) (name[key] & 0x80)

// Implementation

CKeyboard::CKeyboard()
: m_pActiveBuffer(0)
, m_pInactiveBuffer(0)
, m_pDirectInputDevice(0)
{
	memset(m_acBufferA, 0, sizeof(m_acBufferA));
	memset(m_acBufferB, 0, sizeof(m_acBufferB));
}
CKeyboard::~CKeyboard()
{
	if (m_pDirectInputDevice)
	{
		m_pDirectInputDevice->Unacquire();
		m_pDirectInputDevice->Release();
	}
}

/**
*
* This function Initialises the device
*
* @Author Carsten Scholz
* @_pDirectInput is the LPDIRECTINPUT8 structure which is used to set up the keyboard device
* @_Hwnd is the handle to the window
* @returns a bool, if true then the device initialised successfully
* 
*/
bool 
CKeyboard::Initialise(LPDIRECTINPUT8 _pDirectInput, HWND _Hwnd)
{
	HRESULT hr;

	//Create a keyboard device.
	hr = _pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDevice, NULL);

	if(FAILED(hr))
	{
		return (false);
	}

	//Set the data format for the keyboard device
	hr = m_pDirectInputDevice->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		m_pDirectInputDevice->Release();

		return (false);
	}

	//Set the cooperative level for the keyboard device.
	hr = m_pDirectInputDevice->SetCooperativeLevel(_Hwnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	if(FAILED(hr))
	{
		m_pDirectInputDevice->Release();

		return false;
	}

	//Acquire the keyboard device.
	hr = m_pDirectInputDevice->Acquire();

	if(FAILED(hr))
	{
		m_pDirectInputDevice->Release();
		return (false);
	}

	m_pActiveBuffer = m_acBufferA;
	m_pInactiveBuffer = m_acBufferB;

	return (true);
}

/**
*
* This function Stores all the data for the buttons which have been pressed
*
* @Author Carsten Scholz
* @returns a bool, if true then the data was filled in correctly if false it failed.
* 
*/
bool 
CKeyboard::Update()
{
	HRESULT hr;

    char* pTemp = m_pActiveBuffer;
	m_pActiveBuffer = m_pInactiveBuffer;
	m_pInactiveBuffer = pTemp;

	bool bLoop = true;

	while (bLoop)
	{
		//Poll the device
		m_pDirectInputDevice->Poll();

		//Read in the state.
		hr = m_pDirectInputDevice->GetDeviceState(256, m_pActiveBuffer);
		if(SUCCEEDED(hr))
		{
			bLoop = false;
		}
		else if(hr != DIERR_INPUTLOST && hr != DIERR_NOTACQUIRED)
		{
			return false;
		}
		else if(FAILED(m_pDirectInputDevice->Acquire()))
		{
			return false;
		}
	}

	return true;
}

/**
*
* This function Checks if a button is being triggered on the keyboard
*
* @Author Carsten Scholz
* @param _eControl Is the button which is being checked if it is being triggered
* @returns a bool, if true then the button is pressed if false the button is not pressed..
* 
*/
bool 
CKeyboard::IsControlTriggered(EControl _eControl)
{
	switch(_eControl)
	{
		//*****************************************************
		//Debug Camera Controls
		//F1 Debug Camera enabled
		case CONTROL_ENABLE_DEBUG_CAMERA:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_F1) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_F1)));
		}
		break;
		//Arrow left
		case CONTROL_CAMERALEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_LEFT) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_LEFT)));
		}
		break;
		//Arrow Right
		case CONTROL_CAMERARIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_RIGHT) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_RIGHT)));
		}
		break;
		//Arrow up
		case CONTROL_CAMERAFORWARD:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_UP) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_UP)));
		}
		break;
		//Arrow down
		case CONTROL_CAMERABACK:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_DOWN) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_DOWN)));
		}
		break;
		//Page Up
		case CONTROL_CAMERAUP:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_PRIOR) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_PRIOR)));
		}
		//Page Down
		break;
		case CONTROL_CAMERADOWN:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NEXT) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NEXT)));
		}
		break;
		//Letter A
		case CONTROL_CAMERAYAWLEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_A) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_A)));
		}
		break;
		//Letter D
		case CONTROL_CAMERAYAWRIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_D) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_D)));
		}
		break;
		//Letter W
		case CONTROL_CAMERAPITCHUP:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_W) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_W)));
		}
		break;
		//Letter S
		case CONTROL_CAMERAPITCHDOWN:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_S) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_S)));
		}
		//Letter R
		break;
		case CONTROL_CAMERAROLLLEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_R) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_R)));
		}
		break;
		//Letter T
		case CONTROL_CAMERAROLLRIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_T) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_T)));
		}
		break;
		//*******************************************************
		//*******************************************************
		//Cheats Codes
		//Num Pad 1
		case CONTROL_CHEATINVINC:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD1) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD1)));
		}
		break;
		//Num Pad 2
		case CONTROL_CHEATNEVEREND:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD2) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD2)));
		}
		break;
		//Num Pad 3
		case CONTROL_CHEATINVIS:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD3) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD3)));
		}
		break;
		//Num Pad 4
		case CONTROL_CHEATSHEILD:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD4) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD4)));
		}
		//Num Pad 5
		break;
		case CONTROL_CHEATFLAGCAPTURE:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD5) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD5)));
		}
		break;
		//Num Pad 6
		case CONTROL_CHEATPIC:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD6) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_NUMPAD6)));
		}
		//Num 1
		case CONTROL_PLAYER1:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_1) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_1)));
		}
		//Num 2
		case CONTROL_PLAYER2:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_2) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_2)));
		}
		//Num 3
		case CONTROL_PLAYER3:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_3) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_3)));
		}
		//Num 4
		case CONTROL_PLAYER4:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_4) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_4)));
		}
		// Debug window toggle key
		case CONTROL_ENABLE_DEBUG_WINDOW:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_F2) != 0)) &&
				!((KEYDOWN(m_pInactiveBuffer, DIK_F2)));
		}

	}

	return false;
}
/**
*
* This function Checks if a button is being pressed on the keyboard
*
* @Author Carsten Scholz
* @param _eControl Is the button which is being checked if it is being held
* @returns a bool, if true then the button is pressed if false the button is not pressed..
* 
*/
bool 
CKeyboard::IsControlHeld(EControl _eControl)
{
	switch(_eControl)
	{
		//*****************************************************
		//Debug Camera Controls
		//F1 Debug Camera enabled
		case CONTROL_ENABLE_DEBUG_CAMERA:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_F1) != 0));
		}
		break;
		//Arrow left
		case CONTROL_CAMERALEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_LEFT) != 0));
		}
		break;
		//Arrow Right
		case CONTROL_CAMERARIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_RIGHT) != 0));
		}
		break;
		//Arrow up
		case CONTROL_CAMERAFORWARD:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_UP) != 0));
		}
		break;
		//Arrow down
		case CONTROL_CAMERABACK:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_DOWN) != 0));
		}
		break;
		//Page Up
		case CONTROL_CAMERAUP:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_PRIOR) != 0));
		}
		//Page Down
		break;
		case CONTROL_CAMERADOWN:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NEXT) != 0));
		}
		break;
		//Letter A
		case CONTROL_CAMERAYAWLEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_A) != 0));
		}
		break;
		//Letter D
		case CONTROL_CAMERAYAWRIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_D) != 0));
		}
		break;
		//Letter W
		case CONTROL_CAMERAPITCHUP:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_W) != 0));
		}
		break;
		//Letter S
		case CONTROL_CAMERAPITCHDOWN:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_S) != 0));
		}
		//Letter R
		break;
		case CONTROL_CAMERAROLLLEFT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_Q) != 0));
		}
		break;
		//Letter T
		case CONTROL_CAMERAROLLRIGHT:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_E) != 0));
		}
		break;
		//*******************************************************
		//*******************************************************
		//Cheats Codes
		//Num Pad 1
		case CONTROL_CHEATINVINC:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD1) != 0));
		}
		break;
		//Num Pad 2
		case CONTROL_CHEATNEVEREND:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD2) != 0));
		}
		break;
		//Num Pad 3
		case CONTROL_CHEATINVIS:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD3) != 0));
		}
		break;
		//Num Pad 4
		case CONTROL_CHEATSHEILD:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD4) != 0));
		}
		//Num Pad 5
		break;
		case CONTROL_CHEATFLAGCAPTURE:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD5) != 0));
		}
		break;
		//Num Pad 6
		case CONTROL_CHEATPIC:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_NUMPAD6) != 0));
		}
		break;
				//Num 1
		case CONTROL_PLAYER1:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_1) != 0));
		}
		//Num 2
		case CONTROL_PLAYER2:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_2) != 0));
		}
		//Num 3
		case CONTROL_PLAYER3:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_3) != 0));
		}
		//Num 4
		case CONTROL_PLAYER4:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_4) != 0));
		}
		//Num 5
		case CONTROL_PLAYER5:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_5) != 0));
		}
		//Num 6
		case CONTROL_PLAYER6:
		{
			return ((KEYDOWN(m_pActiveBuffer, DIK_6) != 0));
		}

	}

	return false;
}
#endif // _DEBUG