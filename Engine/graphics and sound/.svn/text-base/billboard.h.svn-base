// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   billboard.h
//  Description :   Declaration for CBillboard
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BILLBOARD_H__
#define __IGFEB10_MODULE_BILLBOARD_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes

// Types
struct TBillboardVertex
{
	D3DXVECTOR4 vec4Position;
	D3DXVECTOR2 vec2UV;
};

const DWORD BILLBOARD_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;
//const DWORD BILLBOARD_FVF = D3DFVF_XYZ | D3DFVF_TEX1;

// Prototypes

class CBillboard
{
	// Member Functions
public:
	CBillboard();
	~CBillboard();
	
	bool Initialise(uint32 _uiTextureID, const float32 _fWidth, const float32 _fHeight,
					const D3DXVECTOR2& _vec2Position);
	
	void Draw();

	void OnDeviceLost();
    void OnDeviceReset();

	ID3DXMesh* GetModel();

	float32 GetWidth();
	float32 GetHeight();

	void SetTextureID(uint32 _uiTextureID);
	
protected:

private:

	// Member Variables
public:

protected:

private:
	float32 m_fWidth;
	float32 m_fHeight;

	uint32 m_uiTextureID;

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;

	TBillboardVertex* m_pVertices;

}; 

#endif // __IGFEB10_MODULE_BILLBOARD_H__

