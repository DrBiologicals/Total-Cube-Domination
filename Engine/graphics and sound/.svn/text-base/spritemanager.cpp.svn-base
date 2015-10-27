// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   spritemanager.cpp
//  Description :   spritemanager.cppfor implementation of spritemanager.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "sprite.h"

// This Includes
#include "spritemanager.h"

// Static Variables
CSpriteManager* CSpriteManager::s_pInstance = 0;

// Static Function Prototypes

// Implementation
CSpriteManager::CSpriteManager()
{
	ZeroMemory(m_apSprites, sizeof(m_apSprites));
}

CSpriteManager::~CSpriteManager()
{
	Clear();
}

/**
*
* This function initialises the sprite manager
*
* @author Daniel Jay
* @return True if the initialisation succeeded
*
*/
bool
CSpriteManager::Initialise()
{
	return true;
}

/**
*
* This function clears all resources from the sprite manager
*
* @author Daniel Jay
*
*/
void 
CSpriteManager::Clear()
{
	for (int32 i = 0; i < MAX_SPRITES; ++i)
	{
		delete m_apSprites[i];
	}

	ZeroMemory(m_apSprites, sizeof(m_apSprites));
}

/**
*
* This function prepares all of the manager's resources to be reset when the device is regained
*
* @author Daniel Jay
*
*/
void 
CSpriteManager::OnDeviceLost()
{
	for (int32 i = 0; i < MAX_SPRITES; ++i)
	{
		// The first null pointer indicates the end of 
		// the manager's allocated resources
		if (!m_apSprites[i]) break;

		m_apSprites[i]->OnDeviceLost();
	}
}

/**
*
* This function resets all of the manager's resources with the regained device
*
* @author Daniel Jay
*
*/
void 
CSpriteManager::OnDeviceReset()
{
	for (int32 i = 0; i < MAX_SPRITES; ++i)
	{
		// The first null pointer indicates the end of 
		// the manager's allocated resources
		if (!m_apSprites[i]) break;

		m_apSprites[i]->OnDeviceReset();
	}
}

/**
*
* This function creates a new sprite resource with the specified texture and source rect
*
* @author Daniel Jay
* @param _uiTextureID The ID of the texture for the sprite to use
* @param _krSourceRect The rect from the texture for the sprite to use
* @return The ID of the new sprite resource
*
*/
uint32
CSpriteManager::CreateSprite(uint32 _uiTextureID, const RECT* _kpSourceRect)
{
	// If the array is already full, return an invalid ID
	if (m_apSprites[MAX_SPRITES - 1]) return (BAD_ID);

	for (int32 i = 0; i < MAX_SPRITES; ++i)
	{
		// Use the first empty index in the array
		if (!m_apSprites[i])
		{
			// Create the sprite and return the ID
			m_apSprites[i] = new CSprite;
			if (m_apSprites[i]->Initialise(_uiTextureID, _kpSourceRect))
			{
				return (i);
			}
			else
			{
				// Return an invalid ID if the initialisation failed
				delete m_apSprites[i];
				m_apSprites[i] = 0;

				return (BAD_ID);
			}
		}
	}

	// Return an invalid ID if an unknown problem occured
	return (BAD_ID);
}

/**
*
* This function returns a pointer to the sprite resource with the specified ID
*
* @author Daniel Jay
* @param _uiSpriteID The ID of the sprite to obtain
* @return A pointer to the specified sprite, or null if the ID is invalid
*
*/
CSprite*
CSpriteManager::GetSprite(uint32 _uiSpriteID)
{
#ifdef _DEBUG
	assert((_uiSpriteID >= 0) && (_uiSpriteID < MAX_SPRITES));
#endif // _DEBUG

	return (m_apSprites[_uiSpriteID]);
}

/**
*
* This function returns a reference to the singleton instance of the manager
*
* @author Daniel Jay
* @return A reference to the singleton instance
*
*/
CSpriteManager&
CSpriteManager::GetInstance()
{
	if (!s_pInstance)
	{
		s_pInstance = new CSpriteManager;
	}

	return (*s_pInstance);
}

/**
*
* This function destroys the singleton instance of the manager
*
* @author Daniel Jay
*
*/
void
CSpriteManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}