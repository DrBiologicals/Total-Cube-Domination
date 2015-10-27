// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   billboardmanager.cpp
//  Description :   billboardmanager.cpp for implementation of billboardmanager.h
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "billboard.h"
#include "../totalcubedomination.h"
#include "renderer.h"
#include "../Viewport/camera.h"
#include "../Viewport/viewport.h"

// This Includes
#include "billboardmanager.h"

// Static Variables
CBillboardManager* CBillboardManager::s_pBillboardManager = 0;

// Static Function Prototypes

// Implementation

/**
* 
* Return the singleton instance of CBillboardManager.
* If no instance exists, create a new one.
* 
* @author Rebeccah Cox
* @return CBillboardManager&
*/
CBillboardManager&
CBillboardManager::GetInstance()
{
	if(0 == s_pBillboardManager)
	{
		s_pBillboardManager = new CBillboardManager();
	}
	
	return (*s_pBillboardManager);
}

/**
* 
* Delete the instance of CBillboardManager if there is one.
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboardManager::DestroyInstance()
{
	if(0 != s_pBillboardManager)
	{
		delete s_pBillboardManager;
		s_pBillboardManager = 0;
	}
}

/**
* 
* Creates a new billboard at the size passed in.
* 
* @author Rebeccah Cox
* @param D3DXVECTOR3 _vec3Position - the center point of the billboard.
* @param const float32 _fWidth
* @param const float32 _fHeight
* @return unsigned int32 - index number of the billboard in the array.
*/
uint32
CBillboardManager::CreateBillboard(uint32 _uiTextureID, const float32 _fWidth, const float32 _fHeight,
									const D3DXVECTOR2& _vec2Position)
{
	CBillboard* pBillboard = new CBillboard;

	if(pBillboard->Initialise(_uiTextureID, _fWidth, _fHeight, _vec2Position))
	{
		for(int32 i = 0; i < 64; ++i)
		{
			if(m_apBillboards[i] == 0)
			{
				m_apBillboards[i] = pBillboard;
				return(i);
			}
		}
	}

    delete pBillboard;

	return(BAD_ID);
}

/**
* 
* Returns a pointer to the billboard at the index passed in.
* 
* @author Rebeccah Cox
* @return CBillboard* m_apBillboard - the billboard at the index passed in.
*/
CBillboard*
CBillboardManager::GetBillboard(uint32 _uiID)
{
	return (m_apBillboards[_uiID]);
}

/**
* 
* Calls the OnDeviceLost function in each instance of CBillboard in the array.
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboardManager::OnDeviceLost()
{
	for(int32 iBillboard = 0; iBillboard < 64; ++iBillboard)
	{
		if(0 != m_apBillboards[iBillboard])
		{
			m_apBillboards[iBillboard]->OnDeviceLost();
		}
	}
}

/**
* 
* Calls the OnDeviceReset function in each instance of CBillboard in the array.
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboardManager::OnDeviceReset()
{
	for(int32 iBillboard = 0; iBillboard < 64; ++iBillboard)
	{
		if(0 != m_apBillboards[iBillboard])
		{
			m_apBillboards[iBillboard]->OnDeviceReset();
		}
	}
}

/**
* 
* Deletes all of the CBillboards in the array.
* 
* @author Rebeccah Cox
* @return void
*/
void
CBillboardManager::ClearManager()
{
	for(int32 iBillboard = 0; iBillboard < 64; ++iBillboard)
	{
		if(0 != m_apBillboards[iBillboard])
		{
			delete m_apBillboards[iBillboard];
			m_apBillboards[iBillboard] = 0;
		}
	}
}

/**
* 
* Calculates the inverse of the camera's view matrix once per frame.
* Scales the billboard to the width and height stored in the billboard object.
* Sets the billboard's position in the world matrix.
* Calls each billboard's draw function.
* 
* @author Rebeccah Cox
* @param uint32 _uiID - the ID of the Billboard to be drawn.
* @return void
*/
void
CBillboardManager::Draw(const uint32 _kuiID)
{
	// If the billboard ID is valid.
	if(BAD_ID != _kuiID)
    {
	    m_apBillboards[_kuiID]->Draw();
    }
}

// Private functions to stop more than one instance of CBillboard being created.

/**
* 
* Private constructor. Not to be used outside of this class, because CBillboardManager is a singleton.
* 
* @author Rebeccah Cox
*/
CBillboardManager::CBillboardManager()
{
	memset(m_apBillboards, 0, sizeof(m_apBillboards));
}

/**
* 
* Private destructor. Not to be used outside this class, because CBillboardManager is a singleton.
* 
* @author Rebeccah Cox
*/
CBillboardManager::~CBillboardManager()
{
	for(int32 iBillboard = 0; iBillboard < 64; ++iBillboard)
	{
		if(0 != m_apBillboards[iBillboard])
		{
			delete m_apBillboards[iBillboard];
			m_apBillboards[iBillboard] = 0;
		}
	}
}