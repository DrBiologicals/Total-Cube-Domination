// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   list.h
//  Description :   Declaration for Clist
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_LIST_H__
#define __IGFEB10_MODULE_LIST_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>

// Local Includes
#include "../entity.h"

// Types

// Prototypes
class CButton;

class CList : public CMenuItem
{
	// Member Functions
public:
	CList();
	virtual ~CList();

	bool Initialise(D3DXVECTOR2 _vec2Position);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	CButton* Addbutton();

    void MoveUpList();
    void MoveDownList();

    int32 Select();

    void LoadAssets();

    virtual void Reset();

protected:

private:

	// Member Variables
public:

protected:
	std::vector<CButton*> m_vecButtons;
    CButton* m_pSelectedButton;

    D3DXCOLOR m_Color;

    int32 m_iSelectedIndex;

    static uint32 s_uiFontID;

private:

}; 

#endif // __IGFEB10_MODULE_LIST_H__

