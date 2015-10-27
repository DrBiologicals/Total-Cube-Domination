// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   text.cpp
//  Description :   text.cppfor implementation of text.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Engine/Graphics and sound/fontmanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../../Engine/Graphics and sound/renderer.h"

// This Includes
#include "text.h"

// Static Variables

// Static Function Prototypes

// Implementation

CText::CText()
{
}

CText::~CText()
{
}

bool
CText::Initialise(const RECT& _textRect, DWORD _dwFormat, DWORD _dwColour, const char* _kpcString, uint32 _uiID)
{
	m_textRect = _textRect;

	m_dwFormat = _dwFormat;
	m_dwColour = _dwColour;

	m_kpcString = _kpcString;

	m_uiID = _uiID;

	return (true);
}

void
CText::Process(float32 _fDeltaTick)
{
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
}

void
CText::Draw()
{
	CFontManager::GetInstance().Draw(m_uiID, m_kpcString, &m_textRect, m_dwFormat, m_dwColour);
}
RECT
CText::GetRect()
{
	return (m_textRect);
}

/**
* 
* Resets to the state it needs to be in when entering the menu.
* 
* @author Rebeccah Cox
* @return void.
*/
void
CText::Reset()
{
	Initialise(m_textRect, m_dwFormat, m_dwColour, m_kpcString, m_uiID);
}

/**
* 
* Sets the text to display.
* 
* @author Rebeccah Cox
* @param const char* _kpcString
* @return void.
*/
void
CText::SetText(const char* _kpcString)
{
	m_kpcString = _kpcString;
}
