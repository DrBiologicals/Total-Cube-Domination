// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   modelmanager.h
//  Description :   Declaration for Cmodelmanager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MODELMANAGER_H__
#define __IGFEB10_MODULE_MODELMANAGER_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes

// Types

// Prototypes
class CModel;

class CModelManager 
{
	// Member Functions
public:
	static CModelManager& GetInstance();
	static void DestroyInstance();

	void OnDeviceLost();
    void OnDeviceReset();

	uint32 CreateModel(const char* _kpcFileName);
	CModel* GetModel(uint32 _uiID);

	void Clear();

	void Draw(uint32 _uiID);

protected:

private:
	CModelManager();
	CModelManager(const CModelManager& _kr);
	~CModelManager();

	CModelManager& operator =(const CModelManager& _kr);

	// Member Variables
public:

protected:

	CModel* m_apModels[64];

	static CModelManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_MODELMANAGER_H__

