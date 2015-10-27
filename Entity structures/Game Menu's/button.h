// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   button.h
//  Description :   Declaration for Cbutton
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BUTTON_H__
#define __IGFEB10_MODULE_BUTTON_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../renderentity.h"
#include "menuitem.h"

// Types

// Prototypes


class CButton : public CMenuItem
{
	// Member Functions
public:
	CButton();
	virtual ~CButton();

	bool Initialise(uint32 _uiBillboardID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	uint32 GetID();

	virtual void Reset();

    void SetMapName(std::string _strname);
    std::string GetMapName() const;
    void SetColor(D3DXCOLOR _color);
    D3DXCOLOR GetColor() const;

protected:

private:

	// Member Variables
public:

protected:
	D3DXVECTOR2 m_vec2Position;
	uint32 m_uiBillBoardID;
	uint32 m_uiTextureID;

    std::string m_strMapName;
    D3DXCOLOR m_Color;

private:

}; 

#endif // __IGFEB10_MODULE_BUTTON_H__

