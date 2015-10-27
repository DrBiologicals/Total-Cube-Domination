// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   faultymagplate.cpp
//  Description :   faultymagplate.cppfor implementation of faultymagplate.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/TextureManager.h"
#include "../../engine/totalcubedomination.h"
#include "../player objects/tank.h"

// This Includes
#include "faultymagplate.h"

// Static Variables

// Static Function Prototypes

// Implementation

CFaultyMagPlate::CFaultyMagPlate()
{

}

CFaultyMagPlate::~CFaultyMagPlate()
{

}

/*
* Initialise
* @author Rigardt de Vries
* @param _iY        the y value for the tile.
* @param _iX        the x value for the tile.
* @param _eFace     the face that the 
* @return bool
*/
bool
CFaultyMagPlate::Initialise(int32 _iX, int32 _iY, EFacePosition _eFace, uint32 _uiModelID, uint32 _uiTextureID, EFileDirection _eDir )
{
    // Set the position and side member variables in CTile.
	m_eFace = _eFace;
	m_iX = _iX;
	m_iY = _iY;

	switch (_eDir)
	{
		case DIR_LEFT:
		{
			m_vec3EffectDirection = -g_atUpRightDirectionVecs[_eFace].vec3Right;
			m_eDirection = DIRECTION_LEFT;
		}
		break;

		case DIR_RIGHT:
		{
			m_vec3EffectDirection = g_atUpRightDirectionVecs[_eFace].vec3Right;
			m_eDirection = DIRECTION_RIGHT;
		}
		break;

		case DIR_UP:
		{
			m_vec3EffectDirection = g_atUpRightDirectionVecs[_eFace].vec3Direction;
			m_eDirection = DIRECTION_UP;
		}
		break;

		case DIR_DOWN:
		{
			m_vec3EffectDirection = -g_atUpRightDirectionVecs[_eFace].vec3Direction;
			m_eDirection = DIRECTION_DOWN;
		}
		break;
	}

	m_vec3Position = g_atUpRightDirectionVecs[_eFace].vec3Up * 22.5f;

	m_vec3Position += g_atUpRightDirectionVecs[_eFace].vec3Right * ((_iX * 3.0f) - 21.0f);

	m_vec3Position -= g_atUpRightDirectionVecs[_eFace].vec3Direction * ((_iY * 3.0f) - 21.0f);

	D3DXVec3Cross(&m_vec3Right, &g_atUpRightDirectionVecs[_eFace].vec3Up, &m_vec3EffectDirection);

	// Set the world matrix using the vectors.
	m_matWorld._11 = m_vec3Right.x;
	m_matWorld._21 = g_atUpRightDirectionVecs[_eFace].vec3Up.x;
	m_matWorld._31 = m_vec3EffectDirection.x;

	m_matWorld._12 = m_vec3Right.y;
	m_matWorld._22 = g_atUpRightDirectionVecs[_eFace].vec3Up.y;
	m_matWorld._32 = m_vec3EffectDirection.y;

	m_matWorld._13 = m_vec3Right.z; 
	m_matWorld._23 = g_atUpRightDirectionVecs[_eFace].vec3Up.z; 
	m_matWorld._33 = m_vec3EffectDirection.z;

	m_matWorld._41 = m_vec3Position.x;
	m_matWorld._42 = m_vec3Position.y;
	m_matWorld._43 = m_vec3Position.z;

	m_bTraversable = true;

	m_iModelID = _uiModelID;
	m_iTextureID = _uiTextureID;

    D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_iModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

    m_tOBB.m_vec3Max.y = 3.0f;

	pMesh->UnlockVertexBuffer();

	CEntity::Initialise();

	return(true);
}

/*
* Process
* @author Rigardt de Vries
* @param _fDeltaTick        the game timer
* @return void
*/
void
CFaultyMagPlate::Process(float32 _fDeltaTick)
{
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);

	// Create bounding box.
	CreateAABB();
}

/*
* Draw
* @author Rigardt de Vries
* @return void
*/
void
CFaultyMagPlate::Draw()
{
    // Set the world matrix on the renderer.
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);

	// Set the texture for the flag plate.
	CTextureManager::GetInstance().SetTexture(0, m_iTextureID);

	// Draw the flag plate model.
	CModelManager::GetInstance().Draw(m_iModelID);
}

/*
* CauseEffect
* @author Rigardt de Vries
* @param _rTank         The tank to take the effect;
* @return void
*/
void
CFaultyMagPlate::CauseEffect(CTank &_rTank)
{
    _rTank.SetOnFaultyMagPlate(true, m_vec3EffectDirection);
}

/*
* RemoveCauseEffect
* @author Rigardt de Vries
* @param _rTank         The tank to take the effect;
* @return void
*/
void
CFaultyMagPlate::RemoveCauseEffect(CTank& _rTank)
{
    _rTank.SetOnFaultyMagPlate(false, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

EDirection
CFaultyMagPlate::GetDirection() const
{
	return(m_eDirection);
}