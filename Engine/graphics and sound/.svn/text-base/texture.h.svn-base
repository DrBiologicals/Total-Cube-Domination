// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   texture.h
//  Description :   Declaration for Ctexture
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TEXTURE_H__
#define __IGFEB10_MODULE_TEXTURE_H__

// Library Includes
#include <d3dx9.h>
#include <string>

// Local Includes

// Types

// Prototypes


class CTexture
{
	// Member Functions
public:
	CTexture();
	~CTexture();

    bool Initialise(const char* _pcFileName);

	void OnDeviceLost();
	void OnDeviceReset();

	uint32 GetWidth() const;
	uint32 GetHeight() const;

    LPDIRECT3DTEXTURE9 GetTexture();

protected:

private:

	// Member Variables
public:

protected:
    LPDIRECT3DTEXTURE9 m_pTexture;

	uint32 m_uiWidth;
	uint32 m_uiHeight;

private:

}; 

#endif // __IGFEB10_MODULE_TEXTURE_H__

