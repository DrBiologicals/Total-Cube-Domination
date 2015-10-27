// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   button.cpp
//  Description :   button.cppfor implementation of button.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/billboard.h"
#include "../../engine/graphics and sound/billboardmanager.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/Totalcubedomination.h"
#include "../../engine/viewport/viewport.h"

// This Includes
#include "button.h"

// Static Variables

// Static Function Prototypes

// Implementation

CButton::CButton()
: m_strMapName("")
{
    m_Color = 0xFFFFFFFF;
}

CButton::~CButton()
{
}
/**
* 
* Stores the variables passed in as member variables and then creates a billboard
* 
* @author Carsten Scholz
* @return bool.
*/
bool
CButton::Initialise(uint32 _uiBillboardID)
{
	m_uiBillBoardID = _uiBillboardID;

    if (BAD_ID != _uiBillboardID)
    {
	    CBillboard* pBillboard = CBillboardManager::GetInstance().GetBillboard(m_uiBillBoardID);
	}
	else
	{
		return (false);
	}

	return (true);
}
/**
* 
* Sets the billboard into the viewport
* 
* @author Carsten Scholz
* @return void.
*/
void 
CButton::Process(float32 _fDeltaTick)
{
	if(true == m_bIsActive)
	{
		// Add to viewports.
		CTotalCubeDomination::GetInstance().GetRenderer()
			->AddToViewport(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE, 0);
	}
}
/**
* 
* Sets the texture and gets the billboard then draws both to the screen.
* 
* @author Carsten Scholz
* @return void.
*/
void 
CButton::Draw()
{
    if (m_uiBillBoardID != BAD_ID)
    {
        // Draw the billboard.
        CBillboardManager::GetInstance().Draw(m_uiBillBoardID);
    }
}
/**
* 
* Gets the billboard ID of the button
* 
* @author Carsten Scholz
* @return uint32 the billboards ID
*/
uint32 
CButton::GetID()
{
	return (m_uiBillBoardID);
}

/**
* 
* Resets to the state it needs to be in when entering the menu.
* 
* @author Rebeccah Cox
* @return void.
*/
void
CButton::Reset()
{
	Initialise(m_uiBillBoardID);
}

/*
* This function sets the name of the button.
* @author Rigardt de Vries
* @param _strName           the new name of the button
* @return void
*/
void 
CButton::SetMapName(std::string _strName)
{
    m_strMapName = _strName;
}

/*
* Returns the map name string
* @author Rigardt de Vries
* @return the string
*/
std::string
CButton::GetMapName() const
{
    return (m_strMapName);
}

/*
* This function sets the color of the button.
* @author Rigardt de Vries
* @param _color             the new color
* @return void
*/
void
CButton::SetColor(D3DXCOLOR _color)
{
    m_Color = _color;
}

/*
* Returns the color of the button
* @author Rigardt de Vries
* @return the color.
*/
D3DXCOLOR
CButton::GetColor() const
{
    return (m_Color);
}