
// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   font.cpp
//  Description :   
//  Author      :   TeamA
//

// Library Includes

// Local Includes
#include "engine/totalcubedomination.h"
#include "engine/graphics and sound/renderer.h"

// This Includes
#include "font.h"

// Static Variables

// Static Function Prototypes

// Implementation
CFont::CFont()
: m_pFont(0)
, m_iWidth(0)
, m_iHeight(0)
, m_iWeight(0)
, m_bItalic(false)
{
}

CFont::~CFont()
{
    if (m_pFont)
    {
        m_pFont->Release();
        m_pFont = 0;
    }
}

bool
CFont::Initialise(int32 _iHeight, int32 _iWidth, int32 _iWeight, bool _bItalic, const char *_kpcFontName)
{
	m_iHeight = _iHeight;
	m_iWidth = _iWidth;
	m_iWeight = _iWeight;
	bool m_bItalic = _bItalic;

	HRESULT hr = D3DXCreateFont(CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice(), m_iHeight,
		m_iWidth, m_iWeight, D3DX_DEFAULT, m_bItalic, 0, 0, 0, 0, _kpcFontName, &m_pFont);

    if (FAILED(hr) )
    {
        return (false);
    }

    m_strFontName = _kpcFontName;

	return (true);
}

void 
CFont::OnDeviceLost()
{
	if (m_pFont)
	{
		m_pFont->Release();
		m_pFont = 0;
	}
}

void 
CFont::OnDeviceReset()
{
	D3DXCreateFont(CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice(), m_iHeight,
		m_iWidth, m_iWeight, D3DX_DEFAULT, m_bItalic, 0, 0, 0, 0, m_strFontName.c_str(), &m_pFont);
}

LPD3DXFONT
CFont::GetFont()
{
    return (m_pFont);
}