// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   staticgraphic.cpp
//  Description :   staticgraphic.cppfor implementation of staticgraphic.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/billboard.h"
#include "../../engine/graphics and sound/billboardmanager.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/Totalcubedomination.h"
#include "../../engine/viewport/viewport.h"

// This Includes
#include "staticgraphic.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* 
* 
* 
* @author 
* @param 
* @return 
*/
CStaticGraphic::CStaticGraphic()
: m_uiBillboardID(BAD_ID)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_vec2Position = D3DXVECTOR2(0.0f, 0.0f);
}

/**
* 
* 
* 
* @author 
* @param 
* @return 
*/
CStaticGraphic::~CStaticGraphic()
{
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @param D3DXVECTOR3 _vec3Position
* @param uint32 _uiBillboardID
* @param uint32 _uiTextureID
* @return 
*/
bool
CStaticGraphic::Initialise(uint32 _uiBillboardID)
{
	CMenuItem::Initialise();

	m_uiBillboardID = _uiBillboardID;

	return (true);
}

/**
* 
* 
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void
CStaticGraphic::Process(float32 _fDeltaTick)
{
	//CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	if(true == m_bIsActive)
	{
		CTotalCubeDomination::GetInstance().GetRenderer()
			->AddToViewport(this, RENDERTYPE_SCREENALIGNED | RENDERTYPE_OPAQUE, 0);
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
CStaticGraphic::Draw()
{
	//// Draw the billboard.
	CBillboardManager::GetInstance().Draw(m_uiBillboardID);
}

/**
* 
* Returns the billboard ID number.
* 
* @author Rebeccah Cox
* @return uint32 s_uiBillboardID
*/
uint32
CStaticGraphic::GetBillboardID()
{
	return (m_uiBillboardID);
}

/**
* 
* Returns the world matrix.
* 
* @author  Rebeccah Cox
* @return D3DXMATRIX m_matWorld
*/
D3DXMATRIX
CStaticGraphic::GetWorldMatrix()
{
	return (m_matWorld);
}

/**
* 
* Resets to the state it needs to be in when entering the menu.
* 
* @author Rebeccah Cox
* @return void.
*/
void
CStaticGraphic::Reset()
{
	Initialise(m_uiBillboardID);
}
