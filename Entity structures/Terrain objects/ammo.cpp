// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   ammo.cpp
//  Description :   ammo.cppfor implementation of ammo.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"

// This Includes

#include "ammo.h"

// Static Variables
const float32 MAX_AMMO_RECHARGE = 6.0f;

// Static Function Prototypes

// Implementation
CAmmo::CAmmo()
: m_iLightModelID(BAD_ID)
, m_bCanBeTriggered(true)
, m_fAmmoTimer(0.0f)
, m_eTeam(TEAM_NEUTRAL)
{

}
CAmmo::~CAmmo()
{

}
bool
CAmmo::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiLightModelID,
					uint32 _uiTextureID, ETeam _eTeam)
{
	// Initialise all the variables that are passed in
	D3DXMatrixIdentity(&m_matWorld); 

	m_iX = _iX;
	m_iY = _iY;
	m_eFace = _eSide;
	m_eTeam = _eTeam;

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

	m_iModelID = _uiModelID;
	m_iLightModelID = _uiLightModelID;
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

	return(true);
}
void
CAmmo::Process(float32 _fDeltaTick)
{
	if(false == m_bCanBeTriggered)
	{
		m_fAmmoTimer += _fDeltaTick;

		if(MAX_AMMO_RECHARGE <= m_fAmmoTimer)
		{
			m_bCanBeTriggered = true;
			m_fAmmoTimer = 0.0f;
		}
	}

	//Add to the viewport
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);
}
void
CAmmo::Draw()
{
	// Grab the renderer.
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);
    CTextureManager::GetInstance().SetTexture(0, m_iTextureID);
	CModelManager::GetInstance().Draw(m_iModelID);

	if(true == m_bCanBeTriggered)
	{
		pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//CTextureManager::GetInstance().SetTexture(1, m_iTextureID);
		CModelManager::GetInstance().Draw(m_iLightModelID);

		pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

/**
* 
* Returns true if the plate can be triggered by a tank, or false 
*	if it is recharging.
* 
* @author Rebeccah Cox
* @return bool m_bCanBeTriggered - true if plate has recharged to MAX_AMMO_RECHARGE
*/
bool
CAmmo::CanBeTriggered()
{
	return (m_bCanBeTriggered);
}

/**
* 
* Triggering sets the m_bCanBeTriggered value to false, which starts the timer for recharging. 
* 
* @author Rebeccah Cox
* @return void
*/
void
CAmmo::Trigger()
{
	m_bCanBeTriggered = false;
}

/*
*
* Gets the team which the tank is currently on
*
* @author Rebeccah Cox
* @return Returns the team which the ammo plate belongs to.
*
*/
ETeam
CAmmo::GetTeam()
{
	return(m_eTeam);
}