// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   tower.cpp
//  Description :   tower.cppfor implementation of tower.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes
#include <d3dx9.h>

// Local Includes
#include "toweraistate.h"
#include "toweridle.h"
#include "towerdisabled.h"
#include "towerattack.h"
#include "../../../engine/totalcubedomination.h"
#include "../../../engine/graphics and sound/modelmanager.h"
#include "../../../engine/graphics and sound/renderer.h"
#include "../../../engine/graphics and sound/model.h"
#include "../../../engine/graphics and sound/texturemanager.h"
#include "../../Player Objects/bullet.h"
#include "../../Player Objects/playermanager.h"
#include "../../Player Objects/player.h"
#include "../../Player objects/tank.h"
#include "../../../igutils.h"

// This Includes
#include "tower.h"

// Static Variables

// Static Function Prototypes

// Implementation
CTower::CTower()
: m_pTowerAI(0)
, m_fMaxShieldStrength(80.0f)
, m_fShieldStrength(0.0f)
, m_uiTurretModelID(BAD_ID)
, m_uiDisabledTextureID(BAD_ID)
, m_pCurrentState(0)
, m_eCurrentState(TOWERAI_STATE_NONE)
, m_eNextState(TOWERAI_STATE_NONE)
, m_fCooldownLength(0.6f)
, m_fPlasmaCoolDown(0.0f)
, m_fTurnSpeed(6.28f)
{
	D3DXMatrixIdentity(&m_matTurretWorld);
}

CTower::~CTower()
{
	for (std::list<CBullet*>::iterator iter = m_listBullets.begin(); 
	iter != m_listBullets.end(); ++iter)
	{
		delete *iter;
    }

	m_listBullets.clear();


	delete m_pCurrentState;
	m_pCurrentState = 0;

}

bool
CTower::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, ETeam _eTeam, uint32 _uiTextureID, uint32 _uiDisabledTextureID,
				   uint32 _uiModelID, uint32 _uiTurretModelID)
{
	// Set the position and side member variables in CTile.
    m_iX = _iX;
    m_iY = _iY;
	m_eFace = _eSide;
	m_iX = _iX;
	m_iY = _iY;

	m_eTeam = _eTeam;

	m_vec3Position = g_atUpRightDirectionVecs[_eSide].vec3Up * 22.5f;

	m_vec3Position += g_atUpRightDirectionVecs[_eSide].vec3Right * ((_iX * 3.0f) - 21.0f);

	m_vec3Position -= g_atUpRightDirectionVecs[_eSide].vec3Direction * ((_iY * 3.0f) - 21.0f);

	m_bTraversable = false;

	// Set the world matrix using the vectors.
	m_matWorld._11 = g_atUpRightDirectionVecs[_eSide].vec3Right.x;
	m_matWorld._21 = g_atUpRightDirectionVecs[_eSide].vec3Up.x;
	m_matWorld._31 = g_atUpRightDirectionVecs[_eSide].vec3Direction.x;

	m_matWorld._12 = g_atUpRightDirectionVecs[_eSide].vec3Right.y;
	m_matWorld._22 = g_atUpRightDirectionVecs[_eSide].vec3Up.y;
	m_matWorld._32 = g_atUpRightDirectionVecs[_eSide].vec3Direction.y;

	m_matWorld._13 = g_atUpRightDirectionVecs[_eSide].vec3Right.z; 
	m_matWorld._23 = g_atUpRightDirectionVecs[_eSide].vec3Up.z; 
	m_matWorld._33 = g_atUpRightDirectionVecs[_eSide].vec3Direction.z;

	m_matWorld._41 = m_vec3Position.x;
	m_matWorld._42 = m_vec3Position.y;
	m_matWorld._43 = m_vec3Position.z;

	m_vec3ShootRight = g_atUpRightDirectionVecs[_eSide].vec3Right;
	m_vec3ShootDir = g_atUpRightDirectionVecs[_eSide].vec3Direction;
	m_vec3Up = g_atUpRightDirectionVecs[_eSide].vec3Up;

	// Set the turrets world matrix
	RotateTurret(3.14f, 6.283185f/ m_fTurnSpeed);
	/*m_matTurretWorld._11 = m_vec3ShootRight.x; m_matTurretWorld._21 = m_vec3Up.x; m_matTurretWorld._31 = m_vec3ShootDir.x; m_matTurretWorld._41 = m_vec3Position.x;
	m_matTurretWorld._12 = m_vec3ShootRight.y; m_matTurretWorld._22 = m_vec3Up.y; m_matTurretWorld._32 = m_vec3ShootDir.y; m_matTurretWorld._42 = m_vec3Position.y;
	m_matTurretWorld._13 = m_vec3ShootRight.z; m_matTurretWorld._23 = m_vec3Up.z; m_matTurretWorld._33 = m_vec3ShootDir.z; m_matTurretWorld._43 = m_vec3Position.z;
	*/
	m_iModelID = _uiModelID;
	m_iTextureID = _uiTextureID;
	m_uiDisabledTextureID = _uiDisabledTextureID;
	m_uiTurretModelID = _uiTurretModelID;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_iModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	SetCurrentShield(m_fMaxShieldStrength);

	CEntity::Initialise();

	m_eCurrentState = TOWERAI_STATE_IDLE;
	m_eNextState = TOWERAI_STATE_IDLE;
	m_pCurrentState = new CTowerIdle();
	m_pCurrentState->Initialise(this);

	// Create bounding box.
	CreateAABB();

	return (true);
}

