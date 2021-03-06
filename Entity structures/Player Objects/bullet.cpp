// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bullet.cpp
//  Description :   bullet.cppfor implementation of bullet.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/soundmanager.h"
#include "tank.h"
#include "../Terrain objects/tower/tower.h"
#include "../renderentity.h"

// This Includes
#include "bullet.h"

// Static Variables

// Static Function Prototypes
uint32 CBullet::s_uiModelID = BAD_ID;
uint32 CBullet::s_uiTextureID = BAD_ID;
uint32 CBullet::s_uiGreenTextureID = BAD_ID;
uint32 CBullet::s_uiPurpleTextureID = BAD_ID;
uint32 CBullet::s_uiSoundFireID1 = BAD_ID;
uint32 CBullet::s_uiSoundFireID2 = BAD_ID;
uint32 CBullet::s_uiSoundFireID3 = BAD_ID;

// Implementation

CBullet::CBullet()
: m_pTankOwner(0)
, m_pTowerOwner(0)
, m_eOwnerType(OWNER_MAX)
, m_eTeam(TEAM_NEUTRAL)
{
	
}

CBullet::~CBullet()
{
	m_pTankOwner = 0;
	m_pTowerOwner = 0;
}

void
CBullet::LoadAssets()
{
	if(s_uiModelID == BAD_ID)
	{
		s_uiModelID = CModelManager::GetInstance().CreateModel("models/wpn_plasma.x");
	}
    if(s_uiTextureID == BAD_ID)
	{
		s_uiTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_plasma_neutral.png");
	}
	if(s_uiGreenTextureID == BAD_ID)
	{
		s_uiGreenTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_plasma_green.png");
	}
	if(s_uiPurpleTextureID == BAD_ID)
	{
		s_uiPurpleTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_plasma_purple.png");
	}
	if((s_uiSoundFireID1 == BAD_ID)||(0==CSoundManager::GetInstance().GetSound(s_uiSoundFireID1)))
	{
		s_uiSoundFireID1 = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_plasma_init1.wav",0.4f,false);
		s_uiSoundFireID2 = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_plasma_init2.wav",0.4f,false);
		s_uiSoundFireID3 = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_plasma_init3.wav",0.4f,false);
	}
}

/*
* Initialise
* @author Rigardt de Vries
* @param _vec3Position          the position of the position
* @param _pOwner				The owner, either a tank or a tower.
* @param _eOwnerType			The type of the owner, OWNER_TANK or OWNER_TOWER.
* @return
*/
bool
CBullet::Initialise(D3DXVECTOR3 _vec3Position, CTank* _pTankOwner, D3DXVECTOR3 _vec3Direction,
							D3DXVECTOR3 _vec3Right)
{
	CRenderEntity::Initialise();

	SetTankOwner(_pTankOwner);
	m_eTeam = _pTankOwner->GetTeam();
	m_eOwnerType = OWNER_TANK;

	m_vec3Position = _vec3Position;
	m_vec3Right = _vec3Right;
	m_vec3Direction = _vec3Direction;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(s_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	m_fCurrentTime = 0.0f;

	int32 iSoundID = static_cast<int32>(RandomFloat()*3);
	switch(iSoundID)
	{
		case 0:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID1, m_vec3Position);
			break;
		case 1:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID2, m_vec3Position);
			break;
		default:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID3, m_vec3Position);
			break;
	}

	return (true);
}

bool
CBullet::Initialise(D3DXVECTOR3 _vec3Position, CTower* _pTowerOwner, D3DXVECTOR3 _vec3Direction,
							D3DXVECTOR3 _vec3Right)
{
	CRenderEntity::Initialise();

	SetTowerOwner(_pTowerOwner);
	m_eTeam = _pTowerOwner->GetTeam();
	m_eOwnerType = OWNER_TOWER;

	m_vec3Position = _vec3Position;
	m_vec3Right = _vec3Right;
	m_vec3Direction = _vec3Direction;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(s_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	m_fCurrentTime = 0.0f;

	int32 iSoundID = static_cast<int32>(RandomFloat()*3);
	switch(iSoundID)
	{
		case 0:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID1, m_vec3Position);
			break;
		case 1:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID2, m_vec3Position);
			break;
		default:
			CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundFireID3, m_vec3Position);
			break;
	}

	return (true);
}

