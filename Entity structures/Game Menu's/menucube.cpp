// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menucube.cpp
//  Description :   menucube.cppfor implementation of menucube.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "button.h"
#include "../../Engine/Graphics and sound/modelmanager.h"
#include "../../Engine/Graphics and sound/model.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/Graphics and sound/texture.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/billboardmanager.h"
#include "../../Engine/Graphics and sound/billboard.h"
#include "../../Engine/Graphics and sound/soundmanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../../Engine/Input/input.h"
#include "../../Engine/input/inputhandler.h"
#include "../../Engine/Game/menustate.h"
#include "text.h"
#include "../../Engine/Graphics and sound/fontmanager.h"
#include "../../Engine/viewport/viewport.h"

// This Includes

#include "menucube.h"

// Static Variables
uint32 CMenuCube::s_uiModelID = BAD_ID;
uint32 CMenuCube::s_uiTextureID = BAD_ID;

// Static Function Prototypes

// Implementation

CMenuCube::CMenuCube()
: m_eMenuSelect(MENU_OPTION_PLAY)
, m_bTransition(false)
, m_uiRightArrowBillboard(BAD_ID)
, m_uiLeftArrowBillboard(BAD_ID)
, m_uiRightArrowTexture(BAD_ID)
, m_uiLeftArrowTexture(BAD_ID)
, m_pLeftArrowText(0)
, m_pRightArrowText(0)
, m_uiFontID(0)
, m_uiSoundLeft(BAD_ID)
, m_uiSoundRight(BAD_ID)
, m_uiSoundAccept(BAD_ID)
, m_uiSoundBack(BAD_ID)
{
}

CMenuCube::~CMenuCube()
{
	delete m_pLeftArrowText;
	m_pLeftArrowText = 0;

	delete m_pRightArrowText;
	m_pRightArrowText = 0;
}

/*
* Initialise
* @author Michael McQuarrie
* 
* @return bool
*/
bool
CMenuCube::Initialise(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiRightArrowBillboard,
					uint32 _uiLeftArrowBillboard, uint32 _uiRightArrowTexture, uint32 _uiLeftArrowTexture,
					uint32 _uiFontID, uint32 _uiSoundLeftID, uint32 _uiSoundRightID, uint32 _uiSoundAcceptID,
					uint32 _uiSoundBackID)
{
	//Normal Initialise stuff for menus
	CMenuItem::Initialise();

	D3DXMatrixIdentity(&m_matWorld);

	if(BAD_ID == s_uiModelID)
	{
		s_uiModelID = _uiModelID;
	}

	if(BAD_ID == s_uiTextureID)
	{
		s_uiTextureID = _uiTextureID;
	}

	m_uiFontID = _uiFontID;

	m_uiRightArrowBillboard = _uiRightArrowBillboard;
	m_uiLeftArrowBillboard = _uiLeftArrowBillboard;

	m_uiSoundLeft = _uiSoundLeftID;
	m_uiSoundRight = _uiSoundRightID;
	m_uiSoundAccept = _uiSoundAcceptID;
	m_uiSoundBack = _uiSoundBackID;

	RECT rect;
	rect.bottom = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()
								->GetViewport(0)->GetHeight()*0.68f);
	rect.top = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()
								->GetViewport(0)->GetHeight()*0.48f);
	rect.right = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetWidth()*0.95f);
	rect.left = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetWidth()*0.75f);

	m_strTextOptions.push_back("Play");
	m_strTextOptions.push_back("Exit");
	m_strTextOptions.push_back("Controls");
	m_strTextOptions.push_back("Credits");

	if(0 == m_pRightArrowText)
	{
		m_pRightArrowText = new CText;
	}
	m_pRightArrowText->Initialise(rect, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0),
							m_strTextOptions[MENU_OPTION_INSTRUCTIONS].c_str(), m_uiFontID);

	rect.right = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetWidth()*0.255f);
	rect.left = static_cast<LONG>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetWidth()*0.055f);

	if(0 == m_pLeftArrowText)
	{
		m_pLeftArrowText = new CText;
	}
	m_pLeftArrowText->Initialise(rect, DT_CENTER, D3DCOLOR_XRGB(0, 0, 0),
							m_strTextOptions[MENU_OPTION_EXIT].c_str(), m_uiFontID);

	return(true);
}