void
CTower::Process(float32 _fDeltaTick)
{
	//if state change is desired, change it before processing the state
	if(m_eNextState!=m_eCurrentState)
	{
		delete m_pCurrentState;
		m_pCurrentState = 0;
		switch(m_eNextState)
		{
		case TOWERAI_STATE_IDLE:
			m_pCurrentState = new CTowerIdle();
			m_pCurrentState->Initialise(this);
			break;
		case TOWERAI_STATE_DISABLED:
			m_pCurrentState = new CTowerDisabled();
			m_pCurrentState->Initialise(this);
			break;
		case TOWERAI_STATE_ATTACK:
			m_pCurrentState = new CTowerAttack();
			m_pCurrentState->Initialise(this);
			break;
		default:
			//error goes here
			break;
		}
		m_eCurrentState = m_eNextState;
	}

	//decrease/remove the cooldown time left
	m_fPlasmaCoolDown -= _fDeltaTick;
	if(0>m_fPlasmaCoolDown)
	{
		m_fPlasmaCoolDown = 0;
	}

	//process its current state
	m_pCurrentState->Process(_fDeltaTick);

	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);

	for (std::list<CBullet*>::iterator iter = m_listBullets.begin(); 
	iter != m_listBullets.end();)
	{
		if (!(*iter)->GetAlive())
		{
			delete *iter;
			iter = m_listBullets.erase(iter);
		}
		else
		{
			++iter;
		}
	}

}

void
CTower::Draw()
{
	// Set the world matrix on the renderer.
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);

	// Set the texture for the tower.
	if(TOWERAI_STATE_DISABLED!=m_eCurrentState)
	{
		CTextureManager::GetInstance().SetTexture(0, m_iTextureID);
	}
	else
	{
		CTextureManager::GetInstance().SetTexture(0, m_uiDisabledTextureID);
	}

	// Draw the base model.
	CModelManager::GetInstance().Draw(m_iModelID);

	// set turret world matrix
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matTurretWorld);

	// Draw the turret
	CModelManager::GetInstance().Draw(m_uiTurretModelID);
}

/*
* rotates the turret towards the inputed angle
*
* author				Cameron MacIntosh
* param _fRadian		the desired angle to rotate to
* param _fDeltaTick		the amount of time available to turn
*/
void
CTower::RotateTurret(float32 _fRadian, float32 _fDeltaTick)
{
	//if the turret angle is not equal to the desired angle
	if(_fRadian!=m_turretAngle.GetAngle())
	{
		//turn the turret towards the desired angle, given possible turn amount
		CAngle targetAngle;
		targetAngle.SetAngle(_fRadian);
		m_turretAngle.TurnTowardsAngle(targetAngle, m_fTurnSpeed * _fDeltaTick);

		D3DXMATRIX mat;
		D3DXMatrixRotationAxis(&mat, &m_vec3Up, m_turretAngle.GetAngle());
		D3DXVec3TransformCoord(&m_vec3ShootDir, &g_atUpRightDirectionVecs[m_eFace].vec3Direction, &mat);
		D3DXVec3TransformCoord(&m_vec3ShootRight, &g_atUpRightDirectionVecs[m_eFace].vec3Right, &mat);

		//set the world matrix of the turret model
		// Set the up, right and direction vectors into the world matirx.
		m_matTurretWorld._11 = m_vec3ShootRight.x; m_matTurretWorld._21 = m_vec3Up.x; m_matTurretWorld._31 = m_vec3ShootDir.x;
		m_matTurretWorld._12 = m_vec3ShootRight.y; m_matTurretWorld._22 = m_vec3Up.y; m_matTurretWorld._32 = m_vec3ShootDir.y;
		m_matTurretWorld._13 = m_vec3ShootRight.z; m_matTurretWorld._23 = m_vec3Up.z; m_matTurretWorld._33 = m_vec3ShootDir.z;
		m_matTurretWorld._41 = m_vec3Position.x;
		m_matTurretWorld._42 = m_vec3Position.y;
		m_matTurretWorld._43 = m_vec3Position.z;
	}
}