/*
* Process
* @author Rigardt de Vries
* @param _fDeltaTick
* @return void
*/
void
CBullet::Process(float32 _fDeltaTick)
{
	if(GetAlive())
	{
		m_fCurrentTime += _fDeltaTick;

		m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

		if (m_eFacePosition == FACE_TOP || m_eFacePosition == FACE_BOTTOM)
        {
            m_vec3Position.y = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up.y * 24.0f;
        }
        else if (m_eFacePosition == FACE_LEFT || m_eFacePosition == FACE_RIGHT)
        {
            m_vec3Position.x = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up.x * 24.0f;
        }
        else if (m_eFacePosition == FACE_FRONT || m_eFacePosition == FACE_BACK)
        {
            m_vec3Position.z = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up.z * 24.0f;
        }

		m_vec3Position += m_vec3Direction * _fDeltaTick * m_fMovementSpeed;

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

		CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);

		CreateAABB();

		if(m_fCurrentTime > 5.0f)
		{
			SetAlive(false);
		}
	}
}

/*
* Draw
* @author Rigardt de Vries
* @return void
*/
void
CBullet::Draw()
{
	if(GetAlive())
	{
		CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

		pRenderer->SetWorldMatrix(m_matWorld);
		switch(m_eTeam)
		{
		case TEAM_NEUTRAL:
			CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
			break;
		case TEAM_GREEN:
			CTextureManager::GetInstance().SetTexture(0, s_uiGreenTextureID);
			break;
		case TEAM_PURPLE:
			CTextureManager::GetInstance().SetTexture(0, s_uiPurpleTextureID);
			break;
		}
		CModelManager::GetInstance().Draw(s_uiModelID);
	}
}

/*
* GetMoveSpeed
* @author Rigardt de Vries
* @return float32
*/
float32
CBullet::GetMoveSpeed()
{
	return (m_fMovementSpeed);
}

/*
* SetMoveSpeed
* @author Rigardt de Vries
* @param _fMoveSpeed        the new movement speed
* @return void
*/
void
CBullet::SetMoveSpeed(float32 _fMoveSpeed)
{
    m_fMovementSpeed = _fMoveSpeed;
}

/*
* GetWorldMatrix
* @author Rigardt de Vries
* @return D3DXMATRIX&
*/
D3DXMATRIX&
CBullet::GetWorldMatrix()
{
	return (m_matWorld);
}

/*
* GetDamage
* @author Rigardt de Vries
* @return float32
*/
float32
CBullet::GetDamage()
{
	return (m_fDamage);
}

/*
* SetDamage
* @author Rigardt de Vries
* @param _fDamage       the new Damage
* @return void
*/
void
CBullet::SetDamage(float32 _fDamage)
{
    m_fDamage = _fDamage;
}

/**
* 
* Sets the tank owner to the pointer passed in, sets the tower owner to zero.
* Sets the owner type to OWNER_TANK.
* 
* @author Rebeccah Cox
* @param CTank* _pTankOwner - pointer to new CTank owner.
* @return void
*/
void
CBullet::SetTankOwner(CTank* _pTankOwner)
{
	m_pTankOwner = _pTankOwner;
	m_pTowerOwner = 0;
	m_eOwnerType = OWNER_TANK;
}

/**
* 
* Sets the tank owner to the pointer passed in, sets the tower owner to zero.
* Sets the owner type to OWNER_TOWER.
* 
* @author Rebeccah Cox
* @param CTower* _pTowerOwner - pointer to new CTower owner.
* @return void
*/
void
CBullet::SetTowerOwner(CTower* _pTowerOwner)
{
	m_pTankOwner = 0;
	m_pTowerOwner = _pTowerOwner;
	m_eOwnerType = OWNER_TANK;
}

CTank*
CBullet::GetTankOwner()
{
	return (m_pTankOwner);
}

CTower*
CBullet::GetTowerOwner()
{
	return (m_pTowerOwner);
}

/**
* 
* Returns the owner type, either OWNER_TANK or OWNER_TOWER.
* OWNER_MAX is the null/default value.
* 
* @author Rebeccah Cox
* @return EOwnerType m_eOwnerType - which class the owner is.
*/
EOwnerType
CBullet::GetOwnerType()
{
	return (m_eOwnerType);
}

/*
* SetModelAndTextureID
* @author Rigardt de Vries
* @param _uiTextureID           the ID for a texture
* @param _uimodelID             the ID for a model
* @return void
*/
void 
CBullet::SetModelAndTextureID(uint32 _uiTextureID, uint32 _uiModelID, uint32 _uiGreenTextureID, uint32 _uiPurpleTextureID)
{
    s_uiTextureID = _uiTextureID;
    s_uiModelID = _uiModelID;
    s_uiGreenTextureID = _uiGreenTextureID;
    s_uiPurpleTextureID = _uiPurpleTextureID;
}

