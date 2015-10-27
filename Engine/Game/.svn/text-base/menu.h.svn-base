// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menu.h
//  Description :   Declaration for Cmenu
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MENU_H__
#define __IGFEB10_MODULE_MENU_H__

// Library Includes
#include <vector>

// Local Includes

// Types

// Prototypes
class CMenuItem;

class CMenu
{
	// Member Functions
public:
	CMenu();
	~CMenu();
	
	bool Initialise(uint32 _uiMaxNumButtons = 0);
	void Process(float32 _fDeltaTick);
	void AddMenuItem(CMenuItem* _pMenuItem);

	CMenuItem* GetMenuItem(uint32 _uiIndex);
	uint32 GetNumberOfMenuItems();

	void SetMenuItemsToActive(bool _bIsActive);

	uint32 GetNumPlayerSelectors();
	bool IsAPlayerSelectorID(uint32 _uiID);
	bool SetPlayerSelectorID(uint32 _uiID);

	int32 GetMenuCubeID();
	void SetMenuCubeID(int32 _iID);

	uint32 GetNumButtons();
	bool IsAButtonID(uint32 _uiID);
	bool SetButtonID(uint32 _uiID);

	uint32 GetTextID();
	void SetTextID(uint32 _uiID);

protected:

private:

	// Member Variables
public:

protected:
	std::vector<CMenuItem*> m_vecMenuItems;

	static const uint32 MAX_NUM_PLAYER_SELECTORS;
	int32* m_apiPlayerSelectorID;

	int32 m_iMenuCubeID;

	uint32 m_uiMaxNumButtons;
	int32* m_apiButtonID;

	uint32 m_uiTextID;

private:

}; 

#endif // __IGFEB10_MODULE_MENU_H__