/*
* the cannon fires a plasma bullet if its ready
* 
* @author				Cameron MacIntosh
*/
void CTower::Shoot()
{
	if(m_fPlasmaCoolDown == 0)
	{
		m_fPlasmaCoolDown = m_fCooldownLength;

		CBullet* pBullet = new CBullet;
        pBullet->Initialise(m_vec3Position + m_vec3Up * 1.0f + m_vec3ShootDir * 0.7f, this, m_vec3ShootDir,
							m_vec3ShootRight); 
        pBullet->SetFace(m_eFace);
        pBullet->SetMoveSpeed(24.0f);
        pBullet->SetDamage(12.0f);
        m_listBullets.push_back(pBullet);
	}
}

/*
* Requests the AI change its state
* 
* @author				Cameron MacIntosh
* @param _nextState		The state that the AI will be changed to
* @return				success
*/
bool CTower::SetAIState(ETowerAIState _nextState)
{
	m_eNextState = _nextState;
	return(true);
}

bool
CTower::SetTurretModel(int32 _iModelID)
{
	m_uiTurretModelID = _iModelID;
	return(true);
}

/*
* Damages the shield, and forces an AIState transition to disabled
*   if the shield is no longer positive
* 
* @author				Cameron MacIntosh
* @param _fDamage		The amount to damage the shield by
* @return float32		The shield's modified strength
*/
float32
CTower::TakeDamage(float32 _fDamage)
{
	m_fShieldStrength -= _fDamage;
	if(m_fShieldStrength<=0)
	{
		m_fShieldStrength = 0;
		SetAIState(TOWERAI_STATE_DISABLED);
	}
	return (m_fShieldStrength);
}

/*
* remove the shield, and change the state to disabled
* 
* @author			Cameron MacIntosh
*/
void
CTower::TakeEMP()
{
	m_fShieldStrength = 0.0f;
	SetAIState(TOWERAI_STATE_DISABLED);
}

/**
* 
* Sets the current shield amount to the float32 value passed in.
* 
* @author Rebeccah Cox
* @param float32 _fShield
* @return void
*/
void
CTower::SetCurrentShield(float32 _fShield)
{
	m_fShieldStrength = _fShield;
}

/**
* 
* Returns the current shield strength.
* 
* @author Rebeccah Cox
* @return float32 m_fCurrentShieldStrength
*/
const float32
CTower::GetCurrentShield()
{
	return (m_fShieldStrength);
}

/**
* 
* Returns the maximum shield strength.
* 
* @author Rebeccah Cox
* @return float32 m_fMaxShieldStrength
*/
const float32
CTower::GetMaxShield()
{
	return (m_fMaxShieldStrength);
}

/**
* 
* Returns the current enum AI state.
* 
* @author Rebeccah Cox
* @return ETowerAIState m_eTowerState
*/
ETowerAIState
CTower::GetCurrentAIStateEnum()
{
	return (m_eCurrentState);
}

/**
* 
* Returns a pointer to the current AI state.
* 
* @author Rebeccah Cox
* @return CTowerAIState* m_pTowerAI
*/
CTowerAIState*
CTower::GetCurrentAIState()
{
	return (m_pCurrentState);
}

ETeam
CTower::GetTeam()
{
	return(m_eTeam);
}

/*
* GetBulletList
* @author Rigardt de Vries
* @return std::list<CBullet*>& 
*/
std::list<CBullet*>& 
CTower::GetBulletList()
{
	return (m_listBullets);
}
const D3DXVECTOR3&
CTower::GetPosition() const
{
	return (m_vec3Position);
}