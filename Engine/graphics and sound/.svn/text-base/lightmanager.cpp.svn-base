// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   lightmanager.cpp
//  Description :   lightmanager.cppfor implementation of lightmanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../totalcubedomination.h"
#include "light.h"
#include "renderer.h"

// This Includes
#include "lightmanager.h"

// Static Variables

// Static Function Prototypes
CLightManager* CLightManager::s_pInstance = 0;

// Implementation
CLightManager::CLightManager()
{
    memset(&m_apLights, 0, sizeof(m_apLights) );
}

CLightManager::~CLightManager()
{
    for (int32 i = 0; i < 8; ++i)
    {
        if(m_apLights[i])
        {
            delete m_apLights[i];
            m_apLights[i] = 0;
        }
    }
}

/*
* GetInstance
* @author rigardt de vries
* @return CLightManager&
*/
CLightManager& 
CLightManager::GetInstance()
{
    if(!s_pInstance)
	{
		s_pInstance = new CLightManager;
	}

	return(*s_pInstance);
}

/*
* DestroyInstance
* @author Rigardt de Vries
* @return void
*/
void 
CLightManager::DestroyInstance()
{
    delete s_pInstance;
    s_pInstance = 0;
}
void
CLightManager::Clear()
{
    for (int32 i = 0; i < 8; ++i)
    {
        if (m_apLights[i])
        {
			SetLightActive(i, false);
            delete m_apLights[i];
        }
		else
		{
			break;
		}
    }

    memset(m_apLights, 0, sizeof(m_apLights));
}
/*
* CreateLight
* @author Rigardt de Vries
* @param _krLight           the created light
* @return uint32
*/
uint32
CLightManager::CreateLight(const D3DLIGHT9& _krLight)
{
    for (uint32 ui = 0; ui < 8; ++ui)
    {
        if (m_apLights[ui] == 0)
        {
            m_apLights[ui] = new CLight;

            m_apLights[ui]->CreateLight(_krLight);
            CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->SetLight(ui, &_krLight);

            return (ui);
        }
    }
	return (BAD_ID);
}

void 
CLightManager::OnDeviceLost()
{ 
}

void 
CLightManager::OnDeviceReset()
{
	for (int32 i = 0; i < 32; ++i)
    {
        if (m_apLights[i])
        {
            CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->SetLight(i, &m_apLights[i]->GetLight());

            CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->LightEnable(i, m_apLights[i]->IsActive());
        }
		else
		{
			break;
		}
    }
}

/*
* GetLight
* @author Rigardt de Vries
* @param _uiID          the ID of the requested light.
* @return CLight*
*/
CLight* 
CLightManager::GetLight(uint32 _uiID)
{
	return(m_apLights[_uiID]);
}

/*
* SetLightActive
* @author Rigardt de Vries
* @param _uiID          the ID of the light
* @return void
*/
void
CLightManager::SetLightActive(uint32 _uiID, bool _bActive)
{
    m_apLights[_uiID]->SetActive(_bActive);
    CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->LightEnable(_uiID, _bActive);
}