//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   TotalCubeDomination.h
//  Description :   TotalCubeDomination declaration file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#pragma once

#if !defined(__IGFEB10_IG300_TOTALCUBEDOMINATION_H__)
#define __IGFEB10_IG300_TOTALCUBEDOMINATION_H__

// Library Includes
#include <windows.h>
#include <windowsx.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CClock;
class CRenderer;
class CViewport;
class CProgramState;
class CStaticGraphic;
#ifdef _DEBUG
class CLogManager;
class CTestManager;
#endif // _DEBUG

class CTotalCubeDomination
{
    // Member Functions
public:
	static CTotalCubeDomination& GetInstance();
	static void DestroyInstance();

	bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int32 _iWidth, int32 _iHeight, bool _bFullscreen);

	void Draw();
	void Process(float32 _fDeltaTick);

	void ExecuteOneFrame();

	void SetProgramState(CProgramState* _pState);
	CProgramState* GetProgramState();

#ifdef _DEBUG
	void LogMessage(const char* _kpcMessage, ELogMessageType _eType);
#endif // _DEBUG

	CRenderer* GetRenderer();

	HINSTANCE GetAppInstance();
	HWND GetWindow();

	bool CreateLoadingScreen();

	void ChangeToMenuState();
	void ChangeToGameState();

	void SetLevelName(const char *_kpcFileName);
	std::string GetLevelName();

protected:

private:
	CTotalCubeDomination();
	CTotalCubeDomination(CTotalCubeDomination& _kr);
	CTotalCubeDomination& operator =(CTotalCubeDomination& _kr);
	~CTotalCubeDomination();

    // Member Variables
public:

protected:
	//Singleton
	static CTotalCubeDomination* s_pTotalCubeDomination;

#ifdef _DEBUG
	CLogManager* m_apLogManager[LOG_MESSAGE_MAX];
#endif // _DEBUG

	CProgramState* m_pState;
	CProgramState* m_pLastState;

	//Application data
	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	//Direct3D Renderer
	CRenderer* m_pRenderer;

	//Clock
	CClock* m_pClock;

	CStaticGraphic* m_pLoadingScreen;
	bool m_bIsLoading;
	bool m_bIsStartingGame;

	std::string m_strLevelName;

	bool m_bChangeToMenu;
	bool m_bChangeToGame;

#ifdef _DEBUG
	// Test Harness.
	CTestManager* m_pTestManager;
#endif // _DEBUG

private:

};

#endif // __IGFEB10_IG300_TOTALCUBEDOMINATION_H__

