//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   debugcamera.cpp
//  Description :   debugcamera implementation (source) file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes
#ifdef _DEBUG

// Local Includes
#include "../TotalCubeDomination.h"
#include "../../igutils.h"
#include "viewport.h"
#include "../Input/inputhandler.h"

// This Include
#include "debugcamera.h"

// Static Variables

// Static Function Prototypes

// Implementation

CDebugCamera::CDebugCamera()
{
}

CDebugCamera::~CDebugCamera()
{
}

/**
* 
* Calls the ProcessControls function to update the camera's position etc.
* Rotates the camera by the current yaw, pitch and roll values, and then 
*	re-calculates the view matrix by calling the SetView3D function. 
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void 
CDebugCamera::Process(float32 _fDeltaTick)
{
	ProcessControls(_fDeltaTick);

	D3DXQUATERNION quatRotation;
	D3DXQuaternionRotationYawPitchRoll(&quatRotation, m_fYaw, m_fPitch, m_fRoll);

	SetViewQuaternion(m_vec3Position, quatRotation);
}

/**
* 
* CONTROL_F1,
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void 
*/
void
CDebugCamera::ProcessControls(float32 _fDeltaTick)
{
	// Get the input handler.
	CInputHandler& rInputHandler = CInputHandler::GetInstance();

	// Call IsControlTriggered on the input handler to check each control 
	//	that the debug camera uses. 
	// NOTE: The second parameter (_uiController) is left blank, as the default 
	//			is the keyboard input.

	// Temp variables to alter movement/rotation speeds by system time.
	float32 fMoveSpeed = 10.0f * _fDeltaTick;
	float32 fRotateSpeed = D3DX_PI * 0.5f * _fDeltaTick;

	// Check the movement controls.
	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERALEFT))
	{
		// Move the camera left using Strafe.
		m_vec3Position += m_vec3Right * (-fMoveSpeed);
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERARIGHT))
	{
		// Move the camera right using Strafe.
		m_vec3Position += m_vec3Right * (fMoveSpeed);
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAFORWARD))
	{
		// Move the camera forward using Move.
		m_vec3Position += m_vec3Look * (fMoveSpeed);
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERABACK))
	{
		// Move the camera backward using Move.
		m_vec3Position += m_vec3Look * (-fMoveSpeed);
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAUP))
	{
		m_vec3Position += D3DXVECTOR3(0.0f, 1.0f, 0.0f) * (fMoveSpeed);
	}
	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERADOWN))
	{
		// Move the camera down using Fly.
		m_vec3Position += D3DXVECTOR3(0.0f, 1.0f, 0.0f) * (-fMoveSpeed);
	}
	
	// Check the angle controls.
	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAYAWLEFT))
	{
		// Rotate the camera left on the yaw axis.
		m_fYaw -= fRotateSpeed;
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAYAWRIGHT))
	{
		// Rotate the camera right on the yaw axis.
		m_fYaw += fRotateSpeed;
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAPITCHUP))
	{
		// Rotate the camera up on the pitch axis.
		m_fPitch -= fRotateSpeed;
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAPITCHDOWN))
	{
		// Rotate the camera down on the pitch axis.
		m_fPitch += fRotateSpeed;
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAROLLLEFT))
	{
		// Rotate the camera left on the roll axis.
		m_fRoll -= fRotateSpeed;
	}

	if(true == rInputHandler.IsControlHeld(CONTROL_CAMERAROLLRIGHT))
	{
		// Rotate the camera right on the roll axis.
		m_fRoll += fRotateSpeed;
	}
}
#endif // _DEBUG