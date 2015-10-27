// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   hud.cpp
//  Description :   hud.cppfor implementation of hud.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../Player Objects/tank.h"
#include "../Player Objects/playermanager.h"
#include "../Player Objects/player.h"
#include "../terrain objects/flag.h"
#include "../terrain objects/flagplate.h"
#include "../terrain objects/cube.h"
#include "../../igutils.h"
#include "../../defines.h"
#include "../../Engine/graphics and sound/renderer.h"
#include "../../Engine/Viewport/viewport.h"
#include "../../Engine/Totalcubedomination.h"
#include "../../Engine/Game/gamestate.h"
#include "../../Engine/Game/rules.h"
#include "../../Engine/graphics and sound/fontmanager.h"
#include "../../Engine/graphics and sound/spritemanager.h"
#include "../../Engine/graphics and sound/sprite.h"
#include "../../Engine/graphics and sound/texturemanager.h"

// This Includes
#include "hud.h"

// Static Variables
uint32 CHUD::s_uiFontID = BAD_ID;
uint32 CHUD::s_uiWinLoseFontID = BAD_ID;
uint32 CHUD::s_uiRespawnFontID = BAD_ID;
uint32 CHUD::s_uiToolTipID = BAD_ID;

// Static Function Prototypes
enum EHudItem
{
    HUD_SHIELD_BACK,
    HUD_SHIELD_BLUE,
    HUD_SHIELD_ORANGE,
    HUD_LEFT_BAR,
    HUD_RIGHT_BAR,
    HUD_EMP_ONE,
    HUD_EMP_TWO,
    HUD_EMP_THREE,
    HUD_PURPLE_LIGHT_ON,
    HUD_GREEN_LIGHT_ON,
    HUD_MINE,
    HUD_EXTRA_BAR_LEFT,
    HUD_EXTRA_BAR_RIGHT,
    HUD_NUM_ZERO,
    HUD_NUM_ONE,
    HUD_NUM_TWO,
    HUD_NUM_THREE,
    HUD_TOOL_TIP,
	HUD_GREEN_SCORE1,
	HUD_GREEN_SCORE2,
	HUD_GREEN_SCORE3,
	HUD_PURPLE_SCORE1,
	HUD_PURPLE_SCORE2,
	HUD_PURPLE_SCORE3,
    HUD_MAX

};

const float32 KIDISPLAYTIME = 3.5f;

// Implementation

CHUD::CHUD()
: m_uiSpriteID(BAD_ID)
, m_uiHudTextureID(BAD_ID)
, m_uiPlayerID(0)
, m_iOverShieldHeight(0)
, m_iShieldHeight(0)
, m_strWinOrLose("")
, m_strBulletSpeedPIC("")
, m_strDamagePIC("")
, m_strMoveSpeedPIC("")
, m_strRadiusPIC("")
, m_strShieldPIC("")
, m_strRespawnTimer("")
, m_strDanger("")
, m_iShieldMax(0)
, m_eHudItem(HUD_MAX)
, m_iScore(0)
, m_iEnemyScore(0)
, m_bRoundOver(false)
, m_bTankMoved(false)
, m_bTankAimed(false)
, m_bTankShot(false)
, m_iCurrentToolTip(TT_MOVE)
, m_iNextToolTip(TT_MAX)
, m_fFadeInAndOutTimer(0.01f)
, m_fFadeMultiplier(2.0f)
, m_fDisplayTimer(0.0f)
, m_fCurrentTime(0.0f)
, m_fDangerTimer(0.0f)
, m_fBlinkTimer(0.0f)
, m_fBlinkMax(0.5f)
{
    memset(&m_tHudRects, false, sizeof(m_tHudRects) );
	m_FadeColor = 0xFFCCCCCC;
}

