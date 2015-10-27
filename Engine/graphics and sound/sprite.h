// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   sprite.h
//  Description :   Declaration for Csprite
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SPRITE_H__
#define __IGFEB10_MODULE_SPRITE_H__

// Library Includes
#include <d3dx9.h>

// Local Includes

// Types
struct TSpriteVertex
{
	D3DXVECTOR4 vec4Position;
	D3DXVECTOR2 vec2UV;
};

const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

// Prototypes
class CSprite
{
	// Member Functions
public:
	CSprite();
	~CSprite();

	bool Initialise(uint32 _uiTextureID, const RECT* _kpSourceRect);

	void SetSourceRect(const RECT& _krSourceRect);

	void OnDeviceLost();
	void OnDeviceReset();

	void Draw(const RECT& _krScreenRect);

protected:

private:

	// Member Variables
public:

protected:
	uint32 m_uiTextureID;
	D3DXVECTOR2 m_avec2UVCoords[4];

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;

private:

}; 

#endif // __IGFEB10_MODULE_SPRITE_H__

