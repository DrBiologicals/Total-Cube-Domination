//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   game.cpp
//  Description :   game implementation file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../igutils.h"
#include "../performanceclock.h"
#include "../systemclock.h"
#include "graphics and sound/renderer.h"
#include "viewport/viewport.h"
#include "game/gamestate.h"
#include "game/statistics.h"
#include "game/menustate.h"
#include "input/inputhandler.h"
#include "../entity structures/player objects/ai/pathfinder.h"
#include "Graphics and sound/texturemanager.h"
#include "Graphics and sound/modelmanager.h"
#include "Graphics and sound/fontmanager.h"
#include "Graphics and sound/billboardmanager.h"
#include "Graphics and sound/soundmanager.h"
#include "Graphics and sound/spritemanager.h"
#include "Graphics and sound/lightmanager.h"
#include "../entity structures/particle/emittermanager.h"
#include "../entity structures/player objects/playermanager.h"
#include "../entity structures/player objects/power up/powerupmanager.h"
#include "../entity structures/game menu's/staticgraphic.h"
#include "viewport/camera.h"
#ifdef _DEBUG
#include "./logging/logmanager.h"
#include "./logging/logdebugoutput.h"
#include "./logging/logfile.h"
#include "TestHarnesses/testManager.h"
#endif // _DEBUG

// This Include
#include "TotalCubeDomination.h"

// Static Variables
CTotalCubeDomination* CTotalCubeDomination::s_pTotalCubeDomination = 0;

// Static Function Prototypes

// Implementation
CTotalCubeDomination::CTotalCubeDomination()
: m_pRenderer(0)
, m_hApplicationInstance(0)
, m_hMainWindow(0)
, m_pClock(0)
, m_pState(0)
, m_pLastState(0)
, m_pLoadingScreen(0)
, m_bIsLoading(false)
, m_bIsStartingGame(false)
, m_bChangeToMenu(false)
, m_bChangeToGame(false)
#ifdef _DEBUG
, m_pTestManager(0)
#endif // _DEBUG
{
#ifdef _DEBUG
	memset(m_apLogManager, 0, sizeof(m_apLogManager));
#endif // _DEBUG
}

CTotalCubeDomination::~CTotalCubeDomination()
{
	delete m_pClock;
	m_pClock = 0;

	delete m_pRenderer;
	m_pRenderer = 0;

	delete m_pState;
	m_pState = 0;

	delete m_pLastState;
	m_pLastState = 0;

	delete m_pLoadingScreen;
	m_pLoadingScreen = 0;

#ifdef _DEBUG
	for (int32 i = 0; i < LOG_MESSAGE_MAX; ++i)
	{
		delete m_apLogManager[i];
		m_apLogManager[i] = 0;
	}
#endif // _DEBUG
}

/**
*
* This function clears the renderer's buffers
*
* @author Daniel Jay
* @param _hInstance The red component of the colour
* @param _hWnd The green component of the colour
* @param _iWidth The blue component of the colour
* @param _iHeight The blue component of the colour
* @param _bFullscreen The blue component of the colour
* @return The success or failure of the initialisation
*
*/
bool 
CTotalCubeDomination::Initialise(HINSTANCE _hInstance, HWND _hWnd, int32 _iWidth, int32 _iHeight, bool _bFullscreen)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

#ifdef _DEBUG
	for (int32 i = 0; i < LOG_MESSAGE_MAX; ++i)
	{
		m_apLogManager[i] = new CLogManager;
	}

	{
		CLogFile* pLogFile = new CLogFile;
		pLogFile->Initialise("init.log");

		m_apLogManager[LOG_MESSAGE_INIT]->AddLogTarget(pLogFile);

		CLogDebugOutput* pOutput = new CLogDebugOutput;

		m_apLogManager[LOG_MESSAGE_INIT]->AddLogTarget(pOutput);

		pLogFile = new CLogFile;
		pLogFile->Initialise("paths.log");
		m_apLogManager[LOG_MESSAGE_PATHS]->AddLogTarget(pLogFile);
		pOutput = new CLogDebugOutput;
		m_apLogManager[LOG_MESSAGE_PATHS]->AddLogTarget(pOutput);

		pLogFile = new CLogFile;
		pLogFile->Initialise("sound.log");
		m_apLogManager[LOG_MESSAGE_SOUND]->AddLogTarget(pLogFile);
		pOutput = new CLogDebugOutput;
		m_apLogManager[LOG_MESSAGE_SOUND]->AddLogTarget(pOutput);

		//pLogFile = new CLogFile;
		//pLogFile->Initialise("tower.log");
		//m_apLogManager[LOG_MESSAGE_TOWER]->AddLogTarget(pLogFile);
		pOutput = new CLogDebugOutput;
		m_apLogManager[LOG_MESSAGE_OUTPUT]->AddLogTarget(pOutput);

		// Test harness logging file.
		pLogFile = new CLogFile;
		pLogFile->Initialise("tests.log");

		m_apLogManager[LOG_MESSAGE_TEST]->AddLogTarget(pLogFile);
	}
