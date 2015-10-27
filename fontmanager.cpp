// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :  fontmanager.cpp
//  Description :   
//  Author      :   
//  Mail        :   
//

// Library Includes

// Local Includes
#include "font.h"

// This Includes
#include "fontmanager.h"

// Static Variables

// Static Function Prototypes
CFontManager* CFontManager::s_pInstance = 0;

// Implementation
CFontManager::CFontManager()
{
    memset(m_apFonts, 0, sizeof(m_apFonts));
}

CFontManager::~CFontManager()
{
    for (int32 i = 0; i < 8; ++i)
    {
        if (m_apFonts[i])
        {
            delete m_apFonts[i];
            m_apFonts[i] = 0;
        }
    }
}

bool
CFontManager::Initialise()
{
	return true;
}

void
CFontManager::Clear()
{
    for (int32 i = 0; i < 8; ++i)
    {
        if (m_apFonts[i])
        {
            delete m_apFonts[i];
        }
		else
		{
			break;
		}
    }

    memset(m_apFonts, 0, sizeof(m_apFonts));
}

void 
CFontManager::OnDeviceLost()
{
	for (int32 i = 0; i < 8; ++i)
    {
        if (m_apFonts[i])
        {
            m_apFonts[i]->OnDeviceLost();
        }
		else
		{
			break;
		}
    }
}

void 
CFontManager::OnDeviceReset()
{
	for (int32 i = 0; i < 8; ++i)
    {
        if (m_apFonts[i])
        {
            m_apFonts[i]->OnDeviceReset();
        }
		else
		{
			break;
		}
    }
}

uint32
CFontManager::CreateDirect3DFont(int32 _iHeight, int32 _iWidth, int32 _iWeight, bool _bItalic, const char *_kpcFontName)
{
    CFont* pFont = new CFont;

	if (pFont->Initialise(_iHeight, _iWidth, _iWeight, _bItalic, _kpcFontName) )
	{
		for (int32 i = 0; i < 8; ++i)
		{
			if (m_apFonts[i] == 0)
			{
				m_apFonts[i] = pFont;

				return (i);
			}
		}
	}

    delete pFont;

	return (BAD_ID);
}

void
CFontManager::Draw(uint32 _uiID, const char* _kpcString, LPRECT _pRect, DWORD _dwFormat, DWORD _dwColour)
{
	if (m_apFonts[_uiID]->GetFont())
	{
		m_apFonts[_uiID]->GetFont()->DrawText(0, _kpcString, -1, _pRect, _dwFormat, _dwColour);
	}
}

CFontManager&
CFontManager::GetInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CFontManager;
	}

	return(*s_pInstance);
}

void
CFontManager::DestroyInstance()
{
    delete s_pInstance;
    s_pInstance = 0;
}