CHUD::~CHUD()
{
    s_uiFontID = BAD_ID;
    s_uiWinLoseFontID = BAD_ID;
    s_uiRespawnFontID = BAD_ID;
	s_uiToolTipID = BAD_ID;
}
/*
* 
* @author Michael McQuarrie
* 
* @return true when done
*/
bool
CHUD::Initialise(uint32 _uiPlayerID, uint32 _uiTextureId)
{
	m_uiPlayerID = _uiPlayerID;

	if (s_uiFontID == BAD_ID)
	{
		s_uiFontID = CFontManager::GetInstance().CreateDirect3DFont(20, 8, 500, false, "Arial");
	}
	if (s_uiWinLoseFontID == BAD_ID)
	{
		s_uiWinLoseFontID = CFontManager::GetInstance().CreateDirect3DFont(60, 30, 500, false, "Arial");
	}
    if (s_uiRespawnFontID == BAD_ID)
    {
        s_uiRespawnFontID = CFontManager::GetInstance().CreateDirect3DFont(200, 80, 1000, false, "Arial");
    }
	if (s_uiToolTipID == BAD_ID)
	{
		s_uiToolTipID = CFontManager::GetInstance().CreateDirect3DFont(20, 10, 400, false, "Arial");
	}

    CViewport* pViewport = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID);

    int32 iXOffset = pViewport->GetPosX();
    int32 iYOffset = pViewport->GetPosY();

    m_uiHudTextureID = _uiTextureId;

    // LEFT_HAND_BAR
    m_tHudRects[3].m_Src.left = 1;      m_tHudRects[3].m_Dest.left = 0 + iXOffset;
    m_tHudRects[3].m_Src.top = 1;       m_tHudRects[3].m_Dest.top = 0 + iYOffset; 
    m_tHudRects[3].m_Src.right = 41;    m_tHudRects[3].m_Dest.right = 41 + iXOffset;
    m_tHudRects[3].m_Src.bottom = 384;  m_tHudRects[3].m_Dest.bottom = 384 + iYOffset;

    // RIGHT_HAND_BAR
    m_tHudRects[4].m_Src.left = 43;     m_tHudRects[4].m_Dest.left = (pViewport->GetWidth() - 41) + iXOffset;
    m_tHudRects[4].m_Src.top = 1;       m_tHudRects[4].m_Dest.top = 0 + iYOffset;
    m_tHudRects[4].m_Src.right = 82;    m_tHudRects[4].m_Dest.right = pViewport->GetWidth() + iXOffset;    
    m_tHudRects[4].m_Src.bottom = 384;  m_tHudRects[4].m_Dest.bottom = 384 + iYOffset;

    // EMP_ONE
    m_tHudRects[5].m_Src.left = 84;     m_tHudRects[5].m_Dest.left = 0 + iXOffset;
    m_tHudRects[5].m_Src.top = 1;       m_tHudRects[5].m_Dest.top = 224 + iYOffset;
    m_tHudRects[5].m_Src.right = 124;   m_tHudRects[5].m_Dest.right = 40 + iXOffset;
    m_tHudRects[5].m_Src.bottom = 26;   m_tHudRects[5].m_Dest.bottom = 251 + iYOffset;

    // EMP_TWO
    m_tHudRects[6].m_Src.left = 84;     m_tHudRects[6].m_Dest.left = 0 + iXOffset;
    m_tHudRects[6].m_Src.top = 1;       m_tHudRects[6].m_Dest.top = 253 + iYOffset;
    m_tHudRects[6].m_Src.right = 124;   m_tHudRects[6].m_Dest.right = 40 + iXOffset;
    m_tHudRects[6].m_Src.bottom = 26;   m_tHudRects[6].m_Dest.bottom = 280 + iYOffset;

     // EMP_THREE
    m_tHudRects[7].m_Src.left = 84;     m_tHudRects[7].m_Dest.left = 0 + iXOffset;
    m_tHudRects[7].m_Src.top = 1;       m_tHudRects[7].m_Dest.top = 282 + iYOffset;
    m_tHudRects[7].m_Src.right = 124;   m_tHudRects[7].m_Dest.right = 40 + iXOffset;
    m_tHudRects[7].m_Src.bottom = 26;   m_tHudRects[7].m_Dest.bottom = 309 + iYOffset;

    // PURPLE_LIGHT_ON
    m_tHudRects[8].m_Src.left = 83;     m_tHudRects[8].m_Dest.left = (pViewport->GetWidth()) - 40 + iXOffset;
    m_tHudRects[8].m_Src.top = 244;     m_tHudRects[8].m_Dest.top = 113 + iYOffset;
    m_tHudRects[8].m_Src.right = 123;   m_tHudRects[8].m_Dest.right = pViewport->GetWidth() + iXOffset;
    m_tHudRects[8].m_Src.bottom = 281;  m_tHudRects[8].m_Dest.bottom = 151 + iYOffset;

    // GREEN_LIGHT_ON
    m_tHudRects[9].m_Src.left = 83;     m_tHudRects[9].m_Dest.left = (pViewport->GetWidth() - 40) + iXOffset;
    m_tHudRects[9].m_Src.top = 204;     m_tHudRects[9].m_Dest.top = 75 + iYOffset;
    m_tHudRects[9].m_Src.right = 123;   m_tHudRects[9].m_Dest.right = pViewport->GetWidth() + iXOffset;
    m_tHudRects[9].m_Src.bottom = 241;  m_tHudRects[9].m_Dest.bottom = 115 + iYOffset;

    // SHIELD_BACK
    m_tHudRects[0].m_Src.left = 83;     m_tHudRects[0].m_Dest.left = 1 + iXOffset;
    m_tHudRects[0].m_Src.top = 61;      m_tHudRects[0].m_Dest.top = 46 + iYOffset;
    m_tHudRects[0].m_Src.right = 121;   m_tHudRects[0].m_Dest.right = 39 + iXOffset;
    m_tHudRects[0].m_Src.bottom = 201;  m_tHudRects[0].m_Dest.bottom = 186 + iYOffset;
    m_iShieldMax = m_tHudRects[0].m_Dest.bottom - m_tHudRects[0].m_Dest.top;
    m_iShieldHeight = m_iShieldMax;

    // SHIELD_REGULAR_BAR
    m_tHudRects[1].m_Src.left = 122;    m_tHudRects[1].m_Dest.left = 1 + iXOffset;
    m_tHudRects[1].m_Src.top = 61;      m_tHudRects[1].m_Dest.top = 46 + iYOffset;
    m_tHudRects[1].m_Src.right = 160;   m_tHudRects[1].m_Dest.right = 39 + iXOffset;
    m_tHudRects[1].m_Src.bottom = 201;  m_tHudRects[1].m_Dest.bottom = 186 + iYOffset;

    // SHIELD_OVERSHIELD_BAR
    m_tHudRects[2].m_Src.left = 161;    m_tHudRects[2].m_Dest.left = 1 + iXOffset;
    m_tHudRects[2].m_Src.top = 61;      m_tHudRects[2].m_Dest.top = 46 + iYOffset;
    m_tHudRects[2].m_Src.right = 199;   m_tHudRects[2].m_Dest.right = 39 + iXOffset;
    m_tHudRects[2].m_Src.bottom = 201;  m_tHudRects[2].m_Dest.bottom =186 + iYOffset;

    // MINE
    m_tHudRects[10].m_Src.left = 84;     m_tHudRects[10].m_Dest.left = 0 + iXOffset;
    m_tHudRects[10].m_Src.top = 29;      m_tHudRects[10].m_Dest.top = 188 + iYOffset;
    m_tHudRects[10].m_Src.right = 124;   m_tHudRects[10].m_Dest.right = 41 + iXOffset;
    m_tHudRects[10].m_Src.bottom = 60;   m_tHudRects[10].m_Dest.bottom = 220 + iYOffset;

    // LEFT EXTRA BAR
    m_tHudRects[11].m_Src.left = 84;       m_tHudRects[11].m_Dest.left = 0 + iXOffset;
    m_tHudRects[11].m_Src.top = 283;        m_tHudRects[11].m_Dest.top = 383 + iYOffset;
    m_tHudRects[11].m_Src.right = 124;      m_tHudRects[11].m_Dest.right = 41 + iXOffset;
    m_tHudRects[11].m_Src.bottom = 367;     m_tHudRects[11].m_Dest.bottom = pViewport->GetHeight() + iYOffset;

    // RIGHT EXTRA BAR
    m_tHudRects[12].m_Src.left = 126;       m_tHudRects[12].m_Dest.left = (pViewport->GetWidth() - 41) + iXOffset;;
    m_tHudRects[12].m_Src.top = 283;        m_tHudRects[12].m_Dest.top = 383 + iYOffset;
    m_tHudRects[12].m_Src.right = 165;      m_tHudRects[12].m_Dest.right = pViewport->GetWidth() + iXOffset;
    m_tHudRects[12].m_Src.bottom = 367;     m_tHudRects[12].m_Dest.bottom = pViewport->GetHeight() + iYOffset;

	// Tool Tip box
    m_tHudRects[17].m_Src.left = 119;      m_tHudRects[17].m_Dest.left = (pViewport->GetWidth() >> 2) + iXOffset;
    m_tHudRects[17].m_Src.top = 199;       m_tHudRects[17].m_Dest.top = (pViewport->GetHeight() - 95) + iYOffset;
    m_tHudRects[17].m_Src.right = 120;     m_tHudRects[17].m_Dest.right = (pViewport->GetWidth() - (pViewport->GetWidth() >> 2)) + iXOffset;
    m_tHudRects[17].m_Src.bottom = 200;    m_tHudRects[17].m_Dest.bottom = (pViewport->GetHeight() - 50) + iYOffset;

	// HUD_GREEN_SCORE1
	m_tHudRects[HUD_GREEN_SCORE1].m_Src.left = 125;      m_tHudRects[HUD_GREEN_SCORE1].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE1].m_Src.top = 239;       m_tHudRects[HUD_GREEN_SCORE1].m_Dest.top = 195 + iYOffset;
    m_tHudRects[HUD_GREEN_SCORE1].m_Src.right = 140;     m_tHudRects[HUD_GREEN_SCORE1].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE1].m_Src.bottom = 250;    m_tHudRects[HUD_GREEN_SCORE1].m_Dest.bottom = 206 + iYOffset;

	// HUD_GREEN_SCORE2
	m_tHudRects[HUD_GREEN_SCORE2].m_Src.left = 125;      m_tHudRects[HUD_GREEN_SCORE2].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE2].m_Src.top = 239;       m_tHudRects[HUD_GREEN_SCORE2].m_Dest.top = 207 + iYOffset;
    m_tHudRects[HUD_GREEN_SCORE2].m_Src.right = 140;     m_tHudRects[HUD_GREEN_SCORE2].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE2].m_Src.bottom = 250;    m_tHudRects[HUD_GREEN_SCORE2].m_Dest.bottom = 218 + iYOffset;

	// HUD_GREEN_SCORE3
	m_tHudRects[HUD_GREEN_SCORE3].m_Src.left = 125;      m_tHudRects[HUD_GREEN_SCORE3].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE3].m_Src.top = 239;       m_tHudRects[HUD_GREEN_SCORE3].m_Dest.top = 219 + iYOffset;
    m_tHudRects[HUD_GREEN_SCORE3].m_Src.right = 140;     m_tHudRects[HUD_GREEN_SCORE3].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_GREEN_SCORE3].m_Src.bottom = 250;    m_tHudRects[HUD_GREEN_SCORE3].m_Dest.bottom = 230 + iYOffset;

	// HUD_PURPLE_SCORE1
	m_tHudRects[HUD_PURPLE_SCORE1].m_Src.left = 125;      m_tHudRects[HUD_PURPLE_SCORE1].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE1].m_Src.top = 203;       m_tHudRects[HUD_PURPLE_SCORE1].m_Dest.top = 183 + iYOffset;
    m_tHudRects[HUD_PURPLE_SCORE1].m_Src.right = 140;     m_tHudRects[HUD_PURPLE_SCORE1].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE1].m_Src.bottom = 214;    m_tHudRects[HUD_PURPLE_SCORE1].m_Dest.bottom = 194 + iYOffset;

	// HUD_PURPLE_SCORE2
	m_tHudRects[HUD_PURPLE_SCORE2].m_Src.left = 125;      m_tHudRects[HUD_PURPLE_SCORE2].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE2].m_Src.top = 203;       m_tHudRects[HUD_PURPLE_SCORE2].m_Dest.top = 171 + iYOffset;
    m_tHudRects[HUD_PURPLE_SCORE2].m_Src.right = 140;     m_tHudRects[HUD_PURPLE_SCORE2].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE2].m_Src.bottom = 214;    m_tHudRects[HUD_PURPLE_SCORE2].m_Dest.bottom = 182 + iYOffset;

	// HUD_PURPLE_SCORE3
	m_tHudRects[HUD_PURPLE_SCORE3].m_Src.left = 125;      m_tHudRects[HUD_PURPLE_SCORE3].m_Dest.left = (pViewport->GetWidth() -27) + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE3].m_Src.top = 203;       m_tHudRects[HUD_PURPLE_SCORE3].m_Dest.top = 160 + iYOffset;
    m_tHudRects[HUD_PURPLE_SCORE3].m_Src.right = 140;     m_tHudRects[HUD_PURPLE_SCORE3].m_Dest.right = pViewport->GetWidth() -12 + iXOffset;
    m_tHudRects[HUD_PURPLE_SCORE3].m_Src.bottom = 214;    m_tHudRects[HUD_PURPLE_SCORE3].m_Dest.bottom = 171 + iYOffset;



    for (int32 i = 0; i < 22; ++i)
    {
        m_tHudRects[i].m_bDrawing = true;
    }

    RECT rect;
    SetRectEmpty(&rect);
    m_uiSpriteID = CSpriteManager::GetInstance().CreateSprite(m_uiHudTextureID, &rect);

	m_strToolTips[TT_MOVE]          = "Left analogue to move.";
    m_strToolTips[TT_SHOOT]         = "Right trigger to shoot.";
    m_strToolTips[TT_AIM]           = "Right analogue to aim your turret.";
    m_strToolTips[TT_GOAL_ROUND]    = "Your goal is to capture\n your enemies flag.";
    m_strToolTips[TT_GOAL_BASE]     = "Their base is on the\n opposite side to yours.";
    m_strToolTips[TT_GOAL_ROUTE]    = "Move around the cube\n to find them.";
    m_strToolTips[TT_GOAL_SCORE]    = "You must have both \n flags to score.";
    m_strToolTips[TT_GOAL_WIN]      = "First team to three points\n win the game.";
    m_strToolTips[TT_EMP]           = "Right bumper to shoot EMP.";
    m_strToolTips[TT_MINE]          = "Left bumper to drop mine.";
    m_strToolTips[TT_SCOUT]         = "Left trigger to scout.";

	CEntity::Initialise();

	return (true);
}

