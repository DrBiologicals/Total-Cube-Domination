// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   lightmanager.h
//  Description :   Declaration for Clightmanager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_LIGHTMANAGER_H__
#define __IGFEB10_MODULE_LIGHTMANAGER_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes

// Types

// Prototypes
class CLight;

class CLightManager 
{
	// Member Functions
public:

	static CLightManager& GetInstance();
	static void DestroyInstance();

	uint32 CreateLight(const D3DLIGHT9& _krLight);
	CLight* GetLight(uint32 _uiID);

    void SetLightActive(uint32 _uiID, bool _bActive);

	void OnDeviceLost();
	void OnDeviceReset();
	void Clear();

protected:

private:
	CLightManager();
	CLightManager(const CLightManager& _kr);
	~CLightManager();

	CLightManager& operator =(const CLightManager& _kr);

	// Member Variables
public:

protected:
	CLight* m_apLights[8];

    static CLightManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_LIGHTMANAGER_H__

