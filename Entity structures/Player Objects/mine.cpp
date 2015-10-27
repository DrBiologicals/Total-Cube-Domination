// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   mine.cpp
//  Description :   mine.cppfor implementation of mine.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "tank.h"
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/soundmanager.h"

// This Includes
#include "mine.h"

// Static Variables
uint32 CMine::s_uiModelID = BAD_ID;
uint32 CMine::s_uiGreenTextureID = BAD_ID;
uint32 CMine::s_uiPurpleTextureID = BAD_ID;
uint32 CMine::s_uiUnarmedTextureID = BAD_ID;
uint32 CMine::s_uiExTextureID = BAD_ID;
uint32 CMine::s_uiExModelID = BAD_ID;
float32 CMine::s_fActivateTime = 1.0f;
uint32 CMine::s_uiSoundID = BAD_ID;
uint32 CMine::s_uiExpldSoundID = BAD_ID;
uint32 CMine::s_uiEmptySoundID = BAD_ID;
// Static Function Prototypes

// Implementation

CMine::CMine()
: m_bIsActive(true)
, m_fExplodeRadius(1.0f)
, m_fLifeTimer(4.0f)
, m_fExplosionTimer(0.0f)
, m_fMaxRadius(6.0f)
, m_pTankOwner(0)
, m_bIsExploding(false)
, m_bIsArmed(false)
, m_ePosition(FACE_NONE)
{
	memset(&m_aTanksHit, 0, sizeof(m_aTanksHit));
}

CMine::~CMine()
{
	m_pTankOwner  = 0;
}

void
CMine::LoadAssets()
{
	if (s_uiModelID == BAD_ID)
	{
		s_uiModelID =  CModelManager::GetInstance().CreateModel("models/wpn_mine.x");
		s_uiExModelID = CModelManager::GetInstance().CreateModel("models/eff_mine.x");
	}

	if (s_uiGreenTextureID == BAD_ID)
	{
		s_uiGreenTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_mine_green.png");
		s_uiPurpleTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_mine_purple.png");
		s_uiUnarmedTextureID = CTextureManager::GetInstance().CreateTexture("textures/wpn_mine_unarmed.png");
		s_uiExTextureID = CTextureManager::GetInstance().CreateTexture("textures/eff_mine.png");
	}

	if (s_uiSoundID == BAD_ID)
	{
		s_uiSoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_mine_init.wav", 0.5f, false,25.0f);
		s_uiExpldSoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_mine_detonate.wav", 0.6f, false, 75.0f);
		s_uiEmptySoundID = CSoundManager::GetInstance().CreateSound("sounds/sfx/wpn_mine_empty.wav", 0.5f, false, 5.0f);
	}

}
/*
* Initialise
* @author Michael McQuarrie
* @param _pTankOwner
* @return bool
*/

