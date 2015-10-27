// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagplate.cpp
//  Description :   flagplate.cppfor implementation of flagplate.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/totalcubedomination.h"

// This Includes
#include "flagplate.h"

// Static Variables

// Static Function Prototypes


// Implementation
CFlagPlate::CFlagPlate()
: m_bHaveFlag(true)
{

}

CFlagPlate::~CFlagPlate()
{

}

/**
* 
* PRECONDITION: parameter EFacePosition _eSide must be either FACE_TOP, or FACE_BOTTOM. 
* 
* @author Rebeccah Cox 
* @param EFacePosition _eSide - the side the flag is on, either top or bottom.
* @param int32 _iX - the position along the X axis.
* @param int32 _iY - the position along the Z axis (looks like the y axis when 
* 						looking at the flag plate). 
* @param ETeam _eTeam - team the flagplate belongs to.
* @param uint32 _uiTextureID
* @param uint32 _uiModelID
* @return bool - returns true if the initialisation was successful.
*/
bool
CFlagPlate::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, ETeam _eTeam, uint32 _uiModelID, uint32 _uiTextureID)
{
	// Set the position and side member variables in CTile.
	m_eFace = _eSide;
	m_iX = _iX;
	m_iY = _iY;

	m_vec3Position = g_atUpRightDirectionVecs[_eSide].vec3Up * 22.5f;

	m_vec3Position += g_atUpRightDirectionVecs[_eSide].vec3Right * ((_iX * 3.0f) - 21.0f);

	m_vec3Position -= g_atUpRightDirectionVecs[_eSide].vec3Direction * ((_iY * 3.0f) - 21.0f);

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

	m_bTraversable = true;

	m_iModelID = _uiModelID;
	m_iTextureID = _uiTextureID;

	/*// Set the model ID
	if(BAD_ID == _uiModelID)
	{
		m_iModelID = CModelManager::GetInstance().CreateModel("../../models/tile_flagplate.x");
	}

	// Set the texture ID
	if(BAD_ID == _uiTextureID)
	{
		if(TEAM_GREEN == _eTeam)
		{
			m_iTextureID = CTextureManager::GetInstance().CreateTexture("../../textures/tile_flagTile_green.png");
		}
		else
		{
			m_iTextureID = CTextureManager::GetInstance().CreateTexture("../../textures/tile_flagTile_purple.png");
		}
	}*/

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_iModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	CEntity::Initialise();

	return (true);
}

/**
* 
* Adds the flag plate to the viewports.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void
CFlagPlate::Process(float32 _fDeltaTick)
{
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);

	// Create bounding box.
	CreateAABB();
}

/**
* 
* Sets the world matrix and texture, then draws the model.
* 
* @author Rebeccah Cox
* @return void
*/
void
CFlagPlate::Draw()
{
	// Set the world matrix on the renderer.
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);

	// Set the texture for the flag plate.
	CTextureManager::GetInstance().SetTexture(0, m_iTextureID);

	// Draw the flag plate model.
	CModelManager::GetInstance().Draw(m_iModelID);
}

/**
*
* Sets the member variable m_bHaveFlag to true.
*
* @author Rebeccah Cox
* @return void
*/
void
CFlagPlate::AddFlag()
{
	m_bHaveFlag = true;
}

/**
*
* Returns the value of m_bHaveFlag.
*
* @author Rebeccah Cox
* @return bool m_bHaveFlag - whether the flag plate has a flag currently.
*/
bool
CFlagPlate::HasFlag()
{
	return (m_bHaveFlag);
}

/**
*
* Sets the member variable m_bHaveFlag to false.
*
* @author Rebeccah Cox
* @return void
*/
void
CFlagPlate::RemoveFlag()
{
	m_bHaveFlag = false;
}

/**
*
* Returns the position of the flag plate.
*
* @author Rebeccah Cox
* @return D3DVECTOR* m_vec3Position - position vector inherited from CTile.
*/
const D3DVECTOR*
CFlagPlate::GetPosition()
{
	return (&m_vec3Position);
}
