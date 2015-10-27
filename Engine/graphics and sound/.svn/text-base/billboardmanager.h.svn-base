// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   billboardmanager.h
//  Description :   Declaration for CBillboardManager
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BILLBOARDMANAGER_H__
#define __IGFEB10_MODULE_BILLBOARDMANAGER_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes

// Types

// Prototypes
class CBillboard;

class CBillboardManager 
{
	// Member Functions
public:
	static CBillboardManager& GetInstance();
	static void DestroyInstance();

	uint32 CreateBillboard(uint32 _uiTextureID, const float32 _fWidth, const float32 _fHeight,
							const D3DXVECTOR2& _vec2Position = D3DXVECTOR2(0.0f, 0.0f));
	CBillboard* GetBillboard(uint32 _uiID);

	void OnDeviceLost();
    void OnDeviceReset();

	void ClearManager();

	void Draw(const uint32 _kuiID);

protected:

private:
	CBillboardManager();
	CBillboardManager(const CBillboardManager& _kr);
	~CBillboardManager();

	CBillboardManager& operator =(const CBillboardManager& _kr);

	// Member Variables
public:

protected:
	CBillboard* m_apBillboards[64];

private:
	// Singleton instance of this class.
	static CBillboardManager* s_pBillboardManager;

}; 

#endif // __IGFEB10_MODULE_BILLBOARDMANAGER_H__