/*
* 
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void 
CHUD::Process(float32 _fDeltatick)
{
    CGameState* pGameState = dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState());
    CPlayer* pPlayer = CPlayerManager::GetPlayerManagerInstance().GetPlayer(m_uiPlayerID);

    SetToolTips(pPlayer, _fDeltatick);
	m_strRespawnTimer = "";
	m_strDanger = "";

	//This is a timer to flash danger when the player is down to less than half shield
	if(pPlayer->GetTank()->GetCurrentShield() <= pPlayer->GetTank()->GetMaxShield() / 2.0f)
	{
		m_fDangerTimer += _fDeltatick;
		if(m_fDangerTimer >= 0.5f)
		{
			m_strDanger = "DANGER!!!";
			if(m_fDangerTimer >= 2.0f)
			{
				m_fDangerTimer = 0.0f;
			}
		}
	}

    if(!pPlayer->GetTank()->GetAlive())
    {
		
         // get the respawn timer.
        m_strRespawnTimer = ToString(static_cast<int32>(pPlayer->GetRespawnTimer()) );
        CTotalCubeDomination::GetInstance().GetRenderer()->AddToViewport(this, RENDERTYPE_SCREENALIGNED | RENDERTYPE_ALPHABLEND, m_uiPlayerID);
		m_bRoundOver = false;
		
		if(pGameState->GetRules()->GetScore(pPlayer->GetTank()->GetTeam()) > m_iScore)
		{
			m_bRoundOver = true;
			m_strRespawnTimer = "Round Won";
		}
		if(pPlayer->GetTank()->GetTeam() == TEAM_GREEN)
		{
			if(pGameState->GetRules()->GetScore(TEAM_PURPLE) > m_iEnemyScore)
			{
				m_bRoundOver = true;
				m_strRespawnTimer = "Round Lost";
			}
		}
		if(pPlayer->GetTank()->GetTeam() == TEAM_PURPLE)
		{
			if(pGameState->GetRules()->GetScore(TEAM_GREEN) > m_iEnemyScore)
			{
				m_bRoundOver = true;
				m_strRespawnTimer = "Flag Lost";
			}
		}
		return;
    }

    m_iScore = pGameState->GetRules()->GetScore(pPlayer->GetTank()->GetTeam());
	if(pPlayer->GetTank()->GetTeam() == TEAM_GREEN)
	{
		m_iEnemyScore = pGameState->GetRules()->GetScore(TEAM_PURPLE);
	}
	else
	{
		m_iEnemyScore = pGameState->GetRules()->GetScore(TEAM_GREEN);
	}

    m_tHudRects[HUD_EMP_ONE].m_bDrawing = false;
    m_tHudRects[HUD_EMP_TWO].m_bDrawing = false;
    m_tHudRects[HUD_EMP_THREE].m_bDrawing = false;

    switch (pPlayer->GetTank()->GetEMPCount())
    {
    case 3:
        {
            m_tHudRects[HUD_EMP_THREE].m_bDrawing = true;
        }
    case 2:
        {
            m_tHudRects[HUD_EMP_TWO].m_bDrawing = true;
        }
    case 1:
        {
            m_tHudRects[HUD_EMP_ONE].m_bDrawing = true;
        }
        break;
    case 0:
        {
            m_tHudRects[HUD_EMP_ONE].m_bDrawing = false;
            m_tHudRects[HUD_EMP_TWO].m_bDrawing = false;
            m_tHudRects[HUD_EMP_THREE].m_bDrawing = false;
        }
        break;
    }
    
    if (pPlayer->GetTank()->GetMineCool() == false)
    {
        m_tHudRects[HUD_MINE].m_bDrawing = false;
    }
    else
    {
        m_tHudRects[HUD_MINE].m_bDrawing = true;
    }

    if (pPlayer->GetTank()->GetCurrentOverShield() == 0.0f)
    {
        m_tHudRects[HUD_SHIELD_ORANGE].m_bDrawing = false;
    }
    else
    {
        m_iOverShieldHeight = static_cast<int32>(m_iShieldMax * pPlayer->GetTank()->GetCurrentOverShield() / pPlayer->GetTank()->GetMaxOverShield());
        m_tHudRects[HUD_SHIELD_ORANGE].m_bDrawing = true;
        m_tHudRects[HUD_SHIELD_ORANGE].m_Dest.top = m_tHudRects[HUD_SHIELD_ORANGE].m_Dest.bottom - m_iOverShieldHeight;
    }

    if (pPlayer->GetTank()->GetCurrentShield() == 0.0f)
    {
        m_tHudRects[HUD_SHIELD_BLUE].m_bDrawing = false;
    }
    else
    {
        m_iShieldHeight = static_cast<int32>(m_iShieldMax * pPlayer->GetTank()->GetCurrentShield() / pPlayer->GetTank()->GetMaxShield());
        m_tHudRects[HUD_SHIELD_BLUE].m_bDrawing = true;
        m_tHudRects[HUD_SHIELD_BLUE].m_Dest.top = m_tHudRects[HUD_SHIELD_BLUE].m_Dest.bottom - m_iShieldHeight;
    }

	m_fBlinkTimer += _fDeltatick;
    m_tHudRects[HUD_GREEN_LIGHT_ON].m_bDrawing = false;
    m_tHudRects[HUD_PURPLE_LIGHT_ON].m_bDrawing = false;
	CCube* pCube = CCube::GetCube();
	if(pCube)
	{
		CFlagPlate* pFlagPlate = pCube->GetFlagPlate(TEAM_GREEN);
		if(!pFlagPlate->HasFlag())
		{
			CFlag* pFlag = pCube->GetFlag(TEAM_GREEN);
			if(pFlag->GetFlagPickedUp())
			{
				//blink
				if(m_fBlinkTimer>m_fBlinkMax)
				{
					if(m_fBlinkTimer<m_fBlinkMax*2)
					{
						m_tHudRects[HUD_GREEN_LIGHT_ON].m_bDrawing = true;
					}
				}
			}
			else
			{
				m_tHudRects[HUD_GREEN_LIGHT_ON].m_bDrawing = true;
			}
		}
		pFlagPlate = pCube->GetFlagPlate(TEAM_PURPLE);
		if(!pFlagPlate->HasFlag())
		{
			CFlag* pFlag = pCube->GetFlag(TEAM_PURPLE);
			if(pFlag->GetFlagPickedUp())
			{
				//blink
				if(m_fBlinkTimer>m_fBlinkMax)
				{
					if(m_fBlinkTimer<m_fBlinkMax*2)
					{
						m_tHudRects[HUD_PURPLE_LIGHT_ON].m_bDrawing = true;
					}
				}
			}
			else
			{
				m_tHudRects[HUD_PURPLE_LIGHT_ON].m_bDrawing = true;
			}
		}
	}
	if(m_fBlinkTimer>m_fBlinkMax*2)
	{
		m_fBlinkTimer = 0.0f;
	}

    if (pGameState->GetRules()->GetScore(TEAM_GREEN ) == 3) 
    {
		m_fCurrentTime += _fDeltatick;

		if(m_fCurrentTime < 3.0f)
		{
			if (pPlayer->GetTeam() == TEAM_GREEN )
			{
				m_strWinOrLose = "VICTORY!!";
			}
			else
			{
				m_strWinOrLose = "DEFEAT!!";
			}
		}
		else
		{
			m_strWinOrLose = "";
		}
    }
    else if (pGameState->GetRules()->GetScore(TEAM_PURPLE ) == 3)
    {
		m_fCurrentTime += _fDeltatick;

		if(m_fCurrentTime < 3.0f)
		{
			if (pPlayer->GetTeam() == TEAM_GREEN )
			{
				m_strWinOrLose = "DEFEAT!!";
			}
			else
			{
				m_strWinOrLose = "VICTORY!!";
			}
		}
		else
		{
			m_strWinOrLose = "";
		}
    }
    
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToViewport(this, RENDERTYPE_SCREENALIGNED | RENDERTYPE_ALPHABLEND, m_uiPlayerID);
}

/*
* 
* @author Michael McQuarrie
* 
* @return void
*/
void 
CHUD::Draw()
{
    RECT rect;
    DWORD dwColour;
    dwColour = ((CPlayerManager::GetPlayerManagerInstance().GetPlayer(m_uiPlayerID)->GetTank()->GetTeam() == TEAM_GREEN)?(0xFF00FF00):(0xFFFF00FF));
    CPlayer* pPlayer = CPlayerManager::GetPlayerManagerInstance().GetPlayer(m_uiPlayerID);

	CViewport* pViewport = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID);
    CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// The respawn timer
    // if the tank is dead
    if (!pPlayer->GetTank()->GetAlive())
    {
		if(m_bRoundOver)
		{
			//Drawing round over things
			rect.top = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosY();
			rect.bottom = rect.top + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetHeight() - 5;
			rect.left = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosX();
			rect.right = rect.left + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetWidth();
			CFontManager::GetInstance().Draw(s_uiWinLoseFontID, m_strRespawnTimer.c_str(), &rect, DT_VCENTER | DT_CENTER, dwColour);
		}
		else
		{
			//Drawing the respawn
			rect.top = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosY();
			rect.bottom = rect.top + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetHeight() - 5;
			rect.left = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosX();
			rect.right = rect.left + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetWidth();
			CFontManager::GetInstance().Draw(s_uiRespawnFontID, m_strRespawnTimer.c_str(), &rect, DT_TOP | DT_CENTER, dwColour);
		}
    
        return ;
    }

	// Tool Tip text
    if (!(m_iNextToolTip == TT_MAX && m_fFadeInAndOutTimer == 0.0f))
    {  
        pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

        CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->SetSourceRect(m_tHudRects[HUD_TOOL_TIP].m_Src);
        CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->Draw(m_tHudRects[HUD_TOOL_TIP].m_Dest);

        pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
        pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

        rect.bottom = (pViewport->GetHeight() - 49) + pViewport->GetPosY();
	    rect.top = (pViewport->GetHeight() - 94) + pViewport->GetPosY();
	    rect.left = (pViewport->GetWidth() >> 2) + pViewport->GetPosX();
	    rect.right = (pViewport->GetWidth() - (pViewport->GetWidth() >> 2)) + pViewport->GetPosX();
	    CFontManager::GetInstance().Draw(s_uiToolTipID, m_strToolTips[m_iCurrentToolTip].c_str(), &rect, DT_VCENTER | DT_CENTER, m_FadeColor);
    }

	// Victory and defeat text
    rect.top = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosY();
	rect.bottom = rect.top + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetHeight() - 5;
    rect.left = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetPosX();
	rect.right = rect.left + CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(m_uiPlayerID)->GetWidth();
    CFontManager::GetInstance().Draw(s_uiWinLoseFontID, m_strWinOrLose.c_str(), &rect, DT_VCENTER | DT_CENTER, dwColour);

    LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	// the hud images
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    for (int32 i = 0; i < 13; ++i)
    {
        if (m_tHudRects[i].m_bDrawing)
        {
            CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->SetSourceRect(m_tHudRects[i].m_Src);
            CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->Draw(m_tHudRects[i].m_Dest);
        }
    }

	CGameState* pGameState = dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState());
	CRules* pRules = pGameState->GetRules();
	int32 iGreenScore = pRules->GetScore(TEAM_GREEN);
	int32 iPurpleScore = pRules->GetScore(TEAM_PURPLE);

	CSprite* pSprite = CSpriteManager::GetInstance().GetSprite(m_uiSpriteID);
	pSprite->SetSourceRect(m_tHudRects[HUD_GREEN_SCORE1].m_Src);
	switch(iGreenScore)
	{
	case 3:
        pSprite->Draw(m_tHudRects[HUD_GREEN_SCORE3].m_Dest);
	case 2:
		pSprite->Draw(m_tHudRects[HUD_GREEN_SCORE2].m_Dest);
	case 1:
		pSprite->Draw(m_tHudRects[HUD_GREEN_SCORE1].m_Dest);
		break;
	default:
		break;
	}
	pSprite->SetSourceRect(m_tHudRects[HUD_PURPLE_SCORE1].m_Src);
	switch(iPurpleScore)
	{
	case 3:
       pSprite->Draw(m_tHudRects[HUD_PURPLE_SCORE3].m_Dest);
	case 2:
		pSprite->Draw(m_tHudRects[HUD_PURPLE_SCORE2].m_Dest);
	case 1:
		pSprite->Draw(m_tHudRects[HUD_PURPLE_SCORE1].m_Dest);
		break;
	default:
		break;
	}

    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

