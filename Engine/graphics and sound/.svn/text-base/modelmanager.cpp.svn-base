// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   modelmanager.cpp
//  Description :   modelmanager.cppfor implementation of modelmanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "model.h"
#ifdef _DEBUG

//#include "../../logutil.h"

#endif //_DEBUG

// This Includes
#include "modelmanager.h"

// Static Variables

// Static Function Prototypes


// Implementation

CModelManager* CModelManager::s_pInstance = 0;
// Static Function Prototypes


// Implementation
CModelManager::CModelManager()
{
	memset(m_apModels, 0, sizeof(m_apModels));
}

CModelManager::~CModelManager()
{
	for(int32 i = 0; i < 64; ++i)
	{
		delete m_apModels[i];
		m_apModels[i] = 0;
	}
}

void 
CModelManager::OnDeviceLost()
{
	for (int32 i = 0; i < 64; ++i)
	{
		if (m_apModels[i])
		{
			m_apModels[i]->OnDeviceLost();
		}
		else
		{
			break;
		}
	}
}

void 
CModelManager::OnDeviceReset()
{
	for (int32 i = 0; i < 64; ++i)
	{
		if (m_apModels[i])
		{
			m_apModels[i]->OnDeviceReset();
		}
		else
		{
			break;
		}
	}
}

/*
* CreateModel
* @author Rigardt de Vries
* @param _kpcFilename		the name of the file
* @return uint32
*/
uint32
CModelManager::CreateModel(const char* _kpcFileName)
{
	CModel* pModel = new CModel;

	if (pModel->Initialise(_kpcFileName) )
	{
		for (int32 i = 0; i < 64; ++i)
		{
			if (m_apModels[i] == 0)
			{
				m_apModels[i] = pModel;
				return(i);
			}
		}
	}

	delete pModel;

	return (BAD_ID);
}

/*
* Draw
* @author Rigardt de Vries
* @param _uiID			the ID to the model
* @return void
*/
void 
CModelManager::Draw(uint32 _uiID)
{
    if (_uiID != BAD_ID)
    {
	    m_apModels[_uiID]->Draw();
    }
}

/*
* GetModel
* @author Rigardt de Vries
* @param _uiID		the ID of the model
* @return CModel*
*/
CModel*
CModelManager::GetModel(uint32 _uiID)
{
    if (_uiID != -1)
    {
	    return (m_apModels[_uiID]);
    }
    return (0);
}

void
CModelManager::Clear()
{
    for (int32 i = 0; i < 32; ++i)
    {
        if (m_apModels[i])
        {
            delete m_apModels[i];
        }
		else
		{
			break;
		}
    }

    memset(m_apModels, 0, sizeof(m_apModels));
}

/*
* DestroyInstance
* @author Rigardt de Vries
* @return void
*/
void
CModelManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/*
* GetInstance
* @author Rigardt de Vries
* @return CModelManager&
*/
CModelManager&
CModelManager::GetInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CModelManager;
	}

	return(*s_pInstance);
}