/*
* Process
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CMenuCube::Process(float32 _fDeltaTick)
{
	if(true == m_bIsActive)
	{
		// Check controller ID is the first active controller.
		if(false == IsControllerActive())
		{
			UpdateControllerID();
		}

		// If controller is active, process normal functionality.
		if(true == IsControllerActive())
		{
			//Process the cube moving animations if any
			//First check if its spinning
			if (m_TargetAngle.GetAngle() == m_CurrentAngle.GetAngle())
			{
				m_bTransition = false;

				// TEMP!
				if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_SELECT, m_uiControllerID))
				{
					MenuSelect();
					CSoundManager::GetInstance().PlaySound(m_uiSoundAccept);
				}
				if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVELEFT, m_uiControllerID) < -0.9f)
				{
					m_bTransition = true;

					ChangeMenuOption(false);

					CSoundManager::GetInstance().GetSound(m_uiSoundLeft);
					CSoundManager::GetInstance().PlaySound(m_uiSoundLeft);

					m_TargetAngle.SetAngle(m_TargetAngle.GetAngle() - D3DXToRadian(90.0f));
				}
				else if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVERIGHT, m_uiControllerID) > 0.9f)
				{
					m_bTransition = true;
					ChangeMenuOption(true);

					CSoundManager::GetInstance().PlaySound(m_uiSoundRight);

					m_TargetAngle.SetAngle(m_TargetAngle.GetAngle() + D3DXToRadian(90.0f));
				}
				else
				{
					m_pLeftArrowText->Process(_fDeltaTick);
					m_pRightArrowText->Process(_fDeltaTick);
				}
			}
			else
			{
				m_bTransition = true;

				m_CurrentAngle.TurnTowardsAngle(m_TargetAngle, _fDeltaTick * MENU_CUBE_TURN_SPEED);
			}

			D3DXMatrixRotationY(&m_matWorld, m_CurrentAngle.GetAngle());
		}
				
		//Add to the viewport
		CTotalCubeDomination::GetInstance().GetRenderer()->AddToViewport(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE, 0);
	}
}

/*
* Draw
* @author Michael McQuarrie
* 
* @return void
*/
void
CMenuCube::Draw()
{
	// Grab the renderer.
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);

	//Draw it
	CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
	CModelManager::GetInstance().Draw(s_uiModelID);

	if(!m_bTransition)
	{
        pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		CBillboardManager::GetInstance().Draw(m_uiRightArrowBillboard);

		CBillboardManager::GetInstance().Draw(m_uiLeftArrowBillboard);

        pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	    pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		m_pRightArrowText->Draw();
		m_pLeftArrowText->Draw();
	}
}

void
CMenuCube::MenuSelect()
{
	if(MENU_OPTION_PLAY == m_eMenuSelect)
	{
		m_bIsAdvancing = true;
	}
	if(MENU_OPTION_INSTRUCTIONS == m_eMenuSelect)
	{
		//Instructions
		dynamic_cast<CMenuState*>(CTotalCubeDomination::GetInstance().GetProgramState())
									->SetActiveMenu(INSTRUCTIONS_MENU);
	}
	if(MENU_OPTION_CREDITS == m_eMenuSelect)
	{
		//Credits
		dynamic_cast<CMenuState*>(CTotalCubeDomination::GetInstance().GetProgramState())
									->SetActiveMenu(CREDITS_MENU);
	}
	if(MENU_OPTION_EXIT == m_eMenuSelect)
	{
		PostQuitMessage(0);
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
CMenuCube::Reset()
{
	Initialise(s_uiModelID, s_uiTextureID, m_uiRightArrowBillboard, m_uiLeftArrowBillboard,
				m_uiRightArrowTexture, m_uiLeftArrowTexture, m_uiFontID, m_uiSoundLeft,
				m_uiSoundRight, m_uiSoundAccept, m_uiSoundBack);
}

void
CMenuCube::ChangeMenuOption(bool _bToRight)
{
	switch(m_eMenuSelect)
	{
		case MENU_OPTION_PLAY:
		{
			if(true == _bToRight)
			{
				SetCurrentMenu(MENU_OPTION_INSTRUCTIONS);
			}
			else // to left
			{
				SetCurrentMenu(MENU_OPTION_EXIT);
			}
			break;
		}
		case MENU_OPTION_EXIT:
		{
			if(true == _bToRight)
			{
				SetCurrentMenu(MENU_OPTION_PLAY);
			}
			else // to left
			{
				SetCurrentMenu(MENU_OPTION_CREDITS);
			}
			break;
		}
		case MENU_OPTION_INSTRUCTIONS:
		{
			if(true == _bToRight)
			{
				SetCurrentMenu(MENU_OPTION_CREDITS);
			}
			else // to left
			{
				SetCurrentMenu(MENU_OPTION_PLAY);
			}
			break;
		}
		case MENU_OPTION_CREDITS:
		{
			if(true == _bToRight)
			{
				SetCurrentMenu(MENU_OPTION_EXIT);
			}
			else // to left
			{
				SetCurrentMenu(MENU_OPTION_INSTRUCTIONS);
			}
			break;
		}
		default:break;
	}
}

void
CMenuCube::SetCurrentMenu(EMenuOption _eMenu)
{
	m_eMenuSelect = _eMenu;

	switch(m_eMenuSelect)
	{
		case MENU_OPTION_PLAY:
		{
			m_pRightArrowText->SetText(m_strTextOptions[MENU_OPTION_INSTRUCTIONS].c_str());
			m_pLeftArrowText->SetText(m_strTextOptions[MENU_OPTION_EXIT].c_str());
			break;
		}
		case MENU_OPTION_INSTRUCTIONS:
		{
			m_pRightArrowText->SetText(m_strTextOptions[MENU_OPTION_CREDITS].c_str());
			m_pLeftArrowText->SetText(m_strTextOptions[MENU_OPTION_PLAY].c_str());
			break;
		}
		case MENU_OPTION_CREDITS:
		{
			m_pRightArrowText->SetText(m_strTextOptions[MENU_OPTION_EXIT].c_str());
			m_pLeftArrowText->SetText(m_strTextOptions[MENU_OPTION_INSTRUCTIONS].c_str());
			break;
		}
		case MENU_OPTION_EXIT:
		{
			m_pRightArrowText->SetText(m_strTextOptions[MENU_OPTION_PLAY].c_str());
			m_pLeftArrowText->SetText(m_strTextOptions[MENU_OPTION_CREDITS].c_str());
			break;
		}
		default:break;
	}
}
