// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   light.h
//  Description :   Declaration for Clight
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_LIGHT_H__
#define __IGFEB10_MODULE_LIGHT_H__

// Library Includes

// Local Includes
#include "lightmanager.h"

// Types

// Prototypes


class CLight
{
	// Member Functions
public:
	CLight();
	~CLight();

    bool CreateLight(const D3DLIGHT9& _krLight);
    const D3DLIGHT9& GetLight();

	void OnDeviceLost();
	void OnDeviceReset();

    void SetActive(bool _bActive);
    bool IsActive() const;

protected:

private:

	// Member Variables
public:

protected:
    D3DLIGHT9 m_tLight;
    bool m_bActive;

private:

}; 

#endif // __IGFEB10_MODULE_LIGHT_H__

