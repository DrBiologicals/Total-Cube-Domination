// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menustate.cpp
//  Description :   menustate.cppfor implementation of menustate.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes
#include <fstream>

// Local Includes
#include "../totalcubedomination.h"
#include "../viewport/viewport.h"
#include "../viewport/camera.h"
#include "../../igutils.h"
#include "../../Entity structures/Game Menu's/menucube.h"
#include "../../Entity structures/Game Menu's/text.h"
#include "../graphics and sound/renderer.h"
#include "../Graphics and sound/texturemanager.h"
#include "../Graphics and sound/modelmanager.h"
#include "../Graphics and sound/fontmanager.h"
#include "../Graphics and sound/billboardmanager.h"
#include "../Graphics and sound/soundmanager.h"
#include "../Graphics and sound/spritemanager.h"
#include "../Graphics and sound/lightmanager.h"
#include "../../entity structures/player objects/playermanager.h"
#include "../../entity structures/particle/emittermanager.h"
#include "menu.h"
#include "../../entity structures/game menu's/playerselector.h"
#include "../input/input.h"
#include "../input/inputhandler.h"
#include "../../entity structures/entitymanager.h"
#include "../graphics and sound/lightmanager.h"
#include "../../entity structures/game menu's/staticgraphic.h"
#include "../../entity structures/game menu's/list.h"
#include "../../entity structures/game menu's/levelpreview.h"
#include "../../Engine/Game/gamestate.h"
#include "../graphics and sound/texturemanager.h"
#include "../graphics and sound/modelmanager.h"
#include "../../entity structures/game menu's/button.h"
#include "../../dirent.h"

// This Includes
#include "menustate.h"

// Static Variables
std::string CMenuState::s_strSelectedMap = "";

// Static Function Prototypes

// Implementation
CMenuState::CMenuState()
: m_eActiveMenu(MAIN_MENU)
, m_fBackgroundWidth(0.0f)
, m_fBackgroundHeight(0.0f)
, m_fBackgroundDistance(0.0f)
, m_iDifficulty(0)
, m_fCurrentTime(0.0f)
, m_uiMusic(BAD_ID)
, m_uiBackgroundBillboardID(BAD_ID)
, m_uiBackgroundTextureID(BAD_ID)
, m_vec2CenterPosition(0.0f,0.0f)
{
	memset(m_apMenus, 0, sizeof(m_apMenus));
}

CMenuState::~CMenuState()
{
	for (int32 i = 0; i < MENU_MAX; ++i)
	{
		delete m_apMenus[i];
	}

	memset(m_apMenus, 0, sizeof(m_apMenus));
}

