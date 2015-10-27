// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   texturemanager.cpp
//  Description :   texturemanager.cppfor implementation of texturemanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "texture.h"
#include "../totalcubedomination.h"
#include "renderer.h"

// This Includes
#include "texturemanager.h"

// Static Variables
uint32 CTextureManager::s_uiCurrentTexture = BAD_ID;

// Static Function Prototypes

CTextureManager* CTextureManager::s_pInstance = 0;
// Implementation

CTextureManager::CTextureManager()
{
    ZeroMemory(m_apTextures, sizeof(m_apTextures));
}

CTextureManager::~CTextureManager()
{
    Clear();
}

/*
* Initialise
* @author Rigardt de Vries
* @return bool
*/
bool
CTextureManager::Initialise()
{
	return true;
}

/**
*
* This function clears all resources from the manager
*
* @author Daniel Jay
*
*/
void
CTextureManager::Clear()
{
    for (int32 i = 0; i < MAX_TEXTURES; ++i)
    {
		delete m_apTextures[i];
    }

	ZeroMemory(m_apTextures, sizeof(m_apTextures));

    s_uiCurrentTexture = BAD_ID;
}

/**
*
* This function prepares the manager's resources for being reset when the device is regained
*
* @author Daniel Jay
*
*/
void 
CTextureManager::OnDeviceLost()
{
	for (int32 i = 0; i < MAX_TEXTURES; ++i)
    {
        if (!m_apTextures[i]) break;

        m_apTextures[i]->OnDeviceLost();
    }
}

/**
*
* This function resets the manager's resources when the device is regained
*
* @author Daniel Jay
*
*/
void 
CTextureManager::OnDeviceReset()
{
	for (int32 i = 0; i < MAX_TEXTURES; ++i)
    {
        if (!m_apTextures[i]) break;

        m_apTextures[i]->OnDeviceReset();
    }
}

/**
*
* This function creates a texture resource from a file
*
* @author Daniel Jay
* @param _kpcFileName The file to create the texture from
* @return The ID of the created texture
*
*/
uint32
CTextureManager::CreateTexture(const char *_kpcFileName)
{
	// If the array is already full, return an invalid ID
	if (m_apTextures[MAX_TEXTURES - 1]) return (BAD_ID);

	for (int32 i = 0; i < MAX_TEXTURES; ++i)
	{
		// Use the first empty index in the array
		if (!m_apTextures[i])
		{
			// Create the texture and return the ID
			m_apTextures[i] = new CTexture;
			if (m_apTextures[i]->Initialise(_kpcFileName))
			{
				return (i);
			}
			else
			{
				// Return an invalid ID if the initialisation failed
				delete m_apTextures[i];
				m_apTextures[i] = 0;

				return (BAD_ID);
			}
		}
	}

	// Return an invalid ID if an unknown problem occured
	return (BAD_ID);
}

/**
*
* This function sets the specified texture into the specified texture stage on the device
*
* @author Daniel Jay
* @param _uiTextureStage The texture stage to set the texture to
* @param _uiID The ID of the texture to set on to the device
*
*/
void
CTextureManager::SetTexture(uint32 _uiTextureStage, uint32 _uiID)
{
#ifdef _DEBUG
	assert((_uiID >= 0) && (_uiID < MAX_TEXTURES));
#endif // _DEBUG

    if (s_uiCurrentTexture != _uiID)
    {
        CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->SetTexture(_uiTextureStage, m_apTextures[_uiID]->GetTexture());
        s_uiCurrentTexture = _uiID;
    }
}

CTexture* 
CTextureManager::GetTexture(uint32 _uiTextureID)
{
#ifdef _DEBUG
	assert((_uiTextureID >= 0) && (_uiTextureID < MAX_TEXTURES));
#endif // _DEBUG

	return (m_apTextures[_uiTextureID]);
}

/*
* GetInstance
* @author Rigardt the Vries
* @return CTextureManager&
*/
CTextureManager&
CTextureManager::GetInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CTextureManager;
	}

	return(*s_pInstance);
}

/*
* DestroyInstance
* @author Rigardt de vries
* @return void
*/
void
CTextureManager::DestroyInstance()
{
    delete s_pInstance;
    s_pInstance = 0;
}