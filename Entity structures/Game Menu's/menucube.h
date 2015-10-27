// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menucube.h
//  Description :   Declaration for CMenuCube
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MENUCUBE_H__
#define __IGFEB10_MODULE_MENUCUBE_H__

// Library Includes

// Local Includes
#include "menuitem.h"
#include "../../angle.h"

// Types
const float32 MENU_CUBE_TURN_SPEED = 3.14f;

enum EMenuOption
{
	MENU_OPTION_PLAY,
	MENU_OPTION_EXIT,
	MENU_OPTION_INSTRUCTIONS,
	MENU_OPTION_CREDITS,
	MAX_MENU_OPTIONS
};

// Prototypes
class CButton;
class CText;

class CMenuCube : public CMenuItem
{
	// Member Functions
public:
	CMenuCube();
	~CMenuCube();

	bool Initialise(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiRightArrowBillboard,
					uint32 _uiLeftArrowBillboard, uint32 _uiRightArrowTexture, uint32 _uiLeftArrowTexture,
					uint32 _uiFontID, uint32 _uiSoundLeftID, uint32 _uiSoundRightID, uint32 _uiSoundAcceptID,
					uint32 _uiSoundBackID);
	void Process(float32 _fDeltaTick);
	void Draw();

	void MenuSelect();

	virtual void Reset();

protected:

private:
	void ChangeMenuOption(bool _bToRight);
	void SetCurrentMenu(EMenuOption _eMenu);

	// Member Variables
public:

protected:
	static uint32 s_uiModelID;
	static uint32 s_uiTextureID;

	bool m_bTransition;

	uint32 m_uiRightArrowBillboard;
	uint32 m_uiLeftArrowBillboard;
	uint32 m_uiRightArrowTexture;
	uint32 m_uiLeftArrowTexture;

	uint32 m_uiSoundLeft;
	uint32 m_uiSoundRight;
	uint32 m_uiSoundAccept;
	uint32 m_uiSoundBack;

	EMenuOption m_eMenuSelect;

	CAngle m_CurrentAngle;
	CAngle m_TargetAngle;

	CText* m_pLeftArrowText;
	CText* m_pRightArrowText;
	std::vector<std::string> m_strTextOptions;

	uint32 m_uiFontID;

private:

}; 

#endif // __IGFEB10_MODULE_MENUCUBE_H__