/**
* 
* This function calls clear on all the managers, set up a camera and one viewport. Initilises the
* function needed for all menu items and sets a ambient light on the menu.
*
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::Initialise()
{
    CFontManager::GetInstance().Clear();
	CTextureManager::GetInstance().Clear();
	CModelManager::GetInstance().Clear();
	CLightManager::GetInstance().Clear();
    CBillboardManager::GetInstance().ClearManager();
    CSoundManager::GetInstance().Clear();
    CSpriteManager::GetInstance().Clear();
    CPlayerManager::GetPlayerManagerInstance().DestroyPlayers();
    CEmitterManager::GetInstance().Clear();

	// Set viewport.
	uint32 uiNumViewports = 1;

	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
    pRenderer->SetNumViewports(uiNumViewports);
#ifdef _DEBUG
	pRenderer->GetViewport(0)->CreateCamera(D3DXToRadian(45), 0.1f, 100);
#else
	uint32 uiCamID1 = pRenderer->GetViewport(0)->CreateCamera(D3DXToRadian(45), 0.1f, 100);
#endif // _DEBUG

	// Set background size/distance for the billboards to use.
	m_fBackgroundWidth = static_cast<float32>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)
											->GetWidth());
	m_fBackgroundHeight = static_cast<float32>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)
											->GetHeight());
	m_vec2CenterPosition = D3DXVECTOR2(m_fBackgroundWidth*0.5f, m_fBackgroundHeight*0.5f);
	m_iDifficulty = 0;

	if(m_uiMusic==BAD_ID)
	{
		m_uiMusic = CSoundManager::GetInstance().CreateSound("sounds/music/soundtrack_one.mp3",0.5f,true);
	}

	// Background.
	m_uiBackgroundTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MainMenuBackground.png");
	m_uiBackgroundBillboardID = CBillboardManager::GetInstance().CreateBillboard(m_uiBackgroundTextureID,
										m_fBackgroundWidth, m_fBackgroundHeight, m_vec2CenterPosition);

	// Create camera.
	VALIDATE(CreateMainMenu());
	VALIDATE(CreatePlayerSelectMenu());
	VALIDATE(CreateInstructions());
	VALIDATE(CreateCredits());
	VALIDATE(CreateLevelSelect());
	VALIDATE(CreateDifficultyMenu());

	// Keep this in please!
	SetActiveMenu(MAIN_MENU);

	D3DLIGHT9 light;
    ZeroMemory(&light, sizeof(light) );
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Ambient.b = 1.0f;
    light.Ambient.r = 1.0f;
    light.Ambient.g = 1.0f;
    light.Ambient.a = 1.0f;
    light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

    uint32 uiAmbientLightID = CLightManager::GetInstance().CreateLight(light);
    CLightManager::GetInstance().SetLightActive(uiAmbientLightID, true);

	CSoundManager::GetInstance().PlaySound(m_uiMusic);

	m_fCurrentTime = 0.0f;

	return (true);
}

/*
* 
* 
* @param float32 _fDeltaTick
* @return void 
*/
void
CMenuState::Process(float32 _fDeltaTick)
{
	m_apMenus[m_eActiveMenu]->Process(_fDeltaTick);

	// Check to see if the current menu needs to change, and set it to the 
	// next appropriate menu.
	CheckForMenuChange(_fDeltaTick);
#ifdef _DEBUG
//	m_pOwner->GetRenderer()->Process(_fDeltaTick);
#endif //_DEBUG
}

/**
* 
* Sets the current active menu (and all menu items in it) to false.
* Sets the new menu passed in to active (inc. items).
* 
* author Rebeccah Cox
* @param EMenu _eMenu
* @return void 
*/
void
CMenuState::SetActiveMenu(EMenu _eMenu)
{
	for(uint32 i = 0; i < CTotalCubeDomination::GetInstance().GetRenderer()->GetNumViewports(); ++i)
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(i)->ClearRenderQueue();
	}

	// Set current active menu to not active.
	m_apMenus[m_eActiveMenu]->SetMenuItemsToActive(false);

	// Set new active menu.
	m_eActiveMenu = _eMenu;

	for(uint32 uiItem = 0; uiItem < m_apMenus[m_eActiveMenu]->GetNumberOfMenuItems(); ++uiItem)
	{
		m_apMenus[m_eActiveMenu]->GetMenuItem(uiItem)->Reset();
	}
	
	m_apMenus[m_eActiveMenu]->SetMenuItemsToActive(true);

	if(DIFFICULTY_MENU == m_eActiveMenu)
	{
		m_apMenus[m_eActiveMenu]->GetMenuItem(3)->SetActive(false);
		m_apMenus[m_eActiveMenu]->GetMenuItem(4)->SetActive(false);
	}

	// Move camera back when in main menu.
	if(MAIN_MENU == m_eActiveMenu || LEVEL_SELECT_MENU == m_eActiveMenu)
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetCamera(0)
			->SetView3D(D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0, -30));
	}
	else
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetCamera(0)
			->SetView3D(D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0, 0));
	}
}

