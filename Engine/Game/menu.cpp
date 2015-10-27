// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menu.cpp
//  Description :   CMenu implementation file.
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../entity structures/entity.h"
#include "../../entity structures/game menu's/menuitem.h" 

// This Includes
#include "menu.h"

// Static Variables
const uint32 CMenu::MAX_NUM_PLAYER_SELECTORS = 4;

// Static Function Prototypes

// Implementation

CMenu::CMenu()
: m_apiPlayerSelectorID(0)
, m_iMenuCubeID(BAD_ID)
, m_apiButtonID(0)
, m_uiMaxNumButtons(0)
, m_uiTextID(BAD_ID)
{
}

CMenu::~CMenu()
{
	for (std::vector<CMenuItem*>::iterator iter = m_vecMenuItems.begin(); 
		iter != m_vecMenuItems.end(); ++iter)
	{
		delete (*iter);
	}
	//deletes the dynamic array
	delete[] m_apiPlayerSelectorID;
	m_apiPlayerSelectorID = 0;

	delete[] m_apiButtonID;
	m_apiButtonID = 0;
}

/**
* 
* Sets the variables to default values.
* 
* @author Rebeccah Cox
* @return bool
*/
bool
CMenu::Initialise(uint32 _uiMaxNumButtons)
{
	m_apiPlayerSelectorID = new int32[MAX_NUM_PLAYER_SELECTORS];
	
	for(uint32 uiID = 0; uiID < MAX_NUM_PLAYER_SELECTORS; ++uiID)
	{
		m_apiPlayerSelectorID[uiID] = BAD_ID;
	}

	m_apiButtonID = new int32[m_uiMaxNumButtons];

	for(uint32 uiID = 0; uiID < m_uiMaxNumButtons; ++uiID)
	{
		m_apiButtonID[uiID] = BAD_ID;
	}

	return (true);
}

/**
* 
* Calls process on all of the menu items.
* 
* @param float32 _fDeltaTick
* @return void 
*/
void
CMenu::Process(float32 _fDeltaTick)
{
	for (std::vector<CMenuItem*>::iterator iter = m_vecMenuItems.begin();
		iter != m_vecMenuItems.end(); ++iter)
	{
		(*iter)->Process(_fDeltaTick);
	}
}

/**
* 
* Adds a menu item to the end of the vector.
* 
* @author Rebeccah Cox
* @param CMenuItem* _pMenuItem
* @return void 
*/
void
CMenu::AddMenuItem(CMenuItem* _pMenuItem)
{
	m_vecMenuItems.push_back(_pMenuItem);
}

/**
* 
* Returns the menu item at the index specified.
* 
* @author Rebeccah Cox
* @return CEntity* - the object in m_vecMenuItems at the index passed in.
*/
CMenuItem*
CMenu::GetMenuItem(uint32 _uiIndex)
{
	return (m_vecMenuItems[_uiIndex]);
}

/**
* 
* Returns the number of menu items.
* 
* @author Rebeccah Cox
* @return uint32 - size of m_vecMenuItems
*/
uint32
CMenu::GetNumberOfMenuItems()
{
	return (static_cast<uint32>(m_vecMenuItems.size()));
}

/**
* 
* Sets all of the menu items this menu holds to active, or not active.
* 
* @author Rebeccah Cox
* @param bool _bIsActive
* @return void
*/
void
CMenu::SetMenuItemsToActive(bool _bIsActive)
{
	for(uint32 iItem = 0; iItem < m_vecMenuItems.size(); ++iItem)
	{
		m_vecMenuItems[iItem]->SetActive(_bIsActive);
	}
}

/**
* 
* Returns the number of player selector boxes. Usually four.
* 
* @author Rebeccah Cox
* @return uint32 MAX_NUM_PLAYER_SELECTORS
*/
uint32
CMenu::GetNumPlayerSelectors()
{
	return (MAX_NUM_PLAYER_SELECTORS);
}

/**
* 
* Checks if the ID passed in is a player selector ID.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID num 
* @return bool - true if ID is one contained in the array.
*/
bool
CMenu::IsAPlayerSelectorID(uint32 _uiID)
{
	uint32 uiIndex = 0;

	while(MAX_NUM_PLAYER_SELECTORS > uiIndex)
	{
		if(m_apiPlayerSelectorID[uiIndex] == static_cast<int32>(_uiID))
		{
			return (true);
		}
		++uiIndex;
	}

	return (false);
}

/**
* 
* Sets the ID number passed in to the first availbale slot in the array.
* If the array is already full, the function returns false, because you are 
*	trying to assign more IDs than there are player selector boxes.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID number
* @return bool - true if the ID was stored.
*/
bool
CMenu::SetPlayerSelectorID(uint32 _uiID)
{
	for(uint32 uiIndex = 0; uiIndex < MAX_NUM_PLAYER_SELECTORS; ++uiIndex)
	{
		if(BAD_ID == m_apiPlayerSelectorID[uiIndex])
		{
			m_apiPlayerSelectorID[uiIndex] = _uiID;
			return (true);
		}
	}

	return (false);
}

/**
* 
* Returns the menu cube ID, which is the position in the menu item vector that the 
*	menu cube is held.
* 
* @author Rebeccah Cox
* @return int32 m_iMenuCubeID - the menu cube ID number.
*/
int32
CMenu::GetMenuCubeID()
{
	return (m_iMenuCubeID);
}

/**
* 
* Returns the menu cube ID number.
* 
* @author Rebeccah Cox
* @param int32 _iID = position in the menu item vector the menu cube is in.
* @return void
*/
void
CMenu::SetMenuCubeID(int32 _iID)
{
	m_iMenuCubeID = _iID;
}

/**
* 
* Returns the number of CButton pointers in the CMenuItem vector.
* 
* @author Rebeccah Cox
* @return uint32 m_uiMaxNumButtons
*/
uint32
CMenu::GetNumButtons()
{
	return(m_uiMaxNumButtons);
}

/**
* 
* Checks if the ID passed in is a button ID.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID num 
* @return bool - true if ID is one contained in the array.
*/
bool
CMenu::IsAButtonID(uint32 _uiID)
{
	uint32 uiIndex = 0;

	while(m_uiMaxNumButtons > uiIndex)
	{
		if(m_apiButtonID[uiIndex] == static_cast<int32>(_uiID))
		{
			return (true);
		}
		++uiIndex;
	}

	return (false);
}

/**
* 
* Sets the ID number passed in to the first availbale slot in the array.
* If the array is already full, the function returns false, because you are 
*	trying to assign more IDs than there are buttons.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID number
* @return bool - true if the ID was stored.
*/
bool
CMenu::SetButtonID(uint32 _uiID)
{
	for(uint32 uiIndex = 0; uiIndex < MAX_NUM_PLAYER_SELECTORS; ++uiIndex)
	{
		if(BAD_ID == m_apiButtonID[uiIndex])
		{
			m_apiButtonID[uiIndex] = _uiID;
			return (true);
		}
	}

	return (false);
}

/**
* 
* Returns the ID number for the instance of CText.
* 
* @author Rebeccah Cox
* @return uint32 m_uiTextID
*/
uint32
CMenu::GetTextID()
{
	return (m_uiTextID);
}

/**
* 
* Sets the ID number for the CText instance.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID number
* @return void
*/
void
CMenu::SetTextID(uint32 _uiID)
{
	m_uiTextID = _uiID;
}