bool
CMine::Initialise(CTank* _pTankOwner)
{
	CRenderEntity::Initialise();

	SetOwner(_pTankOwner);

	m_ePosition = m_pTankOwner->GetFacePosition();
	// Initialise all the variables that are passed in
	D3DXMatrixIdentity(&m_matWorld);
	m_vec3Position = GetOwner()->GetPosition() - g_atUpRightDirectionVecs[m_ePosition].vec3Up * 0.5f;
	m_matWorld = GetOwner()->GetWorldMatrix();
	
	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(s_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	m_matWorld._41 = m_vec3Position.x;
	m_matWorld._42 = m_vec3Position.y;
	m_matWorld._43 = m_vec3Position.z;

	m_tOBB.m_vec3Max.y = 3.0f;
	CreateAABB();

	m_fMaxRadius = m_fMaxRadius + (0.1f * static_cast<float32>(GetOwner()->GetPIC(PIC_EXPLODE_RADIUS)) * m_fMaxRadius );
	
	CSoundManager::GetInstance().PlaySoundFromPoint(s_uiSoundID, m_vec3Position);

	return (true);
}
/*
* Process
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CMine::Process(float32 _fDeltaTick)
{
	if(IsActive())
	{
		//Activate the bomb after the activate time
		if(!GetArmed())
		{
			m_fExplosionTimer += _fDeltaTick;
			if(m_fExplosionTimer >= s_fActivateTime)
			{		
				SetArmed(true);
			}
		}
		//Is armed but still a mine
		else if(!GetExploding())
		{
			m_fExplosionTimer += _fDeltaTick;
			if(m_fExplosionTimer >= m_fLifeTimer)
			{		
				SetExploding(true);
			}
		}
		//Is exploding
		else
		{
			m_fExplosionTimer += _fDeltaTick * 2.0f;
			Explode(m_fExplosionTimer);
			if(m_fExplosionTimer >= 1.0f)
			{
				SetActive(false);
			}
		}
		
		m_matWorld._41 = m_vec3Position.x;
		m_matWorld._42 = m_vec3Position.y;
		m_matWorld._43 = m_vec3Position.z;

		//Add to the viewport
		if (!GetExploding())
		{
			CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
		}
		else
		{
			CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);
		}
	}
}
/*
* Draw
* @author Michael McQuarrie
* 
* @return void
*/
void
CMine::Draw()
{
	if(IsActive())
	{
		// Grab the renderer.
		CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

		// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
		pRenderer->SetWorldMatrix(m_matWorld);
		if(!GetExploding())
		{
			if(!m_bIsArmed)
			{
				CTextureManager::GetInstance().SetTexture(0, s_uiUnarmedTextureID);
			}
			else if(TEAM_GREEN==m_pTankOwner->GetTeam())
			{
				CTextureManager::GetInstance().SetTexture(0, s_uiGreenTextureID);
			}
			else
			{
				CTextureManager::GetInstance().SetTexture(0, s_uiPurpleTextureID);
			}
			CModelManager::GetInstance().Draw(s_uiModelID);
		}
		else
		{
            pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
			//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			CTextureManager::GetInstance().SetTexture(0, s_uiExTextureID);
			CModelManager::GetInstance().Draw(s_uiExModelID);

			pRenderer->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
			//pRenderer->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            pRenderer->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}

/*
* Set the static IDs to BAD_ID
* @author Rigardt de Vries
* @return void
*/
void
CMine::SetAssestToBadID()
{
    s_uiModelID = BAD_ID;
    s_uiExTextureID = BAD_ID;
    s_uiGreenTextureID = BAD_ID;
	s_uiPurpleTextureID = BAD_ID;
	s_uiUnarmedTextureID = BAD_ID;
    s_uiExModelID = BAD_ID;
	s_uiSoundID = BAD_ID;
	s_uiExpldSoundID = BAD_ID;
	s_uiEmptySoundID = BAD_ID;
}

/*
* Explode
* @author Michael McQuarrie
* @return void
*/
void
CMine::Explode(float32 _fExplosionTimer)
{
	SetExplodeRadius(m_fMaxRadius * _fExplosionTimer);
	D3DXMatrixScaling(&m_matWorld, m_fExplodeRadius * 2.0f, m_fExplodeRadius * 2.0f, m_fExplodeRadius * 2.0f);
}
/*
* SetExplodeRadius
* @author Michael McQuarrie
* @param _fRadius
* @return void
*/
void
CMine::SetExplodeRadius(float32 _fRadius)
{
	m_fExplodeRadius = _fRadius;
}

/*
* GetExplodeRadius
* @author Michael McQuarrie
* 
* @return float32 m_fExplodeRadius
*/
float32
CMine::GetExplodeRadius()
{
	return (m_fExplodeRadius);
}
/*
* IsActive
* @author Michael McQuarrie
* 
* @return bool IsActive
*/
bool
CMine::IsActive()
{
	return (m_bIsActive);
}

/*
* SetModelID
* @author Michael McQuarrie
* @param _uiID The Model ID
* @return void
*/
void
CMine::SetModelID(uint32 _uiID)
{
	s_uiModelID = _uiID;
}
/*
* SetTextureID
* @author Michael McQuarrie
* @param _uiID The Texture ID
* @return void
*/
void
CMine::SetTextureIDs(uint32 _uiGreenID, uint32 _uiPurpleID)
{
	s_uiGreenTextureID = _uiGreenID;
	s_uiPurpleTextureID = _uiPurpleID;
}
/*
* SetOwner
* @author Michael McQuarrie
* @param _pTankOwner
* @return void
*/
void
CMine::SetOwner(CTank* _pTankOwner)
{
	m_pTankOwner = _pTankOwner;
}
/*
* GetOwner
* @author Michael McQuarrie
* 
* @return CTank*
*/
CTank*
CMine::GetOwner()
{
	return (m_pTankOwner);
}

/*
* Get Exploding
* @author Michael McQuarrie
* 
* @return bool
*/
bool
CMine::GetExploding()
{
	return(m_bIsExploding);
}

/*
* SetExploding
* @author Michael McQuarrie
* @param _bExploding
* @return void
*/
void
CMine::SetExploding(bool _bExploding)
{
	m_fExplosionTimer = 0.0f;
	m_bIsExploding = _bExploding;
	CSoundManager::GetInstance().PlaySoundFromPoint(s_uiExpldSoundID, m_vec3Position);
}

/*
* SetActive
* @author Michael McQuarrie
* @param _bActive
* @return void
*/
void
CMine::SetActive(bool _bActive)
{
	m_fExplosionTimer = 0.0f;
	m_bIsActive = _bActive;
}

/*
* Position of the mine
* @author Michael McQuarrie
* 
* @return D3DXVECTOR3
*/
D3DXVECTOR3
CMine::GetPosition()
{
	return(m_vec3Position);
}

/*
* AddTankHit
* @author Rigardt de Vries
* @param _pTank			the tank to be added
* @return boo.
*/
bool 
CMine::AddTankHit(CTank* _pTank)
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

/*
* GetTank
* @author Rigardt de Vries
* @param _iTankID		the id of a tank
* @return CTank*
*/
CTank* 
CMine::GetTank(int32 _iTankID)
{
	return (m_aTanksHit[_iTankID]);
}

/*
* Get Armed
* @author Michael McQuarrie
*
* @return bool
*/
bool
CMine::GetArmed()
{
	return(m_bIsArmed);
}

/*
* Set the mine to armed
* @author Michael McQuarrie
* @param _bArmed
* @return void
*/
void
CMine::SetArmed(bool _bArmed)
{
	m_fExplosionTimer = 0.0f;
	m_bIsArmed = _bArmed;
}