/**
* 
* Checks if player one has pressed the back key, to go back to the main menu.
* 
* @author Rebeccah Cox
* @return void 
*/
void
CMenuState::CheckButtonPresses()
{
	// If exit button (back) is held:
	if(true == CInputHandler::GetInstance().IsControlTriggered(CONTROL_EXIT, 0))
	{
		// Go straight to main menu.
		SetActiveMenu(MAIN_MENU);
	}
}
/**
* 
* This function initialises the Main Menu Cube Class, which is shown after the logo's have appeared.
* with this menu cube the player can choose 4 different options, from Play,Exit,Controls and Credits.
* 
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::CreateMainMenu()
{
	m_apMenus[MAIN_MENU] = new CMenu;
	CMenuCube* pMenuCube = new CMenuCube;

	// Create textures.
	uint32 uiModelID = CModelManager::GetInstance().CreateModel("models/menu_cube.x");
	uint32 uiTextureID = CTextureManager::GetInstance().CreateTexture("textures/menu_cube.png");

	uint32 uiRightArrowTexture = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MenuArrowRight.png");
	uint32 uiLeftArrowTexture = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MenuArrowLeft.png");

	// Create billboards.
	D3DXVECTOR2 vecArrowPosition = D3DXVECTOR2(m_fBackgroundWidth*0.15f, m_fBackgroundHeight*0.5f);
	uint32 uiLeftArrowBillboard = CBillboardManager::GetInstance().CreateBillboard(uiLeftArrowTexture,
									m_fBackgroundWidth*0.25f, m_fBackgroundHeight*0.25f, vecArrowPosition);

	vecArrowPosition.x = m_fBackgroundWidth*0.85f;
	uint32 uiRightArrowBillboard = CBillboardManager::GetInstance().CreateBillboard(uiRightArrowTexture,
									m_fBackgroundWidth*0.25f, m_fBackgroundHeight*0.25f, vecArrowPosition);

	// Create menu items.
	uint32 uiMenuItemCount = 0;

	// Create background with a CStaticGraphic object.
	CStaticGraphic* pBackgroundGraphic = new CStaticGraphic();

	uint32 uiFontID = CFontManager::GetInstance().CreateDirect3DFont(static_cast<int32>(m_fBackgroundHeight*0.034f),
						static_cast<int32>(m_fBackgroundWidth*0.016f),500,false,"Arial");
	CSoundManager& rSoundManager = CSoundManager::GetInstance();
	uint32 uiSoundLeftID = rSoundManager.CreateSound("sounds/sfx/menu_left.wav");
	uint32 uiSoundRightID = rSoundManager.CreateSound("sounds/sfx/menu_right.wav");
	uint32 uiSoundAcceptID = rSoundManager.CreateSound("sounds/sfx/menu_accept.wav");
	uint32 uiSoundBackID = rSoundManager.CreateSound("sounds/sfx/menu_back.wav");
	
	uint32 uiBackgroundTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MenuBackground_SelectOnly.png");
	uint32 uiBackgroundID = CBillboardManager::GetInstance().CreateBillboard(uiBackgroundTextureID,
								m_fBackgroundWidth, m_fBackgroundHeight, m_vec2CenterPosition);
	pBackgroundGraphic->Initialise(uiBackgroundID);

	m_apMenus[MAIN_MENU]->AddMenuItem(pBackgroundGraphic);
	++uiMenuItemCount;

	VALIDATE(pMenuCube->Initialise(uiModelID, uiTextureID, uiRightArrowBillboard, uiLeftArrowBillboard,
				uiRightArrowTexture, uiLeftArrowTexture, uiFontID, uiSoundLeftID, uiSoundRightID,
				uiSoundAcceptID, uiSoundBackID));

	m_apMenus[MAIN_MENU]->AddMenuItem(pMenuCube);
	m_apMenus[MAIN_MENU]->SetMenuCubeID(uiMenuItemCount);
	++uiMenuItemCount;

	return (true);
}

/**
* 
* Creates and initialises a new CMenu object, and the four CPlayerSelector
*	objects that it contains.
* 
* @author Rebeccah Cox
* @return bool
*/
bool
CMenuState::CreatePlayerSelectMenu()
{
	const float32 fSizeMultiplier = 0.39f;
	uint32 uiMenuItemCount = 0;

	// Instantiate player select menu.
	m_apMenus[PLAYER_SELECT_MENU] = new CMenu;
	m_apMenus[PLAYER_SELECT_MENU]->Initialise();

	// Create background with a CStaticGraphic object.
	CStaticGraphic* pBackgroundGraphic = new CStaticGraphic();

	pBackgroundGraphic->Initialise(m_uiBackgroundBillboardID);
	m_apMenus[PLAYER_SELECT_MENU]->AddMenuItem(pBackgroundGraphic);
	++uiMenuItemCount;

	// Textures.
	uint32 uiNotConnectedTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/ConnectController.png");
	uint32 uiJoinGameTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/PressAToJoin.png");
	uint32 uiSelectTeamTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/TeamSelectionNotReady.png");
	uint32 uiGreenTeamTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/TeamGreen.png");
	uint32 uiPurpleTeamTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/TeamPurple.png");
	uint32 uiReadyTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/TeamSelectionReady.png");

	// Create and add the four player select boxes.
	uint32 uiControllerID = 0;
	CPlayerSelector* pTempSelector = 0;

	// Player selector position.
	float32 fXOffset = m_fBackgroundWidth*0.215f;
	float32 fYOffset = -(m_fBackgroundHeight*0.205f);

	D3DXVECTOR2 vec2Position = D3DXVECTOR2(0.0f, 0.0f);

	for(uint32 uiSelector = 0; uiSelector < 4; ++uiSelector)
	{
		pTempSelector = new CPlayerSelector();

		fXOffset *= -1.0f;

		if(2 == uiSelector)
		{
			fYOffset *= -1.0f;
		}

		vec2Position = D3DXVECTOR2((m_fBackgroundWidth*0.5f)+fXOffset, (m_fBackgroundHeight*0.48f)+fYOffset);

		// Player selector billboards.
		uint32 uiNotConnectedBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiNotConnectedTextureID,
										m_fBackgroundWidth*fSizeMultiplier, m_fBackgroundHeight*fSizeMultiplier,
										vec2Position);

		uint32 uiJoinGameBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiJoinGameTextureID,
										m_fBackgroundWidth*fSizeMultiplier, m_fBackgroundHeight*fSizeMultiplier,
										vec2Position);

		uint32 uiSelectTeamBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiSelectTeamTextureID,
										m_fBackgroundWidth*fSizeMultiplier, m_fBackgroundHeight*fSizeMultiplier,
										vec2Position);

		uint32 uiGreenTeamBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiGreenTeamTextureID,
										m_fBackgroundWidth*fSizeMultiplier*0.3f, m_fBackgroundHeight*fSizeMultiplier*0.5f,
										vec2Position);

		uint32 uiPurpleTeamBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiPurpleTeamTextureID,
										m_fBackgroundWidth*fSizeMultiplier*0.3f, m_fBackgroundHeight*fSizeMultiplier*0.5f,
										vec2Position);

		uint32 uiReadyBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiReadyTextureID,
										m_fBackgroundWidth*fSizeMultiplier, m_fBackgroundHeight*fSizeMultiplier,
										vec2Position);

		// Initialise player selector.
		pTempSelector->Initialise(uiControllerID++, uiNotConnectedBillboardID, uiJoinGameBillboardID,
									uiSelectTeamBillboardID, uiGreenTeamBillboardID, uiPurpleTeamBillboardID,
									uiReadyBillboardID);
		m_apMenus[PLAYER_SELECT_MENU]->AddMenuItem(pTempSelector);
		m_apMenus[PLAYER_SELECT_MENU]->SetPlayerSelectorID(uiMenuItemCount);
		++uiMenuItemCount;
	}

	pTempSelector = 0;

	return (true);
}