uint32
CHUD::GetID()
{
	return (m_uiPlayerID);
}

/*
* This draws the tool tip for the player.
* @author Rigardt de Vries
* @param _pPlayer               the target player.
* @return void
*/
void
CHUD::SetToolTips(CPlayer *_pPlayer, float32 _fDeltaTick)
{
   	// Set the tank.
	CTank* pTank = _pPlayer->GetTank();

	if (!pTank->GetAlive())
	{
		return ;
	}

    if (m_iNextToolTip == TT_MAX && m_fFadeInAndOutTimer == 0.0f)
    {
        return ;
    }

	// check if tank has aimed
	if (pTank->HasAimed() == false)
	{
		// Chheck if the tank has moved.
		if (pTank->HasMoved() == false)
		{
			// set the next tool tip to the move one.
			m_iNextToolTip = TT_MOVE;
		}
		// if tank has moved
		else
		{
			// check the fade multiplier and the has moved
			if (m_fFadeMultiplier > 0.0f && !m_bTankMoved)
			{
				// flip the multiplier.
				m_fFadeMultiplier *= -1.0f;
				m_bTankMoved = true;
			}

			// check of the tank has shot
			if (pTank->HasShot() == false)
			{
				// set the next tool tip to the shoot one.
				m_iNextToolTip = TT_SHOOT;
			}
			// if player has shot.
			else
			{
				// check the fade multiplier and has shot
				if (m_fFadeMultiplier > 0.0f && !m_bTankShot)
				{
					// flip the multiplier
					m_fFadeMultiplier *= -1.0f;
					m_bTankShot = true;
				}
				
				// Set the next tool tip to the aim one.
				m_iNextToolTip = TT_AIM;
			}
		}
	}
	else
	{
		// check the fade multiplier and has aimed
		if (m_fFadeMultiplier > 0.0f && !m_bTankAimed)
		{
			// flip the multiplier
			m_fFadeMultiplier *= -1.0f;
			m_bTankAimed = true;
		}
	}

	// change the fade in and out timer.
	m_fFadeInAndOutTimer += _fDeltaTick * m_fFadeMultiplier;

	// check if the timer is lessthan or equal to zero.
	if (m_fFadeInAndOutTimer <= 0.0f)
	{
		// set the timer to zero and flip the multiplier.
		m_fFadeInAndOutTimer = 0.0f;
		m_fFadeMultiplier *= -1.0f;

		// check if the tank has aimed.
		if (pTank->HasAimed() == true)
		{
			// check that the next tool tip is not the max tool tip.
			if (m_iNextToolTip != TT_MAX)
			{
				// increment the next tool tip.
				++m_iNextToolTip; 
			}
		}

        // set the current tool tip to the next tool tip.
		m_iCurrentToolTip = m_iNextToolTip;
	}
	// check if the fade timer is greater than or equal to one.
	else if (m_fFadeInAndOutTimer >= 1.0f)
	{
		// set the timer to one.
		m_fFadeInAndOutTimer = 1.0f;

		// check if the tank has aimed.
		if (pTank->HasAimed() == true)
		{
			// increment the display timer by the game timer.
			m_fDisplayTimer += _fDeltaTick;

			// check that the display timer hasn't reach it's end yet.
			if (m_fDisplayTimer >= KIDISPLAYTIME)
			{
				// flip the multiplier.
				m_fFadeMultiplier *= -1.0f;

				// reset the display timer;
				m_fDisplayTimer = 0.0f;
			}
		}
	}

	// set the alpha.
	m_FadeColor.a = m_fFadeInAndOutTimer;
}