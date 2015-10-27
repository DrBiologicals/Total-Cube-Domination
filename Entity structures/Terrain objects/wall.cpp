// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   wall.cpp
//  Description :   wall.cppfor implementation of wall.h
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
#include "wall.h"

// Static Variables

// Static Function Prototypes


// Implementation
CWall::CWall()
{
}

CWall::~CWall()
{
}

/**
*
* This function initialises the wall object with its side and tile coordinates
*
* @author Daniel Jay
* @param _eSide The side of the cube that the wall is on
* @param _iX The wall's x tile coordinate
* @param _iY The wall's y tile coordinate
* @param _uiModelID The ID of the wall's model
* @return True if the initalisation succeeded
*
*/
bool
CWall::Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID)
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

	m_bTraversable = false;

	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

	//CEntity::Initialise();

	CreateAABB();

    m_vec3SideNormals[WALL_SIDE_FRONT] = g_atUpRightDirectionVecs[m_eFace].vec3Direction;
    m_vec3SideNormals[WALL_SIDE_BACK] = -g_atUpRightDirectionVecs[m_eFace].vec3Direction;
    m_vec3SideNormals[WALL_SIDE_LEFT] = -g_atUpRightDirectionVecs[m_eFace].vec3Right;
    m_vec3SideNormals[WALL_SIDE_RIGHT] = g_atUpRightDirectionVecs[m_eFace].vec3Direction;

	return(true);
}


void
CWall::Process(float32 _fDeltaTick)
{
	//Add to the viewport
	//CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
	int i = 0;
}

void
CWall::Draw()
{
	// Grab the renderer.
	/*CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);
    CTextureManager::GetInstance().SetTexture(0, m_iTextureID);
	CModelManager::GetInstance().Draw(m_iModelID);*/
}
const D3DXVECTOR3&
CWall::GetPosition()
{
	return(m_vec3Position);
}

/*
* Returns a normal of a side of the wall
* @author Rigardt de Vries
* @param _eSide                 the side of the wall that is requested.
* @return The normal of the side.
*/
const D3DXVECTOR3&
CWall::GetWallNormal(EWallSide _eSide) const
{
    return (m_vec3SideNormals[_eSide]);
}