/**
* 
* Runs different checks depending on the current menu state.
* eg. the PLAYER_SELECT_MENU checks if all of the player selector objects have
*		chosen a team, then calls ChangeCurrentMenu() and passes in LEVEL_SELECT_MENU.
* 
* @author Rebeccah Cox
* @return void
*/
void
CMenuState::CheckForMenuChange(float32 _fDeltaTick)
{
	switch(m_eActiveMenu)
	{
		case MAIN_MENU:
		{
			if(true == m_apMenus[MAIN_MENU]->GetMenuItem(m_apMenus[MAIN_MENU]->GetMenuCubeID())->IsAdvancing())
			{
				SetActiveMenu(PLAYER_SELECT_MENU);
			}
			else if(true == m_apMenus[MAIN_MENU]->GetMenuItem(m_apMenus[MAIN_MENU]->GetMenuCubeID())->IsAdvancing())
			{
			}
			break;
		}

		case PLAYER_SELECT_MENU:
		{
			// Check for change request.
			// Iterate through menu items.
			for(uint32 iIndex = 0; iIndex < m_apMenus[PLAYER_SELECT_MENU]->GetNumberOfMenuItems(); ++iIndex)
			{
				if(true == m_apMenus[PLAYER_SELECT_MENU]->IsAPlayerSelectorID(iIndex))
				{
					// If the menu item is a CPlayerSelector, and is exiting, set MAIN_MENU to active.
					if(true == m_apMenus[PLAYER_SELECT_MENU]->GetMenuItem(iIndex)->IsExiting()
						&& true == m_apMenus[PLAYER_SELECT_MENU]->IsAPlayerSelectorID(iIndex))
					{
						SetActiveMenu(MAIN_MENU);
						break;
					}
				}
			}

			// Change the screen to level select if all of the connected players
			// have chosen teams.
			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_SELECT, 0))
			{
				if(true == HavePlayersChosenTeams())
				{
					SetActiveMenu(DIFFICULTY_MENU);
				}
			}
			break;
		}

		case LEVEL_SELECT_MENU:
		{
			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_BACK, 0))
			{
				SetActiveMenu(DIFFICULTY_MENU);
			}

			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_SELECT, 0))
			{
                int32 iMapIndex = dynamic_cast<CList*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(3))->Select();
				s_strSelectedMap = m_vecMapStrings[iMapIndex];

				CTotalCubeDomination::GetInstance().ChangeToGameState();
			}
            m_fCurrentTime += _fDeltaTick;

            if(m_fCurrentTime > 0.1f)
			{
                m_fCurrentTime = 0.0f;
				
                if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEUP, 0) > 0)
                {
                    dynamic_cast<CList*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(3))->MoveUpList();
					int iMapIndex = dynamic_cast<CList*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(3))->Select();
					dynamic_cast<CLevelPreviewer*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(2))->LoadMap(m_vecMapStrings[iMapIndex].c_str());
                }
                if (CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEDOWN, 0) < 0)
                {
                    dynamic_cast<CList*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(3))->MoveDownList();
					int iMapIndex = dynamic_cast<CList*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(3))->Select();
					dynamic_cast<CLevelPreviewer*>(m_apMenus[LEVEL_SELECT_MENU]->GetMenuItem(2))->LoadMap(m_vecMapStrings[iMapIndex].c_str());
                }
            }
			break;
		}

		case INSTRUCTIONS_MENU:
		{
			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_BACK, 0))
			{
				SetActiveMenu(MAIN_MENU);
			}
			break;
		}

		case CREDITS_MENU:
		{
			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_BACK, 0))
			{
				SetActiveMenu(MAIN_MENU);
			}
			break;
		}
		case DIFFICULTY_MENU:
		{
			m_fCurrentTime += _fDeltaTick;

			if(m_iDifficulty == 1)
			{
					dynamic_cast<CText*>(m_apMenus[m_eActiveMenu]->GetMenuItem(m_apMenus[m_eActiveMenu]
						->GetTextID()))->SetText("Friendly Fire ENABLED");

					m_apMenus[m_eActiveMenu]->GetMenuItem(1)->SetActive(false);
					m_apMenus[m_eActiveMenu]->GetMenuItem(2)->SetActive(false);
					m_apMenus[m_eActiveMenu]->GetMenuItem(3)->SetActive(true);
					m_apMenus[m_eActiveMenu]->GetMenuItem(4)->SetActive(true);
			}
			else
			{
					dynamic_cast<CText*>(m_apMenus[m_eActiveMenu]->GetMenuItem(m_apMenus[m_eActiveMenu]
						->GetTextID()))->SetText("Friendly Fire DISABLED");

					m_apMenus[m_eActiveMenu]->GetMenuItem(1)->SetActive(true);
					m_apMenus[m_eActiveMenu]->GetMenuItem(2)->SetActive(true);
					m_apMenus[m_eActiveMenu]->GetMenuItem(3)->SetActive(false);
					m_apMenus[m_eActiveMenu]->GetMenuItem(4)->SetActive(false);
			}

			if(m_fCurrentTime > 0.2f)
			{

				if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEUP, 0) < -0.7f)
				{
					m_iDifficulty -= 1;

					m_fCurrentTime = 0;

					if(m_iDifficulty < 0)
					{
						m_iDifficulty = 1;
					}
				}
				if(CInputHandler::GetInstance().GetControlMagnitude(CONTROL_MOVEDOWN, 0) > 0.7f)
				{
					m_iDifficulty += 1;

					m_fCurrentTime = 0;

					if(m_iDifficulty > 1)
					{
						m_iDifficulty = 0;
					}
				}
			}

			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_SELECT, 0))
			{
				CProgramState::SetDifficulty(m_iDifficulty);
				SetActiveMenu(LEVEL_SELECT_MENU);
			}
			if(CInputHandler::GetInstance().IsControlTriggered(CONTROL_BACK, 0))
			{
				SetActiveMenu(PLAYER_SELECT_MENU);
			}		
			break;
		}
		default:break;
	}
}

