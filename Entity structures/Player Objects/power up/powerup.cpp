// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   powerup.cpp
//  Description :   powerup.cppfor implementation of powerup.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../../engine/graphics and sound/renderer.h"
#include "../../../engine/graphics and sound/model.h"
#include "../../../engine/graphics and sound/modelmanager.h"
#include "../../../engine/graphics and sound/texturemanager.h"
#include "../../../engine/totalcubedomination.h"
#include "../tank.h"

// This Includes
#include "powerup.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* 
* Constructor
* 
* @author Rebeccah Cox
*/
CPowerUp::CPowerUp()
: m_ePowerUpType(POWERUP_MAX)
, m_bIsActive(true)
, m_eFace(FACE_NONE)
, m_uiModelID(0)
, m_uiTextureID(0)
{
	m_vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

/**
* 
* Destructor.
* 
* @author Rebeccah Cox
*/
CPowerUp::~CPowerUp()
{
}

/**
* 
* Calculates the position of the power-up using the g_atUpRightDirectionVecs and the EFacePosition 
*	passed in. 
* Calculates the bounding box, and sets power-up to active.
* 
* @author Rebeccah Cox
* @param int32 _iX					- the X position relevant to the face.
* @param int32 _iY					- the Y position relevant to the face.
* @param EPowerUpType _ePowerUpType - either POWERUP_INVISIBILITY or POWERUP_OVERSHIELD
* @param EFacePosition _eFace		- which face the power-up is on.
* @param uint32 _uiModelID			- model ID to use with CModelManager.
* @param uint32 _uiTextureID		- texture ID to use with CTextureManager.
* @return bool						- returns true if CMesh locking and unlocking are successful.
*/
bool
CPowerUp::Initialise(const D3DXVECTOR3& _rvec3Position, EPowerUpType _ePowerUpType, EFacePosition _eFace, uint32 _uiModelID,
					 uint32 _uiTextureID)
{
	m_bIsActive = true;

	// Set the position and side member variables in CTile.
	m_eFace = _eFace;
	m_ePowerUpType = _ePowerUpType;

	m_vec3Position = _rvec3Position;

	// Set the world matrix using the vectors.
	m_matWorld._11 = g_atUpRightDirectionVecs[_eFace].vec3Right.x;
	m_matWorld._21 = g_atUpRightDirectionVecs[_eFace].vec3Up.x;
	m_matWorld._31 = g_atUpRightDirectionVecs[_eFace].vec3Direction.x;

	m_matWorld._12 = g_atUpRightDirectionVecs[_eFace].vec3Right.y;
	m_matWorld._22 = g_atUpRightDirectionVecs[_eFace].vec3Up.y;
	m_matWorld._32 = g_atUpRightDirectionVecs[_eFace].vec3Direction.y;

	m_matWorld._13 = g_atUpRightDirectionVecs[_eFace].vec3Right.z; 
	m_matWorld._23 = g_atUpRightDirectionVecs[_eFace].vec3Up.z; 
	m_matWorld._33 = g_atUpRightDirectionVecs[_eFace].vec3Direction.z;

	m_matWorld._41 = m_vec3Position.x;
	m_matWorld._42 = m_vec3Position.y;
	m_matWorld._43 = m_vec3Position.z;

	m_uiModelID = _uiModelID;
	if(BAD_ID == m_uiModelID)
	{
		return (false);
	}

	m_uiTextureID = _uiTextureID;
	if(BAD_ID == m_uiTextureID)
	{
		return (false);
	}

    D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_uiModelID)->GetModel();

	if(FAILED(pMesh->LockVertexBuffer(0, (void**)&pFirstVertex)))
	{
		return (false);
	}

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	if(FAILED(pMesh->UnlockVertexBuffer()))
	{
		return (false);
	}

	m_tOBB.m_vec3Max.y = 3.0f;

	CEntity::Initialise();

	CreateAABB();

	return(true);
}

/**
* 
* If the power-up is active (not picked up), it is added to all of the viewports.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void 
CPowerUp::Process(float32 _fDeltaTick)
{
	if(true == m_bIsActive)
	{
		CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
        CreateAABB();
	}
}

/**
* 
* If the power-up is active, the world matrix and texture are set on the device, and then it is drawn.
* If it is not active, it is not added to the viewports anyway, so this check just avoids extra 
*	function calls.
* 
* @author Rebeccah Cox
* @return void
*/
void
CPowerUp::Draw()
{
    if(true == m_bIsActive)
    {
	    // Set the world matrix on the renderer.
	    CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);

		// Set the texture for the flag plate.
		CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);

	    // Draw the flag plate model.
	    CModelManager::GetInstance().Draw(m_uiModelID);
    }
}

/*
* 
* @author
* @return EPowerUpType 
*/
EPowerUpType
CPowerUp::GetPowerUpType()
{
	return (m_ePowerUpType);
}

/**
* 
* Sets the member variable m_bActive to the bool value passed in.
* When true, it activates the process and draw functionality.
* 
* @author Rebeccah Cox
* @param bool _bIsActive - true for active, false for not active.
*/
void
CPowerUp::SetActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}

/**
* 
* Returns true if the power-up is currently active (not picked up), or false 
*	if it is not active (already picked up).
* 
* @author Rebeccah Cox
* @return bool m_bIsActive
*/
bool
CPowerUp::IsActive()
{
	return(m_bIsActive);
}