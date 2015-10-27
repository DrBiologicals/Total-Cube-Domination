// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   empbomb.cpp
//  Description :   empbomb.cppfor implementation of empbomb.h
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

// This Includes
#include "empbomb.h"

// Static Variables

// Static Function Prototypes
uint32 CEMPBomb::s_uiModelID = BAD_ID;
uint32 CEMPBomb::s_uiTextureID = BAD_ID;
uint32 CEMPBomb::s_uiExpldModelID = BAD_ID;
uint32 CEMPBomb::s_uiExpldTextureID = BAD_ID;
uint32 CEMPBomb::s_uiSoundID = BAD_ID;
uint32 CEMPBomb::s_uiExpldSoundID = BAD_ID;
uint32 CEMPBomb::s_uiEmptySoundID = BAD_ID;

// Implementation

CEMPBomb::CEMPBomb()
: m_fBlastRadius(0.0f)
, m_fMaxDistance(12.0f)
, m_fCurrentDistance(0.0f)
, m_fExplodeTimer(0.0f)
, m_fMaxBlastRadius(6.0f)
, m_bDetonating(false)
{
}

CEMPBomb::~CEMPBomb()
{
	m_pTankOwner = 0;
}

void
CEMPBomb::LoadAssets()
{
	if (s_uiModelID == BAD_ID)
	{
		s_uiModelID =  CModelManager::GetInstance().CreateModel("models/wpn_emp.x");
		s_uiExpldModelID = CModelManager::GetInstance().CreateModel("models/eff_emp.x");
	}

	if (s_uiTextureID == BAD_ID)
	{
		s_uiTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_emp.png");
		s_uiExpldTextureID = CTextureManager::GetInstance().CreateTexture("textures/eff_emp.png");
	}

	if (s_uiSoundID == BAD_ID)
	{
		s_uiSoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_emp_init.wav", 0.5f, false,50.0f);
		s_uiExpldSoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_emp_detonate.wav", 0.6f, false, 75.0f);
		s_uiEmptySoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_emp_empty.wav", 0.5f, false, 5.0f);
	}
}
/*
* Initialise
* @author Rigardt de Vries
* @param _vec3Position      the starting position of the emp bomb.
* @param _pTankowner        the onwer of this empbomb.
* @param _uiTextureID       the texture's ID.
* @param _uiModelID         the model's ID.
* @return bool
*/
bool
CEMPBomb::Initialise(D3DXVECTOR3 _vec3Position, CTank *_pTankOwner, D3DXVECTOR3 _vec3Direction, D3DXVECTOR3 _vec3Right)
{
	SetOwner(_pTankOwner);

	m_vec3Position = _vec3Position;
	m_vec3Direction = _vec3Direction;
	m_vec3Right = _vec3Right;
	m_vec3Origin = _vec3Position;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(s_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	m_fMaxBlastRadius = m_fMaxBlastRadius + (0.1f * static_cast<float32>(GetOwner()->GetPIC(PIC_EXPLODE_RADIUS)) * m_fMaxBlastRadius );

	CEntity::Initialise();

	CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundID, m_vec3Position);

	return (true);
}

/*
* Process
* @author Rigardt de vries
* @param _fDeltaTick        the game timer
* @return void
*/
void
CEMPBomb::Process(float32 _fDeltaTick)
{
	if (m_bAlive)
	{
		if(m_fCurrentDistance < m_fMaxDistance)
		{
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

			/*D3DXVECTOR3 vec3Distance;
			D3DXVec3Subtract(&vec3Distance, &m_vec3Origin, &m_vec3Position);*/

			m_fCurrentDistance += _fDeltaTick * m_fMovementSpeed;/*D3DXVec3Length(&vec3Distance)*/
		}
		else
		{
			if(!m_bDetonating)
			{
				m_bDetonating = true;
				CSoundManager::GetInstance().PlaySoundFromPoint(s_uiExpldSoundID, m_vec3Position);
			}
			m_fExplodeTimer += _fDeltaTick;
			Detonate();
			
			m_matWorld._41 = m_vec3Position.x;
			m_matWorld._42 = m_vec3Position.y;
			m_matWorld._43 = m_vec3Position.z;
			if(m_fExplodeTimer >= 1.0f)
			{
				SetAlive(false);
			}
		}
		if (m_fCurrentDistance < m_fMaxDistance)
		{
			CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
		}
		else
		{
			CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);
		}

		CreateAABB();
	}
}