#endif // _DEBUG

	m_pClock = new CPerformanceClock;

	if (!m_pClock->Initialise())
	{
#ifdef _DEBUG
	LogMessage("Performance counter failed, using system clock", LOG_MESSAGE_INIT);
#endif // _DEBUG

		m_pClock = new CSystemClock;
	}

	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pRenderer = new CRenderer;

	VALIDATE(m_pRenderer->Initialise(_hWnd, _iWidth, _iHeight, _bFullscreen));
	m_pRenderer->SetClearColour(0.0f, 0.0f, 0.0f);

    D3DMATERIAL9 material;

    ZeroMemory(&material, sizeof(material) );
    material.Ambient.a = 1.0f;
    material.Ambient.g = 1.0f;
    material.Ambient.r = 1.0f;
    material.Ambient.b = 1.0f;

    m_pRenderer->GetDevice()->SetMaterial(&material);

	VALIDATE(CInputHandler::GetInstance().Initialise(m_hApplicationInstance, m_hMainWindow));

	CreateLoadingScreen();

	ChangeToMenuState();
	//SetProgramState(new CMenuState);

	ShowCursor(false);

#ifdef _DEBUG
	/*// Instantiate test harness manager.
	m_pTestManager = new CTestManager();

	//Set up
	m_pTestManager->SetUp();

	//Run tests
	m_pTestManager->RunTest();

	//Tear down
	m_pTestManager->TearDown();

	delete m_pTestManager;
	m_pTestManager = 0;*/
#endif // _DEBUG

#ifdef _DEBUG
	LogMessage("Initialisation successful", LOG_MESSAGE_INIT);
#endif // _DEBUG

	return (true);
}

/**
*
* This function processes the game's draw cycle
*
* @author Daniel Jay
*
*/
void 
CTotalCubeDomination::Draw()
{
	
	m_pRenderer->Render();
	
}

/**
*
* This function processes the game's logic cycle
*
* @author Daniel Jay
* @param _fDeltaTick The difference in time between the current and last frames
*
*/
void 
CTotalCubeDomination::Process(float32 _fDeltaTick)
{
	if(true == m_bIsLoading)
	{
		CreateLoadingScreen();
		m_pLoadingScreen->Process(_fDeltaTick);

		m_bIsLoading = false;
		//m_bIsStartingGame = true;
	}
	else if(true == m_bChangeToGame)
	{
		m_bChangeToGame = false;

		SetProgramState(new CGameState);
	}
	else if(true == m_bChangeToMenu)
	{
		m_bChangeToMenu = false;

		SetProgramState(new CMenuState);
	}
	else
	{
		delete m_pLastState;
		m_pLastState = 0;

		CInputHandler::GetInstance().Update();

		if (m_pState)
		{
			m_pState->Process(_fDeltaTick);
		}
	}
}

/**
*
* This function processes one full game cycle
*
* @author Daniel Jay
*
*/
void 
CTotalCubeDomination::ExecuteOneFrame()
{
	float32 fDT = m_pClock->GetDeltaTick();

#ifdef _DEBUG
	std::string str = ToString(int32(1.0f / fDT));

	SetWindowText(m_hMainWindow, str.c_str());
#endif // _DEBUG

	Process(fDT);
	
	Draw();

	m_pClock->Process();

	Sleep(1);
}

/**
*
* This function gets the singleton instance of the game
*
* @author Daniel Jay
* @return The singleton instance of the game
*
*/
CTotalCubeDomination& 
CTotalCubeDomination::GetInstance()
{
	if(!s_pTotalCubeDomination)
	{
		s_pTotalCubeDomination = new CTotalCubeDomination();
	}

	return (*s_pTotalCubeDomination);
}

