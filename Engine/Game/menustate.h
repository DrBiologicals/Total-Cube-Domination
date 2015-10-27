// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menustate.h
//  Description :   Declaration for CMenuState
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MENUSTATE_H__
#define __IGFEB10_MODULE_MENUSTATE_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes
#include "programstate.h"
#include "../../entity structures/game menu's/button.h"

// Types

// Prototypes
enum EMenu
{
	MAIN_MENU = 0,
	PLAYER_SELECT_MENU,
	LEVEL_SELECT_MENU,
	INSTRUCTIONS_MENU,
	CREDITS_MENU,
	DIFFICULTY_MENU,
	MENU_MAX
};

class CMenu;
class CMenuCube;

class CMenuState : public CProgramState
{
	// Member Functions
public:
	CMenuState();
	~CMenuState();

	bool Initialise();
	void Process(float32 _fDeltaTick);
	void SetActiveMenu(EMenu _eMenu);

	void CheckButtonPresses();

	static const std::string& GetSelectedMap();

protected:

private:
	bool CreateMainMenu();
	bool CreatePlayerSelectMenu();
	bool CreateInstructions();
	bool CreateCredits();
	bool CreateLevelSelect();
	bool CreateDifficultyMenu();

	void CheckForMenuChange(float32 _fDeltaTick);

	// Used for PLAYER_SELECT_MENU.
	bool HavePlayersChosenTeams();

	// Member Variables
public:

protected:
	CMenu* m_apMenus[MENU_MAX];

	uint32 m_uiBackgroundBillboardID;
	uint32 m_uiBackgroundTextureID;

	EMenu m_eActiveMenu;

	float32 m_fBackgroundWidth;
	float32 m_fBackgroundHeight;
	float32 m_fBackgroundDistance;
	float32 m_fCurrentTime;

	std::vector<std::string> m_vecMapStrings;
	static std::string s_strSelectedMap;

	uint32 m_uiMusic;

	int32 m_iDifficulty;

	D3DXVECTOR2 m_vec2CenterPosition;

private:

}; 

#endif // __IGFEB10_MODULE_MENUSTATE_H__

