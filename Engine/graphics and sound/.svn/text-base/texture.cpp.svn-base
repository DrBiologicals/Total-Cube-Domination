// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   texture.cpp
//  Description :   texture.cppfor implementation of texture.h
//  Author      :   TeamA
//

// Library Includes

// Local Includes
#include "../totalcubedomination.h"
#include "renderer.h"

// This Includes
#include "texture.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTexture::CTexture()
: m_pTexture(0)
{
}

CTexture::~CTexture()
{
    if (m_pTexture)
    {
        m_pTexture->Release();
        m_pTexture = 0;
    }
}

/**
*
* This function initialises the texture resource from a file
*
* @author Daniel Jay
* @param _pcFileName The name of the texture file to load from
* @return True if the initialisation succeeded
*
*/
bool
CTexture::Initialise(const char *_pcFileName)
{
	D3DXIMAGE_INFO ImageInfo;

	HRESULT hr = 
		D3DXCreateTextureFromFileEx(CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice(), 
		_pcFileName, 0, 0, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 0, &ImageInfo, 0, &m_pTexture);

	m_uiWidth = ImageInfo.Width;
	m_uiHeight = ImageInfo.Height;

    if (FAILED(hr) )
    {
        return (false);
    }

	return (true);
}

void 
CTexture::OnDeviceLost()
{
}

void 
CTexture::OnDeviceReset()
{
}

/**
*
* This function returns the width of the texture
*
* @author Daniel Jay
* @return The width of the texture
*
*/
uint32 
CTexture::GetWidth() const
{
	return (m_uiWidth);
}

/**
*
* This function returns the height of the texture
*
* @author Daniel Jay
* @return The height of the texture
*
*/
uint32 
CTexture::GetHeight() const
{
	return (m_uiHeight);
}

/*
* GetTexture
* @author Rigardt de Vries
* @return LPDIRECT3DTEXTURE9
*/
LPDIRECT3DTEXTURE9
CTexture::GetTexture()
{
    return (m_pTexture);
}