/**
*
* This function destroys the singleton instance of the game
*
* @author Daniel Jay
*
*/
void 
CTotalCubeDomination::DestroyInstance()
{
	delete s_pTotalCubeDomination;
	s_pTotalCubeDomination = 0;
}

/**
*
* This function sets the game's state
*
* @author Daniel Jay
* @param _pState A pointer to the new state
*
*/
void 
CTotalCubeDomination::SetProgramState(CProgramState* _pState)
{
    m_pLastState = m_pState;

	delete m_pLastState;
	m_pLastState = 0;
    m_pState = 0;

	CFontManager::GetInstance().Clear();
	CTextureManager::GetInstance().Clear();
	CModelManager::GetInstance().Clear();
	CLightManager::GetInstance().Clear();
    CBillboardManager::GetInstance().ClearManager();
    CSoundManager::GetInstance().Clear();
    CSpriteManager::GetInstance().Clear();
    CPlayerManager::GetPlayerManagerInstance().DestroyPlayers();
    CEmitterManager::GetInstance().Clear();

	for(uint32 i = 0; i < m_pRenderer->GetNumViewports(); ++i)
	{
		m_pRenderer->GetViewport(i)->ClearRenderQueue();
	}

	if (!_pState->Initialise())
	{
		PostQuitMessage(0);
	}

    m_pState = _pState;
    
    m_pState->SetOwner(this);
}

/**
* 
* Return a pointer to the current state.
* 
* @author Rebeccah Cox
* @return 
*/
CProgramState*
CTotalCubeDomination::GetProgramState()
{
	return (m_pState);
}

#ifdef _DEBUG
/**
*
* This function logs a message through the game's logging system
*
* @author Daniel Jay
* @param _kpcMessage The message to log
* @param _eType The type of message to log
*
*/
void 
CTotalCubeDomination::LogMessage(const char* _kpcMessage, ELogMessageType _eType)
{
	m_apLogManager[_eType]->WriteLine(_kpcMessage);
}
#endif // _DEBUG

/**
*
* This function returns a pointer to the game's renderer
*
* @author Daniel Jay
* @return A pointer to the game's renderer
*
*/
CRenderer* 
CTotalCubeDomination::GetRenderer()
{
	return (m_pRenderer);
}

/**
*
* This function returns a handle to the game's instance
*
* @author Daniel Jay
* @return A handle to the game's instance
*
*/
HINSTANCE 
CTotalCubeDomination::GetAppInstance()
{
	return (m_hApplicationInstance);
}

/**
*
* This function returns a handle to the game's window
*
* @author Daniel Jay
* @return A handle to the game's window
*
*/
HWND 
CTotalCubeDomination::GetWindow()
{
	return (m_hMainWindow);
}

/*
* This function creates the loading screen
* @author Rigardt de Vries
* @return true if it succeded the initialisation, else return false
*/

bool
CTotalCubeDomination::CreateLoadingScreen()
{
	delete m_pLoadingScreen;
    m_pLoadingScreen = new CStaticGraphic;

	m_pRenderer->SetNumViewports(1);
	m_pRenderer->GetViewport(0)->CreateCamera(D3DXToRadian(45), 0.1f, 100);

	D3DXVECTOR2 vec2Position = D3DXVECTOR2(static_cast<float32>(m_pRenderer->GetScreenWidth()*0.5f),
								static_cast<float32>(m_pRenderer->GetScreenHeight()*0.5f));
	uint32 uiloadingTextureID = CTextureManager::GetInstance().CreateTexture("textures/loadingScreen.png");
	uint32 uiBillboardID = CBillboardManager::GetInstance().CreateBillboard(uiloadingTextureID,
							static_cast<float32>(m_pRenderer->GetScreenWidth()),
							static_cast<float32>(m_pRenderer->GetScreenHeight()),
							vec2Position);

	if(false == m_pLoadingScreen->Initialise(uiBillboardID))
	{
		return (false);
	}

	m_pLoadingScreen->SetActive(true);

    return (true);
}

void
CTotalCubeDomination::ChangeToMenuState()
{
	m_bIsLoading = true;
	m_bChangeToMenu = true;
}

void
CTotalCubeDomination::ChangeToGameState()
{
	m_bIsLoading = true;
	m_bChangeToGame = true;
}

void
CTotalCubeDomination::SetLevelName(const char *_kpcFileName)
{
	m_strLevelName = _kpcFileName;
}
std::string
CTotalCubeDomination::GetLevelName()
{
	return(m_strLevelName);
}

