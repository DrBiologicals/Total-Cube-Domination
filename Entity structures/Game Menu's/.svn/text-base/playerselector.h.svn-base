// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   playerselector.h
//  Description :   Declaration for Cplayerselector
//  Author      :   Rebeccah Cox
//  Mail        :	rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PLAYERSELECTOR_H__
#define __IGFEB10_MODULE_PLAYERSELECTOR_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "menuitem.h"

// Types
enum EPlayerSelectorState
{
	PLAYER_NOT_CONNECTED,
	PLAYER_JOIN_GAME,
	PLAYER_SELECT_TEAM_GREEN,
	PLAYER_SELECT_TEAM_PURPLE,
	PLAYER_READY
};

// Prototypes

class CPlayerSelector: public CMenuItem
{
	// Member Functions
public:
	CPlayerSelector();
	virtual ~CPlayerSelector();

	bool Initialise(uint32 _uiControllerID, uint32 _uiNotConnectedBillboardID,
					uint32 _uiJoinGameBillboardID, uint32 _uiSelectTeamBillboardID, uint32 _uiGreenTeamBillboardID,
					uint32 _uiPurpleTeamBillboardID, uint32 _uiReadyBillboardID);

	virtual void Process(float32 _fDeltaTick);
	void Draw();

	D3DXMATRIX GetWorldMatrix();

	EPlayerSelectorState GetCurrentSelectorState();
	void SetCurrentSelectorState(EPlayerSelectorState _eState);

	void UpdateTextureIDs();

	bool CheckButtonPresses();
	void CheckControllerConnection();

	EPlayerSelectorState GetPlayerTeam();

	virtual void Reset();

protected:

private:

	// Member Variables
public:

protected:
	// Billboard IDs
	uint32 m_uiNotConnectedBillboardID;
	uint32 m_uiJoinGameBillboardID;
	uint32 m_uiSelectTeamBillboardID;
	uint32 m_uiGreenTeamBillboardID;
	uint32 m_uiPurpleTeamBillboardID;
	uint32 m_uiReadyBillboardID;

	// Active billboard IDs.
	uint32 m_uiActiveBillboardID;
	uint32 m_uiActiveTeamBillboardID;

	static uint32 s_uiPlayerCount;

	EPlayerSelectorState m_eCurrentSelectorState;

	// Timer to stop buttons from being triggered multiple times...
	float32 m_fButtonTimer;
	float32 m_fMaxTime;
	bool m_bCanTriggerButton;

	float32 m_fExtraToggleTimer;
	float32 m_fMaxExtraTime;
	bool m_bCanToggle;

private:

}; 

#endif // __IGFEB10_MODULE_PLAYERSELECTOR_H__

