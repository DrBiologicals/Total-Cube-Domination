// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   texturemanager.h
//  Description :   Declaration for CTextureManager
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TEXTUREMANAGER_H__
#define __IGFEB10_MODULE_TEXTUREMANAGER_H__

// Library Includes

// Local Includes

// Types
const int32 MAX_TEXTURES = 64;

// Prototypes
class CTexture;

class CTextureManager
{
	// Member Functions
public:

	static CTextureManager& GetInstance();
	static void DestroyInstance();

	bool Initialise();

    void Clear();

	void OnDeviceLost();
	void OnDeviceReset();

	uint32 CreateTexture(const char* _kpcFileName);
	void SetTexture(uint32 _uiTextureStage, uint32 _uiID);

	CTexture* GetTexture(uint32 _uiTextureID);

protected:

private:
	CTextureManager();
	CTextureManager(const CTextureManager& _kr);
	~CTextureManager();

	CTextureManager& operator =(const CTextureManager& _kr);

	// Member Variables
public:

protected:
	CTexture* m_apTextures[MAX_TEXTURES];

    static uint32 s_uiCurrentTexture;

    static CTextureManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_TEXTUREMANAGER_H__

