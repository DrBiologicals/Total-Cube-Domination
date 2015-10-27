// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flag.cpp
//  Description :   flag.cppfor implementation of flag.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Engine/TotalCubeDomination.h"
#include "../../Engine/graphics and sound/modelmanager.h"
#include "../../Engine/graphics and sound/texturemanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../Particle/emittermanager.h"
#include "../Particle/particleemitter.h"
#include "flagplate.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/modelmanager.h"

// This Includes
#include "flag.h"

// Static Variables

// Static Function Prototypes


// Implementation
CFlag::CFlag()
: m_pFlagSpawnLocation(0)
, m_uiTextureID(0)
, m_uiModelID(0)
, m_eTeam(TEAM_GREEN)
, m_bPickedUp(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CFlag::~CFlag()
{
	//m_pFlareEmitter = 0;

	// already being deleted somewhere else, so do not delete here.
	m_pFlagSpawnLocation = 0;
}

/**
* 
* Initialises the flag at the position in CFlagPlate* _pFlagSpawnLocation and
*	sets all the member variable. 
* 
* @author Rebeccah Cox
* @param D3DVECTOR _vecPosition - the current position of the flag. 
* @param uint32 _uiModelID - ID to pass into model manager when drawing.
* @param uint32 _uiTextureID - ID to pass into texture manager when drawing.
* @param ETeam _eTeam - which team the flag is assigned to.
* @param CFlagPlate* _pFlagSpawnLocation - the spawn location for the flag.
* @return bool - returns true if the initialisation was successful. 
*/
bool
CFlag::Initialise(uint32 _uiModelID, uint32 _uiTextureID, ETeam _eTeam, CFlagPlate* _pFlagSpawnLocation)
{
	CEntity::Initialise();

	// Set member variables.
	m_eTeam = _eTeam;
	m_pFlagSpawnLocation = _pFlagSpawnLocation;

	// Create particle emitter.
    CEmitterManager::GetInstance().AddEmitter(15, *_pFlagSpawnLocation->GetPosition(), PARTICLE_FLAG, m_eTeam, 0, this);

	//Set the face position
	m_eFace = _pFlagSpawnLocation->GetFacePosition();

	// Set the world matrix using the spawn location and directional vectors.
	SetVectors(g_atUpRightDirectionVecs[m_eFace].vec3Up, g_atUpRightDirectionVecs[m_eFace].vec3Right, 
		g_atUpRightDirectionVecs[m_eFace].vec3Direction, *_pFlagSpawnLocation->GetPosition());

	// Set the model and texture IDs.
	m_uiModelID = _uiModelID;
	m_uiTextureID = _uiTextureID;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

    CreateAABB();

	return (true);
}

/**
* 
* Calls the particle emitter's process function.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void
CFlag::Process(float32 _fDeltaTick)
{
	// Process particle emitter.
	//m_pFlareEmitter->Process(_fDeltaTick);

	// Add this to the viewports.
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);

	// Create bounding box.
	CreateAABB();
}

/**
* 
* Calls the particle emitter's draw function.
* Draws the flag.
* 
* @author Rebeccah Cox
* @return void
*/
void
CFlag::Draw()
{
	// Draw the flare (particle emitter).
	//m_pFlareEmitter->Draw();

	// Set the world matrix on the renderer.
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);

	// Set the texture on the device.
	CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);

	// Draw the model.
	CModelManager::GetInstance().Draw(m_uiModelID);
}

/**
* 
* Sets the flag's current position, using the world matrix inherited from CRenderEntity. 
* 
* @author Rebeccah Cox
* @param D3DVECTOR _vecPosition - the new x,y,z position for the flag.
* @return void
*/
void
CFlag::SetPosition(D3DVECTOR _vecPosition)
{
	m_matWorld._41 = _vecPosition.x;
	m_matWorld._42 = _vecPosition.y;
	m_matWorld._43 = _vecPosition.z;
}

void
CFlag::SetFacePosition(EFacePosition _eFacePosition)
{
	m_eFace = _eFacePosition;
}

/**
* 
* Sets the flag back at the flag plate position.
* 
* @author Rebeccah Cox
* @return void
*/
void
CFlag::ResetPosition()
{
	m_eFace = m_pFlagSpawnLocation->GetFacePosition();
	SetVectors(g_atUpRightDirectionVecs[m_eFace].vec3Up, g_atUpRightDirectionVecs[m_eFace].vec3Right, 
		g_atUpRightDirectionVecs[m_eFace].vec3Direction, *m_pFlagSpawnLocation->GetPosition());
	CreateAABB();
}

/**
* 
* Returns the team that the flag belongs to (TEAM_GREEN or TEAM_PURPLE).
* 
* @author Rebeccah Cox
* @return ETeam m_eTeam - the team the flag is on.
*/
ETeam
CFlag::GetTeam()
{
	return (m_eTeam);
}

/**
* 
* Returns true if the flag is on it's base. 
* 
* @author Rebeccah Cox
* @return bool - true if current position matches spawn position.
*/
bool
CFlag::IsFlagOnFlagPlate()
{
	// Check if the flags current position matches the flag plates position.
	if(m_matWorld._41 == m_pFlagSpawnLocation->GetPosition()->x
		&& m_matWorld._42 == m_pFlagSpawnLocation->GetPosition()->y
		&& m_matWorld._43 == m_pFlagSpawnLocation->GetPosition()->z)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/**
* 
* Returns the current position of the flag.
* 
* @author Rebeccah Cox
* @return D3DXVECTOR3* - the position held in the world matrix.
*/
D3DXVECTOR3
CFlag::GetPosition()
{
	return (D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43));
}

/*
* Returns the face the flag is on
*
* @author		Cameron MacIntosh
* @return		the face the flag is on
*/
EFacePosition&
CFlag::GetFace()
{
	return (m_eFace);
}

/*
* SetFlagPickedUp
* @author Rigardt de Vries
* @param _bPickedUP         the new bool value
* @return void
*/
void
CFlag::SetFlagPickedUp(bool _bPickedUp)
{
    m_bPickedUp = _bPickedUp;
	if(_bPickedUp)
	{
		m_pFlagSpawnLocation->RemoveFlag();
	}
	else
	{
		m_pFlagSpawnLocation->AddFlag();
	}
}

/*
* GetFlagPickedUp
* @author Rigardt de Vries
* @return bool
*/
bool
CFlag::GetFlagPickedUp()
{
    return (m_bPickedUp);
}

const D3DXVECTOR3& 
CFlag::GetUp() const
{
	return (m_vec3Up);
}

const D3DXVECTOR3& 
CFlag::GetRight() const
{
	return (m_vec3Right);
}

const D3DXVECTOR3& 
CFlag::GetDirection() const
{
	return (m_vec3Direction);
}

void 
CFlag::SetVectors(const D3DXVECTOR3& _Up, const D3DXVECTOR3& _Right, const D3DXVECTOR3& _Dir, const D3DXVECTOR3& _Pos)
{
	m_vec3Up = _Up;
	m_vec3Right = _Right;
	m_vec3Direction = _Dir;
	m_vec3Position = _Pos;

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
}