// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   light.cpp
//  Description :   light.cppfor implementation of light.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes

// This Includes
#include "light.h"

// Static Variables

// Static Function Prototypes


// Implementation
CLight::CLight()
: m_bActive(false)
{
    ZeroMemory(&m_tLight, sizeof(m_tLight) );
}
CLight::~CLight()
{

}

/*
* CreateLight
* @author Rigardt de Vries
* @param _krLight           the created light
* @return bool
*/
bool
CLight::CreateLight(const D3DLIGHT9& _krLight)
{
    m_tLight = _krLight;

    return (true);
}

/*
* GetLight
* @author Rigardt de Vries
* @return const D3DLIGHT9&
*/
const D3DLIGHT9&
CLight::GetLight()
{
    return (m_tLight);
}

/*
* SetActive
* @author Rigardt de Vries
* @param _bActive       the new bool for if active
* @return void
*/
void 
CLight::SetActive(bool _bActive)
{
    m_bActive = _bActive;
}

/*
* IsActive
* @author Rigardt de Vries
* @return bool
*/
bool
CLight::IsActive() const
{
    return (m_bActive);
}