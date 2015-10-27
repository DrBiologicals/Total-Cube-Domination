// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   model.cpp
//  Description :   model.cppfor implementation of model.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../totalcubedomination.h"
#include "renderer.h"

// This Includes
#include "model.h"

// Static Variables

// Static Function Prototypes


// Implementation
CModel::CModel()
: m_pMesh(0)
{

}
CModel::~CModel()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = 0;
	}
}

/*
* Initialise
* @author Rigadt de Vries
* @param _kpcFileName		the name of the model file
* @return bool
*/
bool
CModel::Initialise(const char *_kpcFileName)
{
	ID3DXBuffer* pAdjBuffer = 0;

	HRESULT hr = D3DXLoadMeshFromX(	_kpcFileName, D3DXMESH_MANAGED, 
									CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice(), 
									&pAdjBuffer, 0, 0, 0, &m_pMesh);

	if (FAILED(hr) )
	{
		return (false);
	}

	/*if (pMaterialBuffer != 0 && dwNumMaterials != 0 )
	{
		D3DXMATERIAL* pMat = (D3DXMATERIAL*) pMaterialBuffer->GetBufferPointer();
		for (int32 i = 0; i < static_cast<int32>(dwNumMaterials); ++i)
		{
			m_Material = pMat[i].MatD3D;
		}
	}*/

	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL) )
	{
		ID3DXMesh* pTempMesh = 0;
		m_pMesh->CloneMeshFVF(	D3DXMESH_MANAGED, m_pMesh->GetFVF() | D3DFVF_NORMAL, 
								CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice(), 
								&pTempMesh);

		D3DXComputeNormals(pTempMesh, 0);

		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	return (true);
}

/*
* Draw
* @author Rigradt de Vries
* @return void
*/
void
CModel::Draw()
{
	if (m_pMesh)
	{
		m_pMesh->DrawSubset(0);
	}
}

void 
CModel::OnDeviceLost()
{
}

void 
CModel::OnDeviceReset()
{
}

/*
* GetModel
* @author Rigardt de Vries
* @ID3DXMesh*
*/
ID3DXMesh* 
CModel::GetModel()
{
	return (m_pMesh);
}