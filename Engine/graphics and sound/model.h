// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   model.h
//  Description :   Declaration for Cmodel
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MODEL_H__
#define __IGFEB10_MODULE_MODEL_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

// Local Includes

// Types

// Prototypes


class CModel
{
	// Member Functions
public:
	CModel();
	~CModel();

	bool Initialise(const char* _kpcFileName);

	void Draw();

    void OnDeviceLost();
    void OnDeviceReset();

	ID3DXMesh* GetModel();

protected:

private:

	// Member Variables
public:

protected:
	ID3DXMesh* m_pMesh;

	//D3DMATERIAL9 m_Material;

private:

}; 

#endif // __IGFEB10_MODULE_MODEL_H__

