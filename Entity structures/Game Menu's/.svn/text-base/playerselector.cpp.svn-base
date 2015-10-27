// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   playerselector.cpp
//  Description :   playerselector.cppfor implementation of playerselector.h
//  Author      :   Rebeccah Cox
//  Mail        :	rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/billboard.h"
#include "../../engine/graphics and sound/billboardmanager.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/Totalcubedomination.h"
#include "../../engine/input/input.h"
#include "../../engine/input/inputhandler.h"
#include "../../engine/game/programstate.h"

// This Includes
#include "playerselector.h"

// Static Variables
uint32 CPlayerSelector::s_uiPlayerCount = 0;

// Static Function Prototypes

// Implementation

/**
* 
* Constructor.
* 
* @author Rebeccah Cox
*/
CPlayerSelector::CPlayerSelector()
: m_eCurrentSelectorState(PLAYER_NOT_CONNECTED)
, m_uiActiveBillboardID(0)
, m_uiActiveTeamBillboardID(0)
, m_fButtonTimer(0.0f)
, m_fMaxTime(0.0f)
, m_bCanTriggerButton(true)
, m_uiNotConnectedBillboardID(BAD_ID)
, m_uiJoinGameBillboardID(BAD_ID)
, m_uiSelectTeamBillboardID(BAD_ID)
, m_uiGreenTeamBillboardID(BAD_ID)
, m_uiPurpleTeamBillboardID(BAD_ID)
, m_uiReadyBillboardID(BAD_ID)
, m_fExtraToggleTimer(0.0f)
, m_fMaxExtraTime(0.0f)
, m_bCanToggle(true)
{
	D3DXMatrixIdentity(&m_matWorld);
}

/**
* 
* Destructor.
* 
* @author Rebeccah Cox
*/
CPlayerSelector::~CPlayerSelector()
{
}

/**
* 
* Stores the position and the controller ID. Creates two billboards: a small one for the blocks 
*	of team colours used in the select team section, and a larger one for every other texture eg.
*	the 'not connected' display.
* 
* @author Rebeccah Cox
* @param D3DXVECTOR3 _vec3Position
* @param uint32 _uiControllerID
* @return bool
*/
bool
CPlayerSelector::Initialise(uint32 _uiControllerID, uint32 _uiNotConnectedBillboardID,
					uint32 _uiJoinGameBillboardID, uint32 _uiSelectTeamBillboardID, uint32 _uiGreenTeamBillboardID,
					uint32 _uiPurpleTeamBillboardID, uint32 _uiReadyBillboardID)
{
	CMenuItem::Initialise();

	// Reset player count.
	s_uiPlayerCount = 0;

	// Store controller ID.
	m_uiControllerID = _uiControllerID;

	// Set max time between button presses.
	m_fMaxTime = 0.2f;
	m_fMaxExtraTime = 0.2f;

	// Set the billboard IDs.
	m_uiNotConnectedBillboardID = _uiNotConnectedBillboardID;
	m_uiJoinGameBillboardID = _uiJoinGameBillboardID;
	m_uiSelectTeamBillboardID = _uiSelectTeamBillboardID;
	m_uiGreenTeamBillboardID = _uiGreenTeamBillboardID;
	m_uiPurpleTeamBillboardID = _uiPurpleTeamBillboardID;
	m_uiReadyBillboardID = _uiReadyBillboardID;

	CInputHandler::GetInstance().Update();
	if(true == CInputHandler::GetInstance().IsControllerConnected(m_uiControllerID))
	{
		m_uiActiveBillboardID = m_uiJoinGameBillboardID;
		m_bControllerIsConnected = true;
		m_eCurrentSelectorState = PLAYER_JOIN_GAME;
	}
	else
	{
		m_uiActiveBillboardID = m_uiNotConnectedBillboardID;
		m_bControllerIsConnected = false;
		m_eCurrentSelectorState = PLAYER_NOT_CONNECTED;
	}

	return (true);
}

