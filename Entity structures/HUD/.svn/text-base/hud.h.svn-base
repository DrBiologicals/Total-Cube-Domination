// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   hud.h
//  Description :   Declaration for Chud
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_HUD_H__
#define __IGFEB10_MODULE_HUD_H__

// Library Includes
#include <d3d9.h>
#include <string>
#include <d3dx9.h>
#include <vector>

// Local Includes
#include "../entity.h"
#include "../../defines.h"

// Types
struct THudRects
{
    RECT m_Src;
    RECT m_Dest;
    bool m_bDrawing;
};

enum EToolTips
{
    TT_MOVE,
    TT_SHOOT,
    TT_AIM,
    TT_GOAL_ROUND,
    TT_GOAL_BASE,
    TT_GOAL_ROUTE,
    TT_GOAL_SCORE,
    TT_GOAL_WIN,
    TT_EMP,
    TT_MINE,
    TT_SCOUT,
    TT_MAX
};

// Prototypes
enum EHudItem;
class CPlayer;

class CHUD : public CRenderEntity
{
	// Member Functions
public:
	CHUD();
	virtual ~CHUD();

	bool Initialise(uint32 _uiPlayerID, uint32 _uiTextureId);
	virtual void Process(float32 _fDeltaTick);
	void Draw();

    void SetToolTips(CPlayer* _pPlayer, float32 _fDeltaTick);

	uint32 GetID();

protected:

private:

	// Member Variables
public:

protected:
	std::vector<uint32> m_vecuiPICsIDs;
	
    // sprite rects
    THudRects m_tHudRects[30];

    // texture
    uint32 m_uiHudTextureID;

    // sprite
    uint32 m_uiSpriteID;

    // player id
    uint32 m_uiPlayerID;

	static uint32 s_uiFontID;
    static uint32 s_uiWinLoseFontID;
    static uint32 s_uiRespawnFontID;
	static uint32 s_uiToolTipID;

    std::string m_strWinOrLose;
	std::string m_strDanger;
    std::string m_strDamagePIC;
    std::string m_strMoveSpeedPIC;
    std::string m_strBulletSpeedPIC;
    std::string m_strShieldPIC;
    std::string m_strRadiusPIC;
    std::string m_strRespawnTimer;
    std::string m_strToolTips[TT_MAX];
	bool m_bRoundOver;

    int32 m_iShieldHeight;
    int32 m_iOverShieldHeight;
    int32 m_iShieldMax;
	int32 m_iScore;
	int32 m_iEnemyScore;

    EHudItem m_eHudItem;
	float32 m_fDangerTimer;

	float32 m_fBlinkTimer;
	float32 m_fBlinkMax;

	D3DXCOLOR m_FadeColor;
	float32 m_fFadeInAndOutTimer;
	float32 m_fFadeMultiplier;
	float32 m_fDisplayTimer;
	float32 m_fCurrentTime;
	int32 m_iCurrentToolTip;
	int32 m_iNextToolTip;
	bool m_bTankMoved;
	bool m_bTankShot;
	bool m_bTankAimed;

private:
	
}; 

#endif // __IGFEB10_MODULE_HUD_H__

