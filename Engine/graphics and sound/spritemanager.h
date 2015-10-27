// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   spritemanager.h
//  Description :   Declaration for CSpriteManager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SPRITEMANAGER_H__
#define __IGFEB10_MODULE_SPRITEMANAGER_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes

// Types
const int32 MAX_SPRITES = 32;

// Prototypes
class CSprite;

class CSpriteManager 
{
	// Member Functions
public:
	static CSpriteManager& GetInstance();
	static void DestroyInstance();

	bool Initialise();

	void Clear();

	void OnDeviceLost();
	void OnDeviceReset();

	uint32 CreateSprite(uint32 _uiTextureID, const RECT* _kpSourceRect);
	CSprite* GetSprite(uint32 _uiSpriteID);

protected:

private:
	CSpriteManager();
	CSpriteManager(const CSpriteManager& _kr);
	~CSpriteManager();
	CSpriteManager& operator =(const CSpriteManager& _kr);

	// Member Variables
public:

protected:
	static CSpriteManager* s_pInstance;

	CSprite* m_apSprites[MAX_SPRITES];

private:

}; 

#endif // __IGFEB10_MODULE_SPRITEMANAGER_H__