/**
* 
* Adds this object to the viewport this object belongs to.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void
CPlayerSelector::Process(float32 _fDeltaTick)
{
	if(true == m_bIsActive)
	{
		// Check if players are connected.
		CheckControllerConnection();

		if(true == m_bCanTriggerButton)
		{
			// Check for button presses.
			if(true == CheckButtonPresses())
			{
				m_bCanTriggerButton = false;
			}

			if(false == m_bCanToggle)
			{
				// Increment toggle offset timer.
				m_fExtraToggleTimer += _fDeltaTick;
			}

			if(m_fExtraToggleTimer >= m_fMaxExtraTime)
			{
				m_bCanToggle = true;
			}

		}
		else
		{
			if(m_fButtonTimer >= m_fMaxTime)
			{
				m_bCanTriggerButton = true;
				m_fButtonTimer = 0.0f;
			}

			m_fButtonTimer += _fDeltaTick;
		}

		// Add to viewports.
		CTotalCubeDomination::GetInstance().GetRenderer()
			->AddToViewport(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE, 0);
	}
}

/**
* 
* Draws the billboard/s associated with this object.
* 
* @author Rebeccah Cox
* @return void
*/
void
CPlayerSelector::Draw()
{
	// Draw the main/default billboard.
	CBillboardManager::GetInstance().Draw(m_uiActiveBillboardID);

	// If the team select screen is the current screen, then draw the extra team billboard.
	if(m_uiActiveBillboardID == m_uiSelectTeamBillboardID
		|| m_uiActiveBillboardID == m_uiReadyBillboardID)
	{
        CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
        pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		CBillboardManager::GetInstance().Draw(m_uiActiveTeamBillboardID);

        pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}

/**
* 
* Returns a reference to the world martrix.
* 
* @author Rebeccah Cox
* @return D3DXMATRIX m_matWorld
*/
D3DXMATRIX
CPlayerSelector::GetWorldMatrix()
{
	return (m_matWorld);
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @return EPlayerSelectorState m_eCurrentSelectorState
*/
EPlayerSelectorState
CPlayerSelector::GetCurrentSelectorState()
{
	return (m_eCurrentSelectorState);
}

/**
* 
* Sets the current state to the value passed in. See the header file for 
*	the different enum values possible. 
* 
* @author Rebeccah Cox
* @param EPlayerSelectorState _eState
* @return void
*/
void
CPlayerSelector::SetCurrentSelectorState(EPlayerSelectorState _eState)
{
	m_eCurrentSelectorState = _eState;
	UpdateTextureIDs();
}

/**
* 
* Sets the current texture IDs, depending on the current EPlayerSelectorState.
* 
* @author Rebeccah Cox
* @return void
*/
void
CPlayerSelector::UpdateTextureIDs()
{
	switch (m_eCurrentSelectorState)
	{
		case PLAYER_NOT_CONNECTED:
		{
			m_uiActiveBillboardID = m_uiNotConnectedBillboardID;
			break;
		}
		case PLAYER_JOIN_GAME:
		{
			m_uiActiveBillboardID = m_uiJoinGameBillboardID;
			break;
		}
		case PLAYER_SELECT_TEAM_GREEN:
		{
			m_uiActiveBillboardID = m_uiSelectTeamBillboardID;
			m_uiActiveTeamBillboardID = m_uiGreenTeamBillboardID;
			break;
		}
		case PLAYER_SELECT_TEAM_PURPLE:
		{
			m_uiActiveBillboardID = m_uiSelectTeamBillboardID;
			m_uiActiveTeamBillboardID = m_uiPurpleTeamBillboardID;
			break;
		}
		case PLAYER_READY:
		{
			m_uiActiveBillboardID = m_uiReadyBillboardID;
			break;
		}

		default:break;
	}
}

/**
* 
* Checks for any key presses, and switches out the selector screens accordingly.
* 
* @author Rebeccah Cox
* @return bool - if button was pressed.
*/
bool
CPlayerSelector::CheckButtonPresses()
{
	bool bButtonPressed = false;

	// If select button (A) is held:
	if(true == CInputHandler::GetInstance().IsControlTriggered(CONTROL_SELECT, m_uiControllerID))
	{
		// If in PLAYER_JOIN_GAME state.
		if(PLAYER_JOIN_GAME == m_eCurrentSelectorState)
		{
			// Change to PLAYER_SELECT_TEAM_GREEN.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_GREEN);
			m_bIsBeingUsed = true;
			bButtonPressed = true;
		}
		// Else if in PLAYER_SELECT_TEAM_GREEN or PLAYER_SELECT_TEAM_PURPLE state.
		else if(PLAYER_SELECT_TEAM_GREEN == m_eCurrentSelectorState
			|| PLAYER_SELECT_TEAM_PURPLE == m_eCurrentSelectorState)
		{
            // Set player to the appropriate team.
			if(PLAYER_SELECT_TEAM_GREEN == m_eCurrentSelectorState)
			{
				CProgramState::SetPlayerTeam(m_uiControllerID, true);

				// Set to advance to the next menu.
				m_bIsAdvancing = true;
				bButtonPressed = true;
			}
			else if(PLAYER_SELECT_TEAM_PURPLE == m_eCurrentSelectorState)
			{
				CProgramState::SetPlayerTeam(m_uiControllerID, false);

				// Set to advance to the next menu.
				m_bIsAdvancing = true;
				bButtonPressed = true;
			}

			CProgramState::SetNumPlayer(CProgramState::GetNumPlayers()+1);

            // Change to PLAYER_READY.
			SetCurrentSelectorState(PLAYER_READY);
			bButtonPressed = true;
		}
		// Else if in PLAYER_READY state.
		else if(PLAYER_READY == m_eCurrentSelectorState)
		{
			bButtonPressed = true;
		}
	}

	// If the navigate left control is triggered (left analog stick).
	else if(-0.9f > CInputHandler::GetInstance().GetControlMagnitude(CONTROL_NAVIGATELEFT, m_uiControllerID)
		&& true == m_bCanToggle)
	{
		// If in PLAYER_SELECT_TEAM_GREEN state.
		if(PLAYER_SELECT_TEAM_GREEN == m_eCurrentSelectorState)
		{
			// Change to PLAYER_SELECT_TEAM_PURPLE.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_PURPLE);
			bButtonPressed = true;
			m_bCanToggle = false;
		}
		// Else if in PLAYER_SELECT_TEAM_PURPLE state.
		else if(PLAYER_SELECT_TEAM_PURPLE == m_eCurrentSelectorState)
		{
			// Change to PLAYER_SELECT_TEAM_GREEN.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_GREEN);
			bButtonPressed = true;
			m_bCanToggle = false;
		}
	}

	// If the navigate right control is triggered (left analog stick).
	else if(0.9f < CInputHandler::GetInstance().GetControlMagnitude(CONTROL_NAVIGATERIGHT, m_uiControllerID)
		&& true == m_bCanToggle)
	{
		// If in PLAYER_SELECT_TEAM_GREEN state.
		if(PLAYER_SELECT_TEAM_GREEN == m_eCurrentSelectorState)
		{
			// Change to PLAYER_SELECT_TEAM_PURPLE.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_PURPLE);
			bButtonPressed = true;
			m_bCanToggle = false;
		}
		// Else if in PLAYER_SELECT_TEAM_PURPLE state.
		else if(PLAYER_SELECT_TEAM_PURPLE == m_eCurrentSelectorState)
		{
			// Change to PLAYER_SELECT_TEAM_GREEN.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_GREEN);
			bButtonPressed = true;
			m_bCanToggle = false;
		}
	}

	// If exit button (B) is held:
	else if(true == CInputHandler::GetInstance().IsControlTriggered(CONTROL_BACK, m_uiControllerID))
	{
		// If in PLAYER_READY:
		if(PLAYER_READY == m_eCurrentSelectorState)
		{
			// Change current screen to PLAYER_SELECT_TEAM_PURPLE or PLAYER_SELECT_TEAM_GREEN.
			SetCurrentSelectorState(PLAYER_SELECT_TEAM_GREEN);
			bButtonPressed = true;
		}
		// If in PLAYER_SELECT_TEAM_PURPLE or PLAYER_SELECT_TEAM_GREEN:
		else if(PLAYER_SELECT_TEAM_PURPLE == m_eCurrentSelectorState
			|| PLAYER_SELECT_TEAM_GREEN == m_eCurrentSelectorState)
		{
			// Change current screen to PLAYER_JOIN_GAME.
			SetCurrentSelectorState(PLAYER_JOIN_GAME);
			m_bIsBeingUsed = false;
			bButtonPressed = true;
		}
		// If in PLAYER_JOIN_GAME and controller is player one:
		else if(PLAYER_JOIN_GAME == m_eCurrentSelectorState)
		{
			// Go back to main menu.
			m_bIsExiting = true;
			bButtonPressed = true;
		}
	}

	return (bButtonPressed);
}

/**
* 
* Checks if the controllers are connected or not, and changes the current 
*	screen state accordingly.
* 
* @author Rebeccah Cox
* @return void
*/
void
CPlayerSelector::CheckControllerConnection()
{
	// If the controller was connected, and has now been disconnected...
	if(false == CInputHandler::GetInstance().IsControllerConnected(m_uiControllerID)
		&& true == m_bControllerIsConnected)
	{
		// Set the controller connection to be false.
		m_bControllerIsConnected = false;

		// Set the current selector state to PLAYER_NOT_CONNECTED to update display.
		SetCurrentSelectorState(PLAYER_NOT_CONNECTED);
	}
	// Else if the controller was disconnected, and is now connected...
	else if(true == CInputHandler::GetInstance().IsControllerConnected(m_uiControllerID)
		&& false == m_bControllerIsConnected)
	{
		// Set the controller connection to be true.
		m_bControllerIsConnected = true;

		// Set the current selector state to PLAYER_JOIN_GAME to update display.
		SetCurrentSelectorState(PLAYER_JOIN_GAME);
	}
}

/**
* 
* Checks which team the player selector box is currently assigned to.
* Defaults to the PLAYER_NOT_CONNECTED if no player is using box.
* 
* @author Rebeccah Cox
* @param uint32 _uiPlayerID - which box to check.
* @return EPlayerSelectorState - either PLAYER_SELECT_TEAM_GREEN, PLAYER_SELECT_TEAM_PURPLE or PLAYER_NOT_CONNECTED.
*/
EPlayerSelectorState
CPlayerSelector::GetPlayerTeam()
{
	if(PLAYER_NOT_CONNECTED == m_eCurrentSelectorState)
	{
		return (PLAYER_NOT_CONNECTED);
	}
	else if(m_uiActiveTeamBillboardID == m_uiPurpleTeamBillboardID)
	{
		return (PLAYER_SELECT_TEAM_PURPLE);
	}
	else
	{
		return (PLAYER_SELECT_TEAM_GREEN);
	}
}

/**
* 
* Resets to the state it needs to be in when entering the menu.
* 
* @author Rebeccah Cox
* @return void.
*/
void
CPlayerSelector::Reset()
{
	Initialise(m_uiControllerID, m_uiNotConnectedBillboardID, m_uiJoinGameBillboardID,
				m_uiSelectTeamBillboardID, m_uiGreenTeamBillboardID, m_uiPurpleTeamBillboardID,
				m_uiReadyBillboardID);
}
