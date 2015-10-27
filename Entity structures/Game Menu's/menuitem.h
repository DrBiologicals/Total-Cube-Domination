// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   menuitem.h
//  Description :   Declaration for CMenuItem
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MENUITEM_H__
#define __IGFEB10_MODULE_MENUITEM_H__

// Library Includes
#include <vector>

// Local Includes
#include "../renderentity.h"

// Types
struct TMenuRects
{
    RECT m_Src;
    RECT m_Dest;
    bool m_bDrawing;
};

// Prototypes

class CMenuItem: public CRenderEntity
{
	// Member Functions
public:
	CMenuItem();
	virtual ~CMenuItem();
	
	virtual bool Initialise();
	virtual void Process(float32 _fDeltaTick) = 0;
	virtual void Draw() = 0;

	bool IsActive();
	void SetActive(bool _bIsActive);

	bool IsExiting();
	virtual bool IsAdvancing();
	virtual bool IsBeingUsed();

	uint32 GetControllerID();
	bool IsControllerActive();
	void UpdateControllerID();

	virtual void Reset() = 0;

protected:

private:

	// Member Variables
public:

protected:
	bool m_bIsActive;

	// Checked by menu state, to request a menu change. 
	bool m_bIsExiting;
	bool m_bIsAdvancing;
	bool m_bIsBeingUsed;

	uint32 m_uiControllerID;
	bool m_bControllerIsConnected;

private:

}; 

#endif // __IGFEB10_MODULE_MENU_H__