/**
* 
* Checks if all of the players have either chosen teams, or are not connected.
* NOTE: Player one must be connected.
* 
* @author Rebeccah Cox
* @return bool - true if all four player selector objects have acceptable values.
*/
bool
CMenuState::HavePlayersChosenTeams()
{
	uint32 iPlayersAdvancing = 0;
    uint32 iNumJoinedGame = 0;
	uint32 iPlayersChecked = 0;

	// Iterate through menu items.
	for(uint32 iIndex = 0; iIndex < m_apMenus[PLAYER_SELECT_MENU]->GetNumberOfMenuItems(); ++iIndex)
	{
		// If the menu item is a player selector object:
		if(true == m_apMenus[PLAYER_SELECT_MENU]->IsAPlayerSelectorID(iIndex))
		{
			if(true == m_apMenus[PLAYER_SELECT_MENU]->GetMenuItem(iIndex)->IsBeingUsed())
            {
                ++iNumJoinedGame;
            }
			++iPlayersChecked;

			if(true == m_apMenus[PLAYER_SELECT_MENU]->GetMenuItem(iIndex)->IsAdvancing())
			{
				++iPlayersAdvancing;
			}

			// If four player selectors have been checked, return true.
			if(m_apMenus[PLAYER_SELECT_MENU]->GetNumPlayerSelectors() == iPlayersChecked)
			{
				if(0 == iPlayersAdvancing)
				{
					return (false);
				}

                if(iPlayersAdvancing == iNumJoinedGame)
                {
				    // Set the number of human players.
				    CProgramState::SetNumPlayer(iPlayersAdvancing);
				    return (true);
                }
			}
		}
	}

	// All player selector objects that are being used are not ready yet.
	return (false);
}
/**
* 
* This function Initialises the billboard and textures used for the instructions menu,
* used to show the player how to play.
*
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::CreateInstructions()
{
	// Create background.
	CStaticGraphic* pStatGraphic = new CStaticGraphic;

	uint32 uiBackgroundTextureID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MenuBackground.png");
	uint32 uiBackgroundBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiBackgroundTextureID,
										m_fBackgroundWidth, m_fBackgroundHeight, m_vec2CenterPosition);
	pStatGraphic->Initialise(uiBackgroundBillboardID);

	m_apMenus[INSTRUCTIONS_MENU] = new CMenu;
	m_apMenus[INSTRUCTIONS_MENU]->Initialise();

	m_apMenus[INSTRUCTIONS_MENU]->AddMenuItem(pStatGraphic);

	// Create instructions.
	pStatGraphic = new CStaticGraphic;

	uint32 uiTextureInstructID = CTextureManager::GetInstance().CreateTexture("textures/Instuctions.png");

	uint32 uiInstructionsID = CBillboardManager::GetInstance().CreateBillboard(uiTextureInstructID,
							m_fBackgroundWidth*0.85f, m_fBackgroundHeight*0.85f, m_vec2CenterPosition);

	pStatGraphic->Initialise(uiInstructionsID);

	m_apMenus[INSTRUCTIONS_MENU]->AddMenuItem(pStatGraphic);

	return (true);
}
/**
* 
* This function Initialises the billboard and textures used for the Credits Menu,
* Credits is used to show who all made the game.
*
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::CreateCredits()
{
	CStaticGraphic* pStatGraphic = new CStaticGraphic;

	uint32 uiTextureCreditsID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/Credits.png");

	uint32 uiCreditsID = CBillboardManager::GetInstance().CreateBillboard(uiTextureCreditsID,
							m_fBackgroundWidth, m_fBackgroundHeight, m_vec2CenterPosition);

	VALIDATE(pStatGraphic->Initialise(uiCreditsID));

	m_apMenus[CREDITS_MENU] = new CMenu;
	m_apMenus[CREDITS_MENU]->Initialise();

	m_apMenus[CREDITS_MENU]->AddMenuItem(pStatGraphic);


	return (true);
}
/**
* 
* This function Initialises the billboard and textures used for the backgroud of the 
* level select menu, then calls initialise on the levelselect class
*
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::CreateLevelSelect()
{
    CViewport* pViewport = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0);

	// create background
	CStaticGraphic* pStatGraphic = new CStaticGraphic;
	
	VALIDATE(pStatGraphic->Initialise(m_uiBackgroundBillboardID));

	// create list
    CList* pList = new CList;
	pList->Initialise(D3DXVECTOR2(pViewport->GetWidth()*0.2f, pViewport->GetHeight() * 0.5f));
    pList->LoadAssets();

	DIR* pDirectory = 0;
	dirent* pEntry = 0;

	pDirectory = opendir("./maps/");
 
	while ((pEntry = readdir(pDirectory)) != 0)
	{
		std::string String = pEntry->d_name;

		if (String.substr(String.find_last_of('.'), String.size() - String.find_last_of('.')) == ".tcd")
		{
			std::ifstream MapStream;

			String = "./maps/";
			String += pEntry->d_name;

			MapStream.open(String.c_str());

			if (!MapStream.good()) continue;

			char acName[32];

			MapStream.read(acName, 32);

			MapStream.close();

			CButton* pButton = pList->Addbutton();
			pButton->Initialise(BAD_ID);
			pButton->SetMapName(acName);

			m_vecMapStrings.push_back(String);
		}
	}

	// make menu
	m_apMenus[LEVEL_SELECT_MENU] = new CMenu;
	m_apMenus[LEVEL_SELECT_MENU]->Initialise();

	// add background
	m_apMenus[LEVEL_SELECT_MENU]->AddMenuItem(pStatGraphic);

	// create select box
	pStatGraphic = new CStaticGraphic;
	
	uint32 uiTextureCreditsID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/MapSelectBox.png");
	uint32 uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiTextureCreditsID,
							m_fBackgroundWidth*0.2f, m_fBackgroundHeight*0.053f,
							D3DXVECTOR2(pViewport->GetWidth()*0.25f, pViewport->GetHeight()*0.5f));

	VALIDATE(pStatGraphic->Initialise(uiBillboardID));

	// add slect box
	m_apMenus[LEVEL_SELECT_MENU]->AddMenuItem(pStatGraphic);

	// create level previewer
	CLevelPreviewer* pLevelPreview = new CLevelPreviewer;

	VALIDATE(pLevelPreview->Initialise(D3DXVECTOR3(8.0f,0.0f,10.0f)));

	// and levelpreviewer and list
	m_apMenus[LEVEL_SELECT_MENU]->AddMenuItem(pLevelPreview);
    m_apMenus[LEVEL_SELECT_MENU]->AddMenuItem(pList);

	if (!m_vecMapStrings.empty())
		pLevelPreview->LoadMap(m_vecMapStrings[0].c_str());

	// create text
	CText* pText = new CText;

	uint32 uiFontID = CFontManager::GetInstance().CreateDirect3DFont(static_cast<int32>(m_fBackgroundHeight*0.035f),
						static_cast<int32>(m_fBackgroundWidth*0.016f),500,false,"Verdana");

	RECT rect;

	rect.bottom = pViewport->GetHeight();
	rect.top = static_cast<int32>(pViewport->GetHeight() * 0.1f);
	rect.right = pViewport->GetWidth();
	rect.left = static_cast<int32>(pViewport->GetWidth() * 0.1f);

	pText->Initialise(rect, DT_TOP | DT_LEFT, 0xffffffff, "Select Map", uiFontID);

	closedir(pDirectory);

	// add text
	m_apMenus[LEVEL_SELECT_MENU]->AddMenuItem(pText);

	return (true);
}
/**
* 
* This function Initialises the billboard and textures used for the backgroud of the 
* difficulty menu, it also initialises buttons which switch places when selected.
*
* @author Carsten Scholz
* @return bool, return trues if the initialisation was successful
*/
bool
CMenuState::CreateDifficultyMenu()
{
	uint32 uiMenuItemCount = 0;
	CStaticGraphic* pStatGraphic = new CStaticGraphic;

	pStatGraphic->Initialise(m_uiBackgroundBillboardID);

	m_apMenus[DIFFICULTY_MENU] = new CMenu;
	m_apMenus[DIFFICULTY_MENU]->Initialise(4);
	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pStatGraphic);
	++uiMenuItemCount;

	// Positions for buttons.
	D3DXVECTOR2 vec2TopPosition = D3DXVECTOR2(m_fBackgroundWidth*0.5f,m_fBackgroundHeight*0.4f);
	D3DXVECTOR2 vec2BottomPosition = D3DXVECTOR2(m_fBackgroundWidth*0.5f,m_fBackgroundHeight*0.6f);

	//////////
	CButton* pButton = 0;

	uint32 uiTextureInstructID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/NormalModeSelected.png");
	uint32 uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiTextureInstructID,
							m_fBackgroundWidth * 0.5f, m_fBackgroundHeight * 0.15f, vec2TopPosition);

	pButton = new CButton;

	pButton->Initialise(uiBillboardID);

	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pButton);
	m_apMenus[DIFFICULTY_MENU]->SetButtonID(uiMenuItemCount++);

	/////////
	uiTextureInstructID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/HardcoreModeNotSelected.png");
	uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiTextureInstructID, m_fBackgroundWidth * 0.5f,
						m_fBackgroundHeight * 0.1f, vec2BottomPosition);

	pButton = new CButton;

	pButton->Initialise(uiBillboardID);

	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pButton);
	m_apMenus[DIFFICULTY_MENU]->SetButtonID(uiMenuItemCount++);

	//////////
	uiTextureInstructID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/NormalModeNotSelected.png");
	uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiTextureInstructID,
						m_fBackgroundWidth * 0.5f, m_fBackgroundHeight * 0.08f, vec2TopPosition);

	pButton = new CButton;

	pButton->Initialise(uiBillboardID);

	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pButton);
	m_apMenus[DIFFICULTY_MENU]->SetButtonID(uiMenuItemCount++);

	/////////
	uiTextureInstructID = CTextureManager::GetInstance().CreateTexture("textures/Menu Textures/HardcoreModeSelected.png");
	uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiTextureInstructID,
						m_fBackgroundWidth * 0.5f, m_fBackgroundHeight * 0.15f, vec2BottomPosition);

	pButton = new CButton;

	pButton->Initialise(uiBillboardID);

	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pButton);
	m_apMenus[DIFFICULTY_MENU]->SetButtonID(uiMenuItemCount++);

	// Create difficulty level description.
	CText* pText = new CText;

	uint32 uiFontID = CFontManager::GetInstance().CreateDirect3DFont(static_cast<int32>(m_fBackgroundHeight*0.045f),
						static_cast<int32>(m_fBackgroundWidth*0.025f),500,true,"Constantia");

	RECT rect;

	rect.bottom = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetHeight();
	rect.top = static_cast<int32>(CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)
											->GetHeight() * 0.75f);
	rect.right = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewport(0)->GetWidth();
	rect.left = 0;

	// Colour of border.
	pText->Initialise(rect, DT_CENTER, D3DCOLOR_XRGB(8, 57, 99), "Friendly Fire DISABLED", uiFontID);

	m_apMenus[DIFFICULTY_MENU]->AddMenuItem(pText);
	m_apMenus[DIFFICULTY_MENU]->SetTextID(uiMenuItemCount++);

	return true;
}

const std::string& 
CMenuState::GetSelectedMap()
{
	return (s_strSelectedMap);
}