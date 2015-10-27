// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   pausemenu.cpp
//  Description :   pausemenu.cppfor implementation of pausemenu.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/spritemanager.h"
#include "../../engine/graphics and sound/sprite.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/totalcubedomination.h"
#include "../../engine/viewport/viewport.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/game/gamestate.h"

// This Includes
#include "pausescreen.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPauseScreen::CPauseScreen()
: m_uiSpriteID(BAD_ID)
, m_uiTextureID(BAD_ID)
{
}

CPauseScreen::~CPauseScreen()
{
}

/*
* This function intialises the pause menu 
* @author Rigardt de Vries
* @param _uiBillBoardID					the ID of the pause screen billbaird
* @param _uiTextureID					the ID of the texture for the billboard
* @return true if successfull
*/
bool
CPauseScreen::Initialise(uint32 _uiTextureID)
{
	m_uiTextureID = _uiTextureID;

	RECT rect;
    SetRectEmpty(&rect);
	m_uiSpriteID =  CSpriteManager::GetInstance().CreateSprite(_uiTextureID, &rect);

	return (true);
}

/*
* processes the pause screen
* @author Rigardt de Vries
* @param _fDeltaTick				the game timer
* @return void
*/
void
CPauseScreen::Process(float32 _fDeltaTick)
{
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_ALPHABLEND | RENDERTYPE_SCREENALIGNED);
}

/*
* Draws the pause screen
* @author Rigardt
*
*/
void
CPauseScreen::Draw()
{
	if (dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())->GetPause() == false)
	{
		return;
	}

	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
	CViewport* pViewport = pRenderer->GetViewport(0);

	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);
	RECT rect;
	uint32 uiDistanceFromEdge = 50 / pRenderer->GetNumViewports();

	uint32 uiXOffset = pViewport->GetPosX();
	uint32 uiYOffset = pViewport->GetPosY();

	rect.top = 0;
	rect.left = 0;
	rect.bottom = 1024;
	rect.right = 1024;
	CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->SetSourceRect(rect);
	rect.top = 0;
	rect.left = 0;
	rect.bottom = pRenderer->GetScreenHeight();
	rect.right = pRenderer->GetScreenWidth();
	CSpriteManager::GetInstance().GetSprite(m_uiSpriteID)->Draw(rect);

	pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}