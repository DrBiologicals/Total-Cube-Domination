// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   billboard.cpp
//  Description :   CBillboard implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../totalcubedomination.h"
#include "renderer.h"
#include "../Viewport/camera.h"
#include "../Viewport/viewport.h"
#include "texturemanager.h"

// This Includes
#include "billboard.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* 
* Initialises the variables to default values.
* 
* @author Rebeccah Cox
*/
CBillboard::CBillboard()
: m_fWidth(0.0f)
, m_fHeight(0.0f)
{
}

/**
* 
* Deletes any dynamic memory allocated, and sets pointers to zero.
* 
* @author Rebeccah Cox
*/
CBillboard::~CBillboard()
{
	delete[] m_pVertices;
	m_pVertices = 0;

	m_pVertexBuffer->Release();
}

/**
* 
* Loads the mesh and material from file passed in.
* 
* @author Rebeccah Cox
* @param D3DXVECTOR3 _vec3Position - the center point of the billboard.
* @param const float32 _fWidth
* @param const float32 _fHeight
* @return void
*/
bool
CBillboard::Initialise(uint32 _uiTextureID, const float32 _fWidth, const float32 _fHeight,
					   const D3DXVECTOR2& _vec2Position)
{
	m_uiTextureID = _uiTextureID;

	// Local variables for mesh loading. 
	ID3DXBuffer* pAdjBuffer = 0;
	ID3DXBuffer* pMaterialBuffer = 0;
	DWORD dwNumMaterials = 0;

	// Store size.
	m_fWidth = _fWidth*0.5f;
	m_fHeight = _fHeight*0.5f;

	/********************************************************/

	// Vert data.
	m_pVertices = new TBillboardVertex[4];
	m_pVertices[0].vec4Position = D3DXVECTOR4(_vec2Position.x-m_fWidth, _vec2Position.y-m_fHeight, 1.0f, 1.0f);
	m_pVertices[1].vec4Position = D3DXVECTOR4(_vec2Position.x+m_fWidth, _vec2Position.y-m_fHeight, 1.0f, 1.0f);
	m_pVertices[2].vec4Position = D3DXVECTOR4(_vec2Position.x-m_fWidth, _vec2Position.y+m_fHeight, 1.0f, 1.0f);
	m_pVertices[3].vec4Position = D3DXVECTOR4(_vec2Position.x+m_fWidth, _vec2Position.y+m_fHeight, 1.0f, 1.0f);

	m_pVertices[0].vec2UV.x = 0.0f;
	m_pVertices[0].vec2UV.y = 0.0f;
	m_pVertices[1].vec2UV.x = 1.0f;
	m_pVertices[1].vec2UV.y = 0.0f;
	m_pVertices[2].vec2UV.x = 0.0f;
	m_pVertices[2].vec2UV.y = 1.0f;
	m_pVertices[3].vec2UV.x = 1.0f;
	m_pVertices[3].vec2UV.y = 1.0f;

	CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->CreateVertexBuffer((sizeof(TBillboardVertex) * 4),
		D3DUSAGE_WRITEONLY, BILLBOARD_FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);

	LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	TBillboardVertex* pData = 0;

	m_pVertexBuffer->Lock(0, 0, (void**)(&pData), 0);

	for(uint32 i = 0 ; i < 4; ++i)
	{
		pData[i] = m_pVertices[i];
	}

	m_pVertexBuffer->Unlock();

	return (true);
}

/**
* 
* Sets the billboards world matrix to the inverse of the cameras view matrix.
* Sets the position of the object in the billboards world matrix.
* Draws the mesh.
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	// Set texture
	CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);

	// Draw
	pDevice->SetFVF(BILLBOARD_FVF);
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TBillboardVertex));
	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboard::OnDeviceLost()
{
	if(0 != m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
	}
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboard::OnDeviceReset()
{
	CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->CreateVertexBuffer((sizeof(TBillboardVertex) * 4),
		D3DUSAGE_WRITEONLY, BILLBOARD_FVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);

	LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	TBillboardVertex* pData = 0;

	m_pVertexBuffer->Lock(0, 0, (void**)(&pData), 0);

	for(uint32 i = 0 ; i < 4; ++i)
	{
		pData[i] = m_pVertices[i];
	}

	m_pVertexBuffer->Unlock();
}

/**
* 
* Returns a pointer to the ID3DXMesh associated with this object.
* 
* @author Rebeccah Cox
* @return ID3DXMesh* m_pMesh
*/
ID3DXMesh*
CBillboard::GetModel()
{
	//return (m_pMesh);
	return (0);
}

/**
* 
* Returns the width variable to scale the billboard with.
* 
* @author Rebeccah Cox
* @return float32 m_fWidth
*/
float32
CBillboard::GetWidth()
{
	return (m_fWidth);
}

/**
* 
* Returns the height variable to scale the billboard with.
* 
* @author Rebeccah Cox
* @return float32 m_fHeight
*/
float32
CBillboard::GetHeight()
{
	return (m_fHeight);
}

void
CBillboard::SetTextureID(uint32 _uiTextureID)
{
	m_uiTextureID = _uiTextureID;
}
