// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   statistics.cpp
//  Description :   statistics.cppfor implementation of statistics.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Entity structures/Game Menu's/text.h"
#include "../../igutils.h"
#include "../Viewport/viewport.h"
#include "../TotalCubeDomination.h"
#include "../Graphics and sound/renderer.h"
#include "../Graphics and sound/fontmanager.h"
#include "programstate.h"
#include "menustate.h"
#include "../../entity structures/game menu's/staticgraphic.h"
#include "../graphics and sound/billboardmanager.h"
#include "../input/input.h"
#include "../input/inputhandler.h"
#include "../graphics and sound/texturemanager.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Player Objects/playermanager.h"
#include "../../Entity structures/Player Objects/player.h"
// This Includes

#include "statistics.h"

// Static Variables

// Static Function Prototypes


// Implementation
CStatistics::CStatistics()
: m_fCurrentTime(0.0f)
{

}
CStatistics::~CStatistics()
{
	for(uint32 ui = 0; ui < m_vecText.size(); ++ui)
	{
		delete m_vecText[ui];
	}

	m_vecText.clear();

}
/**
* 
* Initialises the text which is shown to screen after the game has finished.
* this shows things like number of kills, deaths etc.
* 
* @author Carsten Scholz
* @return bool, returns true if it successfully initialised
*/
bool
CStatistics::Initialise(uint32 _uiTankID)
{
	CRenderEntity::Initialise();

	m_uiTankID = _uiTankID;

	CPlayer* pPlayer = CPlayerManager::GetPlayerManagerInstance().GetPlayer(m_uiTankID);

	int32 iEnemiesKilled = pPlayer->GetTank()->GetEnemiesKilled();

	m_uiTextID = CFontManager::GetInstance().CreateDirect3DFont(20,14,500,false,"OCR A Std");

	CViewport* pViewport = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiTankID);

	int32 iXOffset = pViewport->GetPosX();
    int32 iYOffset = pViewport->GetPosY();

	m_rect.bottom = static_cast<int32>(pViewport->GetHeight() + iYOffset);
	m_rect.top = static_cast<int32>(pViewport->GetHeight() * 0.2f + iYOffset);
	m_rect.right = static_cast<int32>(pViewport->GetWidth() + iXOffset);
	m_rect.left = static_cast<int32>(pViewport->GetWidth() * 0.27f + iXOffset);

	CText* pText = new CText;

	m_strStats[0] = "Player ";
	m_strStats[0] += ToString(m_uiTankID + 1);
	m_strStats[0] += ": ";

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[0].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	m_rect.top += 40;

	pText = new CText;

	m_strStats[1] = "Enemies Killed : ";
	m_strStats[1] += ToString(iEnemiesKilled);

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[1].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	m_rect.top += 40;
	int32 iTeamKilled = pPlayer->GetTank()->GetTeamKills();

	pText = new CText;

	m_strStats[2] = "Team Members Killed : ";
	m_strStats[2] += ToString(iTeamKilled);

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[2].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	m_rect.top += 40;

	int32 iDeaths = pPlayer->GetTank()->GetNumDeaths();

	pText = new CText;

	m_strStats[3] = "Number of Deaths : ";
	m_strStats[3] += ToString(iDeaths);

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[3].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	m_rect.top += 40;

	int32 iFlagsCaptured = pPlayer->GetTank()->NumFlagsCaptured();

	pText = new CText;

	m_strStats[4] = "Number of Flags Captured : ";
	m_strStats[4] += ToString(iFlagsCaptured);

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[4].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	m_rect.top += 40;

	pText = new CText;

	//Gives the player a rating once game is over
	if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) < (iDeaths + 1))
	{
		m_strStats[5] = "Rating : N00b";
	}
	else if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) >= ((iDeaths + 1) * 1.5f) && 
		((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) < ((iDeaths + 1) * 2))
	{
		m_strStats[5] = "Rating : Beginner";
	}
	else if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) >= ((iDeaths + 1) * 2) &&
		((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) < ((iDeaths + 1) * 4))
	{
		m_strStats[5] = "Rating : Amateur";
	}
	else if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) >= ((iDeaths + 1) * 4) &&
		((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) < ((iDeaths + 1) * 6))
	{
		m_strStats[5] = "Rating : Pro";
	}
	else if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) >= ((iDeaths + 1) * 6) &&
		((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) < ((iDeaths + 1) * 20))
	{
		m_strStats[5] = "Rating : 1337!!!";
	}
	else if(((iEnemiesKilled - iTeamKilled) + (iFlagsCaptured * 2)) >= ((iDeaths + 1) * 20))
	{
		m_strStats[5] = "Rating : Carsten-Like";
	}

	pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[5].c_str(), m_uiTextID);
		
	m_vecText.push_back(pText);

	if(m_uiTankID == 0)
	{
		m_rect.top += 80;

		uint32 uiTextID = CFontManager::GetInstance().CreateDirect3DFont(26,17,500,false,"OCR A Std");

		pText = new CText;

		m_strStats[6] = "Press (A) to restart level";

		pText->Initialise(m_rect, DT_TOP | DT_LEFT, 0xffffffff, m_strStats[6].c_str(), uiTextID);
			
		m_vecText.push_back(pText);

		m_rect.left += 80;
	}

	return true;
}
/**
* 
* Draws the text to the screen and displays text for a timer.
* 
* @author Carsten Scholz
* @return void
*/
void
CStatistics::Draw()
{
	for(uint32 ui = 0; ui < m_vecText.size(); ++ui)
	{
		m_vecText[ui]->Draw();
	}
	
	int32 iRoundTimer = 15;

	m_rect.top = static_cast<int32>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiTankID)->GetHeight() * 0.67f) + 
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiTankID)->GetPosY();

	std::string strTime = "Game Ending in : ";
	strTime += ToString(static_cast<int32>((iRoundTimer - m_fCurrentTime)));

	CFontManager::GetInstance().Draw(m_uiTextID, strTime.c_str(), &m_rect, DT_TOP | DT_LEFT, 0xffff0000); 

}
/**
* 
* Process the timer and sets the viewport to draw to.
* 
* @author Carsten Scholz
* @return void
*/
void
CStatistics::Process(float32 _fDeltaTick)
{
	m_fCurrentTime += _fDeltaTick;

	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_SCREENALIGNED | RENDERTYPE_OPAQUE);
	
}
/**
* 
* Gets the time before the game exits
* 
* @author Carsten Scholz
* @return float32 the current time since the function has been initialised
*/
float32
CStatistics::GetExitTime()
{
	return (m_fCurrentTime);
}

