// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   renderentity.cpp
//  Description :   renderentity.cppfor implementation of renderentity.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes
#include "renderentity.h"

// Static Variables

// Static Function Prototypes

// Implementation

CRenderEntity::CRenderEntity()
{
    D3DXMatrixIdentity(&m_matWorld);
}

CRenderEntity::~CRenderEntity()
{

}

const TBoundingBox&
CRenderEntity::GetBoundingBox() const
{
	return (m_tAABB);
}

const D3DXMATRIX&
CRenderEntity::GetWorldMatrix() const
{
    return (m_matWorld);
}

void
CRenderEntity::SetWorldMatrix(D3DXMATRIX& _rMatrix)
{
	m_matWorld = _rMatrix;
}

void
CRenderEntity::CreateAABB()
{
	D3DXVECTOR3 OBBVerts[8] = 
	{
		D3DXVECTOR3(m_tOBB.m_vec3Min),
		D3DXVECTOR3(m_tOBB.m_vec3Max.x, m_tOBB.m_vec3Min.y, m_tOBB.m_vec3Min.z),
		D3DXVECTOR3(m_tOBB.m_vec3Min.x, m_tOBB.m_vec3Max.y, m_tOBB.m_vec3Min.z),
		D3DXVECTOR3(m_tOBB.m_vec3Max.x, m_tOBB.m_vec3Max.y, m_tOBB.m_vec3Min.z),
		D3DXVECTOR3(m_tOBB.m_vec3Min.x, m_tOBB.m_vec3Min.y, m_tOBB.m_vec3Max.z),
		D3DXVECTOR3(m_tOBB.m_vec3Max.x, m_tOBB.m_vec3Min.y, m_tOBB.m_vec3Max.z),
		D3DXVECTOR3(m_tOBB.m_vec3Min.x, m_tOBB.m_vec3Max.y, m_tOBB.m_vec3Max.z),
		D3DXVECTOR3(m_tOBB.m_vec3Max)
	};

	for (uint32 i = 0; i < 8; ++i)
	{
		D3DXVec3TransformCoord(&OBBVerts[i], &OBBVerts[i], &m_matWorld);
	}

	D3DXComputeBoundingBox(OBBVerts, 8, sizeof(D3DXVECTOR3), &m_tAABB.m_vec3Min, &m_tAABB.m_vec3Max);
}