// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   breakablebarrier.cpp
//  Description :   breakablebarrier.cppfor implementation of breakablebarrier.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"

// This Includes
#include "breakablebarrier.h"

// Static Variables

// Static Function Prototypes


// Implementation
CBreakableBarrier::CBreakableBarrier()
: m_iHealth(60)
{

}

CBreakableBarrier::~CBreakableBarrier()
{

}

bool
CBreakableBarrier::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiTextureID)
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

	CEntity::Initialise();

	CreateAABB();

	return(true);
}

void
CBreakableBarrier::Process(float32 _fDeltaTick)
{
    //Add to the viewport
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
}

void
CBreakableBarrier::Draw()
{
    // Grab the renderer.
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);
    CTextureManager::GetInstance().SetTexture(0, m_iTextureID);
	CModelManager::GetInstance().Draw(m_iModelID);
}

void
CBreakableBarrier::Damage(int32 _iDamage)
{
	m_iHealth = m_iHealth - _iDamage;
}

bool
CBreakableBarrier::IsDestroyed()
{
    if (m_iHealth <= 0)
    {
        return (true);
    }
    return (false);
}