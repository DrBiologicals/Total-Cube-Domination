// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   sprite.cpp
//  Description :   sprite.cppfor implementation of sprite.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../totalcubedomination.h"
#include "renderer.h"
#include "texturemanager.h"
#include "texture.h"

// This Includes
#include "sprite.h"

// Static Variables

// Static Function Prototypes

// Implementation
CSprite::CSprite()
: m_uiTextureID(BAD_ID)
, m_pVertexBuffer(0)
{
	ZeroMemory(m_avec2UVCoords, sizeof(m_avec2UVCoords));
}

CSprite::~CSprite()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = 0;
	}
}

/**
*
* This function initialises the sprite with the specified texture and source rect
*
* @author Daniel Jay
* @param _uiTextureID The ID of the sprite's texture
* @param _krSourceRect The rect from the texture to use
* @return True if the initialisation was successful
*
*/
bool
CSprite::Initialise(uint32 _uiTextureID, const RECT* _kpSourceRect)
{
	m_uiTextureID = _uiTextureID;

	if (_kpSourceRect)
	{
		SetSourceRect(*_kpSourceRect);
	}

	// Create vertex buffer
	CTotalCubeDomination::GetInstance().GetRenderer()->
		GetDevice()->CreateVertexBuffer(sizeof(TSpriteVertex) * 4, 
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, SPRITE_FVF, 
		D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);

	return (true);
}

/**
*
* This function sets the source rect for the sprite
*
* @author Daniel Jay
* @param _krSourceRect The rect from the texture to use
*
*/
void
CSprite::SetSourceRect(const RECT& _krSourceRect)
{
	// Create UV mappings from texture and source rect
	float32 fTextureWidth = static_cast<float32>(CTextureManager::GetInstance().GetTexture(m_uiTextureID)->GetWidth());
	float32 fTextureHeight = static_cast<float32>(CTextureManager::GetInstance().GetTexture(m_uiTextureID)->GetHeight());

	D3DXVECTOR2 vec2TopLeft;
	vec2TopLeft.x = static_cast<float32>(_krSourceRect.left) / fTextureWidth;
	vec2TopLeft.y = static_cast<float32>(_krSourceRect.top) / fTextureHeight;

	D3DXVECTOR2 vec2BottomRight;
	vec2BottomRight.x = static_cast<float32>(_krSourceRect.right) / fTextureWidth;
	vec2BottomRight.y = static_cast<float32>(_krSourceRect.bottom) / fTextureHeight;

	m_avec2UVCoords[0] = D3DXVECTOR2(vec2TopLeft);
	m_avec2UVCoords[1] = D3DXVECTOR2(vec2BottomRight.x, vec2TopLeft.y);
	m_avec2UVCoords[2] = D3DXVECTOR2(vec2TopLeft.x, vec2BottomRight.y);
	m_avec2UVCoords[3] = D3DXVECTOR2(vec2BottomRight);
}

/**
*
* This function releases Direct3D resources that need to be recreated after a lost device
*
* @author Daniel Jay
*
*/
void 
CSprite::OnDeviceLost()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = 0;
	}
}

/**
*
* This function recreates Direct3D resources that need to be recreated on a reset device
*
* @author Daniel Jay
*
*/
void 
CSprite::OnDeviceReset()
{
	// Recreate vertex buffer
	CTotalCubeDomination::GetInstance().GetRenderer()->
		GetDevice()->CreateVertexBuffer(sizeof(TSpriteVertex) * 4, 
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, SPRITE_FVF, 
		D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);
}

/**
*
* This function draws the sprite
*
* @author Daniel Jay
*
*/
void
CSprite::Draw(const RECT& _krScreenRect)
{
	LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	// Update vertex buffer with screen rect
	TSpriteVertex* pData = 0;

	m_pVertexBuffer->Lock(0, 0, (void**)(&pData), D3DLOCK_DISCARD);

	for (int32 i = 0; i < 4; ++i)
	{
		pData[i].vec4Position.w = 1.0f;
		pData[i].vec4Position.z = 0.0f;
		pData[i].vec2UV = m_avec2UVCoords[i];
	}

	// Top left vertex
	pData[0].vec4Position.x = static_cast<float32>(_krScreenRect.left);
	pData[0].vec4Position.y = static_cast<float32>(_krScreenRect.top);

	// Top right vertex
	pData[1].vec4Position.x = static_cast<float32>(_krScreenRect.right);
	pData[1].vec4Position.y = static_cast<float32>(_krScreenRect.top);

	// Bottom left vertex
	pData[2].vec4Position.x = static_cast<float32>(_krScreenRect.left);
	pData[2].vec4Position.y = static_cast<float32>(_krScreenRect.bottom);

	// Bottom right vertex
	pData[3].vec4Position.x = static_cast<float32>(_krScreenRect.right);
	pData[3].vec4Position.y = static_cast<float32>(_krScreenRect.bottom);

	m_pVertexBuffer->Unlock();

	// Set texture
	CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);

	// Draw
	pDevice->SetFVF(SPRITE_FVF);
	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TSpriteVertex));
	
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}