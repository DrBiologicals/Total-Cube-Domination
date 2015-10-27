// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   text.h
//  Description :   Declaration for Ctext
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TEXT_H__
#define __IGFEB10_MODULE_TEXT_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <windowsx.h>
#include <string>

// Local Includes
#include "menuitem.h"
#include "../../defines.h"

// Types

// Prototypes

class CText : public CMenuItem
{
	// Member Functions
public:
	CText();
	virtual ~CText();

	bool Initialise(const RECT& _textRect, DWORD _dwFormat, DWORD _dwColour, const char* _kpcString, uint32 _uiID);

	virtual void Process(float32 _fDeltaTick);
	void Draw();

	RECT GetRect();

	virtual void Reset();

	void SetText(const char* _kpcString);

protected:

private:

	// Member Variables
public:

protected:
	RECT m_textRect;
	DWORD m_dwFormat;
	DWORD m_dwColour;
	const char* m_kpcString;
	uint32 m_uiID;


private:

}; 

#endif // __IGFEB10_MODULE_TEXT_H__

