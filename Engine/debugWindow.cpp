// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   debugwindow.cpp
//  Description :   debugwindow.cppfor implementation of debugwindow.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//
// Library Includes

#ifdef _DEBUG

#include <windows.h>
#include <windowsx.h>
#include <string>

// Local Includes
#include "Totalcubedomination.h"
#include "Game/gamestate.h"
#include "../igutils.h"
#include "../Entity Structures/Player Objects/playermanager.h"
#include "../Entity Structures/Player Objects/player.h"
#include "../Entity Structures/Player Objects/tank.h"
// This Includes

#include "debugwindow.h"

// Static Variables

// Static Function Prototypes


// Implementation
CDebugWindow::CDebugWindow()
: m_bIsOpen(false)
, m_hDebugWindow(0)
{

}

CDebugWindow::~CDebugWindow()
{

}


BOOL CALLBACK DialogProc(HWND _hDlg, uint32 _uiMsg, WPARAM _wParam, LPARAM _lParam)
{	
	HWND MoveBox = GetDlgItem(_hDlg, IDC_MOVESPEED);
	HWND PlasmaBox = GetDlgItem(_hDlg, IDC_PLASMACOOL);
	HWND EMPBox = GetDlgItem(_hDlg, IDC_EMPCOOL);
	HWND ShieldCharge = GetDlgItem(_hDlg, IDC_SHIELDCHARGE);
	HWND ShieldRate = GetDlgItem(_hDlg, IDC_SHIELDRATE);
	HWND MaxShield = GetDlgItem(_hDlg, IDC_MAXSHIELD);

	if(false == dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())
									->GetDebugWindow()->HasAWindowHandle())
	{
		dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())
									->GetDebugWindow()->SetWindowHandle(_hDlg);
	}

	switch(_uiMsg)
	{
	case WM_INITDIALOG:
		{
			//Get handles to the edit boxes		
			SetWindowText(MoveBox, ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetMovementSpeed()).c_str());
			SetWindowText(PlasmaBox, ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetPlasmaCoolDown()).c_str());
			SetWindowText(EMPBox,ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetEMPCoolDown()).c_str());
			SetWindowText(ShieldCharge, ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetShieldRechargeTimer()).c_str());
			SetWindowText(ShieldRate, ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetShieldRechargeRate()).c_str());
			SetWindowText(MaxShield, ToString(CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->GetMaxShield()).c_str());
		}
		break;
	case WM_COMMAND:
		{
			switch(LOWORD(_wParam))
			{
			case IDC_CHANGEBUTTON:
				{
					// Create a buffer to hold the values from the box.
					int32 kiTextSize = GetWindowTextLength(_hDlg) + 1;
					std::vector<int8> textBuffer(kiTextSize);

					//Changing the values by chaning string to float32
					//And changing the players movement
					//Using 8 for max players
					//int32 iDecimalPlace = 1;
					for(int32 iPlayers = 0; iPlayers < 8; ++iPlayers)
					{
						// Set movement.
						GetWindowText(MoveBox, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetMovementSpeed(static_cast<float32>(atof(&textBuffer[0])));

						// Set plasma.
						GetWindowText(PlasmaBox, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetPlasmaCoolDown(static_cast<float32>(atof(&textBuffer[0])));

						// Set EMP.
						GetWindowText(EMPBox, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetEMPCoolDown(static_cast<float32>(atof(&textBuffer[0])));

						// Set shield recharge timer.
						GetWindowText(ShieldCharge, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetShieldRechargeTimer(static_cast<float32>(atof(&textBuffer[0])));

						// Set shield recharge rate.
						GetWindowText(ShieldRate, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetShieldRechargeRate(static_cast<float32>(atof(&textBuffer[0])));

						// Set shield max shield.
						GetWindowText(MaxShield, &textBuffer.front(), static_cast<int32>(textBuffer.size()));
						CPlayerManager::GetPlayerManagerInstance().GetPlayer(iPlayers)->GetTank()
												->SetMaxShield(static_cast<float32>(atof(&textBuffer[0])));
					}
				}
				break;

			case IDC_CLOSEBUTTON:
				{
					dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())
											->GetDebugWindow()->CloseWindow();
					DestroyWindow(_hDlg);
				}
				break;

			default:break;
			}
			break;
		}
		break;

		case WM_CLOSE:
		{
			dynamic_cast<CGameState*>(CTotalCubeDomination::GetInstance().GetProgramState())
											->GetDebugWindow()->CloseWindow();
			DestroyWindow(_hDlg);
		}
		break;
	
		default:break;
		}

	return(false);
}

/*
* 
* @author Michael McQuarrie
*
* @return void
*/
void
CDebugWindow::OpenDebugWindow()
{
	DialogBox(CTotalCubeDomination::GetInstance().GetAppInstance(), MAKEINTRESOURCE(IDD_DEBUGWINDOW), NULL, DialogProc);
	//m_bIsOpen = true;
}

/**
* 
* Returns true if the dialog box is open, or false if it is not.
* 
* @author Rebeccah Cox
* @return bool m_bIsOpen;
*/
bool
CDebugWindow::IsWindowOpen()
{
	return (m_bIsOpen);
}

/**
* 
* Closes the window and sets the m_bIsOpen to false;
* 
* @author Rebeccah Cox
* @return void
*/
void
CDebugWindow::CloseWindow()
{
	m_bIsOpen = false;
}

/**
* 
* Sets the member variable HWND m_hDebugWindow to the handle passed in.
* 
* @author Rebeccah Cox
* @param HWND _hwnd - handle to the dialog window.
* @return void
*/
void
CDebugWindow::SetWindowHandle(HWND _hwnd)
{
	m_hDebugWindow = _hwnd;
}

/**
* 
* Returns true if this object has a handle to a dialog window.
* 
* @author Rebeccah Cox
* @return bool - true if a HWND is set.
*/
bool
CDebugWindow::HasAWindowHandle()
{
	if(0 == m_hDebugWindow)
	{
		return (false);
	}
	return (true);
}

void 
CDebugWindow::ChangeValues(float32 _fMove, float32 _fPlasma, float32 _fEMP, 
		float32 _fCharge, float32 _fRate, float32 _fMax)
{
	//Chaning the players movements
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetMovementSpeed(_fMove);
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetPlasmaCoolDown(_fPlasma);
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetEMPCoolDown(_fEMP);
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetShieldRechargeTimer(_fCharge);
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetShieldRechargeRate(_fRate);
	CPlayerManager::GetPlayerManagerInstance().GetPlayer(0)->GetTank()->SetMaxShield(_fMax);
}

#endif // _DEBUG