void
CBullet::StartTransition(EFacePosition _eTargetFace)
{
   /* if (!m_bTransitioning)
    {
	    m_bTransitioning = true;

        m_eTargetFace = _eTargetFace;

        m_quatOriginAngle = g_aquatFaceQuaternions[m_eFacePosition];

	    m_quatTransitionAngle = g_aquatFaceQuaternions[m_eTargetFace];
    }*/

	EFacePosition eFace = m_eFacePosition;

    switch (_eTargetFace)
    {
		float32 _fDirDot;
		float32 _fRightDot;
		
    case FACE_FRONT:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            m_eFacePosition = FACE_FRONT;
			
            m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			if (eFace == FACE_TOP)
			{
				m_vec3Position -= (m_vec3Direction / m_vec3Direction.y) * 1.5f;

			}
			else if (eFace == FACE_LEFT)
			{
				m_vec3Position += (m_vec3Direction / m_vec3Direction.x) * 1.5f;
			}
			else if (eFace == FACE_RIGHT)
			{
				m_vec3Position -= (m_vec3Direction / m_vec3Direction.x) * 1.5f;
			}
        }
        break;
    case FACE_BACK:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            m_eFacePosition = FACE_BACK;

			 m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			if (eFace == FACE_BOTTOM)
			{
				m_vec3Position += (m_vec3Direction / m_vec3Direction.y) * 1.5f;
			}
			else if (eFace == FACE_LEFT)
			{
				m_vec3Position += (m_vec3Direction / m_vec3Direction.x) * 1.5f;
			}
			else if (eFace == FACE_RIGHT)
			{
				m_vec3Position -= (m_vec3Direction / m_vec3Direction.x) * 1.5f;
			}
        }
        break;
    case FACE_TOP:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            // moving onto the top
            m_eFacePosition = FACE_TOP;

			 m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			m_vec3Position += (m_vec3Direction / m_vec3Direction.z) * 1.5f;
        }
        break;
    case FACE_BOTTOM:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            // moving onto the bottom
            m_eFacePosition = FACE_BOTTOM;			

			 m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			m_vec3Position -= (m_vec3Direction / m_vec3Direction.z) * 1.5f;
        }
        break;
    case FACE_LEFT:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            m_eFacePosition = FACE_LEFT;

			 m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			if (eFace == FACE_FRONT)
			{
				m_vec3Position += (m_vec3Direction / m_vec3Direction.z) * 1.5f;
			}
			else if (eFace == FACE_BACK)
			{
				m_vec3Position -= (m_vec3Direction / m_vec3Direction.z) * 1.5f;
			}
        }
        break;
    case FACE_RIGHT:
        {
			_fDirDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction);
			_fRightDot = D3DXVec3Dot(&m_vec3Direction, &g_atUpRightDirectionVecs[m_eFacePosition].vec3Right);

            m_eFacePosition = FACE_RIGHT;

			 m_vec3Direction = _fDirDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Direction;
	        m_vec3Right = _fRightDot * g_atUpRightDirectionVecs[m_eFacePosition].vec3Right;

	        m_vec3Direction += m_vec3Right;
			m_vec3Up = g_atUpRightDirectionVecs[m_eFacePosition].vec3Up;

			if (eFace == FACE_FRONT)
			{
				m_vec3Position += (m_vec3Direction / m_vec3Direction.z) * 1.5f;
			}
			else if (eFace == FACE_BACK)
			{
				m_vec3Position -= (m_vec3Direction / m_vec3Direction.z) * 1.5f;
			}
        }
        break;
    }

	D3DXVec3Cross(&m_vec3Right, &m_vec3Up, &m_vec3Direction);
}

/*
* Sets the bullet alive bool
* @author Rigardt de Vries
* @param __bAlive           the new bool value
* @return void
*/
void 
CBullet::SetAlive(bool _bAlive)
{
    m_bAlive = _bAlive;
}

/**
*
* This function returns the direction of the bullet
*
* @author Daniel Jay
* @return The direction of the bullet
*
*/
const D3DXVECTOR3&
CBullet::GetDirection() const
{
	return (m_vec3Direction);
}

/*
* This function returns the right vector of the bulelt
* @author Rigardt de Vries
* @return the right vector of the bullet
*/
const D3DXVECTOR3&
CBullet::GetRight() const
{
    return (m_vec3Right);
}

/*
* This function returns the up vector of the bulelt
* @author Rigardt de Vries
* @return the up vector of the bullet
*/
const D3DXVECTOR3&
CBullet::GetUp() const
{
    return (m_vec3Up);
}