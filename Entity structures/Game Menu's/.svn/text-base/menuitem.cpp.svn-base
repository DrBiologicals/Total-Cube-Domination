// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menu.cpp
//  Description :   CMenu implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/input/inputhandler.h"

// This Includes
#include "menuitem.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* 
* Constructor.
* 
* @author Rebeccah Cox
*/
CMenuItem::CMenuItem()
: m_bIsActive(false)
, m_bIsExiting(false)
, m_bIsAdvancing(false)
, m_bIsBeingUsed(false)
, m_uiControllerID(0)
, m_bControllerIsConnected(false)
{
}

/**
* 
* Destructor.
* 
* @author Rebeccah Cox
*/
CMenuItem::~CMenuItem()
{
}

/**
* 
* Sets all of the member variables to default values.
* 
* @author Rebeccah Cox
* @return bool
*/
bool
CMenuItem::Initialise()
{
	m_bIsActive = false;
	m_bIsExiting = false;
	m_bIsAdvancing = false;
	m_bIsBeingUsed = false;
	m_uiControllerID = 0;
	m_bControllerIsConnected = false;

	return (true);
}

/**
* 
* Returns true if this menu item is currently active.
* 
* @author Rebeccah Cox
* @return bool m_bIsActive
*/
bool
CMenuItem::IsActive()
{
	return (m_bIsActive);
}

/**
* 
* Set the object to be active or not.
* 
* @author Rebeccah Cox
* @param bool _bIsActive
* @return void
*/
void
CMenuItem::SetActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}

/**
* 
* Returns true if controller one is assigned to this player selector, and the back key has been pressed.
* 
* @author Rebeccah Cox
* @return bool m_bIsExiting
*/
bool
CMenuItem::IsExiting()
{
	if(0 == m_uiControllerID && true == m_bIsExiting)
	{
		return (true);
	}

	return (false);
}

/**
* 
* Returns true if ready to move on to next menu screen.
* 
* @author Rebeccah Cox
* @return bool m_bIsAdvancing 
*/
bool
CMenuItem::IsAdvancing()
{
	return (m_bIsAdvancing);
}

/**
* 
* Returns true if the menu item is being used.
* Meaning that it is active and should be considered when checking 
*	for menu changes.
* 
* @author Rebeccah Cox
* @return bool m_bIsBeingUsed
*/
bool
CMenuItem::IsBeingUsed()
{
	return (m_bIsBeingUsed);
}

/**
* 
* Returns the controller ID number associated with this object.
* 
* @author Rebeccah Cox
* @return uint32 m_uiControllerID
*/
uint32
CMenuItem::GetControllerID()
{
	return (m_uiControllerID);
}

/**
* 
* Calls CInputHandler's IsControllerConnected function and returns the result, true or false.
* 
* @author Rebeccah Cox
* @return bool - true if the current controller ID is an active controller.
*/
bool
CMenuItem::IsControllerActive()
{
	// If the ID is bad (-1), just return false now.
	if(BAD_ID == m_uiControllerID)
	{
		return (false);
	}

	// Check connectivity with the input handler.
	return (CInputHandler::GetInstance().IsControllerConnected(m_uiControllerID));
}

/**
* 
* Checks for the first available controller and sets m_uiControllerID to it.
* If none is found, the ID is set to BAD_ID.
* 
* @author Rebeccah Cox
* @return void
*/
void
CMenuItem::UpdateControllerID()
{
	// Set the controllerID to the first controller index number.
	m_uiControllerID = 0;

	// While the controller ID is less than the maximum...
	while(CInputHandler::GetInstance().GetMaxNumControllers() >  m_uiControllerID)
	{
		// If the current controller ID represents a connected controller, break out of the loop.
		if(true == CInputHandler::GetInstance().IsControllerConnected(m_uiControllerID))
		{
			break;
		}

		// Increment the controller ID. 
		++m_uiControllerID;
	}

	// If no controller was found, set the ID to BAD_ID(-1).
	if(CInputHandler::GetInstance().GetMaxNumControllers() == m_uiControllerID)
	{
		m_uiControllerID = BAD_ID;
	}
}
