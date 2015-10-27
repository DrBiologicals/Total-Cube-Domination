// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flamegrate.cpp
//  Description :   flamegrate.cppfor implementation of flamegrate.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/soundmanager.h"
#include "../particle/emittermanager.h"

// This Includes

#include "flamegrate.h"

// Static Variables
uint32 CFlameGrate::s_uiSoundID = BAD_ID;

// Static Function Prototypes


// Implementation

CFlameGrate::CFlameGrate()
: m_iBurstDelay(0)
, m_iTimeLeft(0)
, m_iEmitterID(0)
, m_fCurrentTime(0.0f)
, m_bActive(false)
, m_fDamagePerSecond(0.0f)
{

}

CFlameGrate::~CFlameGrate()
{

}

bool
CFlameGrate::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiTextureID)
{
	// Initialise all the variables that are passed in
	D3DXMatrixIdentity(&m_matWorld); 

	m_iX = _iX;
	m_iY = _iY;
	m_eFace = _eSide;

	m_vec3Position = g_atUpRightDirectionVecs[_eSide].vec3Up * 22.5f;

	m_vec3Position += g_atUpRightDirectionVecs[_eSide].vec3Right * ((_iX * 3.0f) - 21.0f);

	m_vec3Position -= g_atUpRightDirectionVecs[_eSide].vec3Direction * ((_iY * 3.0f) - 21.0f);

	m_vec3Up = g_atUpRightDirectionVecs[_eSide].vec3Up;
	m_vec3Right = g_atUpRightDirectionVecs[_eSide].vec3Right;
	m_vec3Direction = g_atUpRightDirectionVecs[_eSide].vec3Direction;

	// Set the world matrix using the vectors
	m_matWorld._11 = m_vec3Right.x;
	m_matWorld._21 = m_vec3Up.x;
	m_matWorld._31 = m_vec3Direction.x;
	m_matWorld._12 = m_vec3Right.y;
	m_matWorld._22 = m_vec3Up.y;
	m_matWorld._32 = m_vec3Direction.y;
	m_matWorld._13 = m_vec3Right.z; 
	m_matWorld._23 = m_vec3Up.z; 
	m_matWorld._33 = m_vec3Direction.z;
	m_matWorld._41 = m_vec3Position.x;
    m_matWorld._42 = m_vec3Position.y;
    m_matWorld._43 = m_vec3Position.z;

	m_bTraversable = true;

	CEmitterManager::GetInstance().AddEmitter(30, m_vec3Position, PARTICLE_FLAME, TEAM_GREEN, this,0);

	m_iModelID = _uiModelID;
	m_iTextureID = _uiTextureID;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_iModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex,
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	m_tOBB.m_vec3Max.y = 3.0f;

	CEntity::Initialise();
 
	CreateAABB();

	m_iBurstDelay = 1 + rand() % 3;
	m_iTimeLeft  = 1 + rand() % 3;

	if(s_uiSoundID==BAD_ID)
	{
		s_uiSoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/tile_fire2.wav",0.2f,false,12.0f);
	}

	m_fDamagePerSecond = 20.0f;

	return(true);


}

void
CFlameGrate::Process(float32 _fDeltaTick)
{
	m_fCurrentTime += _fDeltaTick;

	if((m_fCurrentTime - m_iBurstDelay) > m_iTimeLeft)
	{
		m_bActive = false;
	}

	if((m_fCurrentTime - m_iBurstDelay) > (m_iTimeLeft * 2.0f))
	{
		m_fCurrentTime = 0.0f;
	}

	if((m_fCurrentTime - m_iBurstDelay) < m_iTimeLeft && m_fCurrentTime > 0.0f)
	{
		m_bActive = true;
		CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundID, m_vec3Position);
	}

	//Add to the viewport
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
}

void
CFlameGrate::Draw()
{
	// Grab the renderer.
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);
    CTextureManager::GetInstance().SetTexture(0, m_iTextureID);
	CModelManager::GetInstance().Draw(m_iModelID);
}

bool
CFlameGrate::GetActive()
{
	return(m_bActive);
}

/**
*
* Returns the amount of damage done per second when the flame grate is active.
* 
* @author Rebeccah Cox
* @return float32 m_fDamagePerSecond
*/
float32
CFlameGrate::GetDamagePerSecond()
{
	return (m_fDamagePerSecond);
}