/*
* Draw
* @author Rigardt de Vries
* @return void
*/
void
CEMPBomb::Draw()
{
	if(GetAlive())
	{
		CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
		pRenderer->SetWorldMatrix(m_matWorld);
		if (m_fCurrentDistance < m_fMaxDistance)
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
			CModelManager::GetInstance().Draw(s_uiModelID);
		}
		else
		{
            pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			CTextureManager::GetInstance().SetTexture(0, s_uiExpldTextureID);
			CModelManager::GetInstance().Draw(s_uiExpldModelID);

			pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

/*
* GetDamage
* @author Rigardt de Vries
* @return float32
*/
float32
CEMPBomb::GetDamage()
{
	return (m_fDamage);
}

/*
* SetDamage
* @author Rigardt de Vries
* @param _fDamage       the new damage
* @return void
*/
void
CEMPBomb::SetDamage(float32 _fDamage)
{
	m_fDamage = _fDamage;
}

/*
* GetMoveSpeed
* @author Rigardt de Vries
* @return float32
*/
float32 
CEMPBomb::GetMoveSpeed()
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
CEMPBomb::SetMoveSpeed(float32 _fMoveSpeed)
{
	m_fMovementSpeed = _fMoveSpeed;
}

/*
* GetWorldMatrix
* @author Rigardt de Vries
* @return D3DXMATRIX&
*/
D3DXMATRIX&
CEMPBomb::GetWorldMatrix()
{
	return (m_matWorld);
}

/*
* SetBlastRadius
* @author Rigardt de Vries
* @param _fRadius		the new radius
* @return void
*/
void
CEMPBomb::SetBlastRadius(float32 _fRadius)
{
	m_fBlastRadius = _fRadius;
}

/*
* GetBlastRadius
* @author Rigardt de Vries
* @return float32
*/
float32
CEMPBomb::GetBlastRadius()
{
	return (m_fBlastRadius);
}

/*
* GetMaxDistance
* @author Rigardt de Vries
* @return float32
*/
float32
CEMPBomb::GetMaxDistance()
{
	return (m_fMaxDistance);
}

/*
* SetMaxDistance
* @author Rigardt de Vries
* @param _fdistance			the new current distance
* @return void
*/
void 
CEMPBomb::SetCurrentDistance(float32 _fDistance)
{
	m_fCurrentDistance = _fDistance;
}

/*
* SetOwner
* @author Rigardt de Vries
* @param _pTankOwner		the owning tank of this emp
* @return void
*/
void
CEMPBomb::SetOwner(CTank* _pTankOwner)
{
	m_pTankOwner = _pTankOwner;
}

/*
* GetOwner
* @author Rigardt de Vries
* @return CTank*
*/
CTank*
CEMPBomb::GetOwner()
{
	return (m_pTankOwner);
}

/*
* Detonate
* @author Rigardt de Vries
* @return  void
*/
void
CEMPBomb::Detonate()
{
	SetBlastRadius(m_fMaxBlastRadius * m_fExplodeTimer);
	D3DXMatrixScaling(&m_matWorld, m_fBlastRadius * 2.0f, m_fBlastRadius * 2.0f, m_fBlastRadius * 2.0f);
}

/*
* StartTransition
* @author Rigardt de Vries
* @param _eTargetFace		the target face to transition over to.
* @return void
*/
void
CEMPBomb::StartTransition(EFacePosition _eTargetFace)
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
* SetAssetIDs
* @author Rigardt de Vries
* @param _uiModelID			the model id for the emps.
* @param _uiTextureID		the texture id for the emps.
* @return void
*/
void 
CEMPBomb::SetAssetIDs(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiSoundID)
{
	s_uiModelID = _uiModelID;
	s_uiTextureID = _uiTextureID;
	s_uiSoundID = _uiSoundID;
	s_uiEmptySoundID = BAD_ID;
}

/*
* SetExpldAssetIDs
* @author Rigardt de Vries
* @param _uiModelID			the id of the explosion's model
* @param _uiTextureID		the id of the explosion's texture
*
*/
void 
CEMPBomb::SetExpldAssestIDs(uint32 _uiModelID, uint32 _uiTextureID, uint32 _uiSoundID)
{
	s_uiExpldModelID = _uiModelID;
	s_uiExpldTextureID = _uiTextureID;
	s_uiExpldSoundID = _uiSoundID;
}

/*
* GetCurrentDistance
* @author Rigardt de Vries
* @return float32
*/
float32
CEMPBomb::GetCurrentDistance()
{
	return (m_fCurrentDistance);
}

/*
* GetTank
* @author Rigardt de Vries
* @param _iTankID           the ID of a tank
* @return CTank*
*/
CTank*
CEMPBomb::GetTank(int32 _iTankID)
{
    return (m_aTanksHit[_iTankID]);
}

/*
* AddTankHit
* @author Rigardt de Vries
* @param _pTank			the tank to be added
* @return boo.
*/
bool 
CEMPBomb::AddTankHit(CTank* _pTank)
{
	for (int32 i = 0; i < 8; ++i)
	{
		if (m_aTanksHit[i] == 0)
		{
			m_aTanksHit[i] = _pTank;
			return (true);
		}
	}
	return (false);
}