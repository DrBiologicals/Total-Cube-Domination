// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   mine.h
//  Description :   Declaration for Cmine
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_MINE_H__
#define __IGFEB10_MODULE_MINE_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../renderentity.h"

// Types

// Prototypes
class CTank;

class CMine : public CRenderEntity
{
	// Member Functions
public:
	CMine();
	virtual ~CMine();

	static void LoadAssets();

	bool Initialise(CTank* _pTankOwner);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	void Explode(float32 _fExplosionTimer);

	bool IsActive();
	void SetActive(bool _bActive);

	void SetExplodeRadius(float32 _fRadius);
	float32 GetExplodeRadius();

	void SetModelID(uint32 _uiID);
	void SetTextureIDs(uint32 _uiGreenID, uint32 _uiPurpleID);

	void SetOwner(CTank* _pTankOwner);
	CTank* GetOwner();

	bool GetExploding();
	void SetExploding(bool _bExploding);

	D3DXVECTOR3 GetPosition();

	bool AddTankHit(CTank* _pTank);
	CTank* GetTank(int32 _iTankID);

	bool GetArmed();
	void SetArmed(bool _bArmed);

    static void SetAssestToBadID();

protected:

private:

	// Member Variables
public:

protected:
	CTank* m_pTankOwner;
	CTank* m_aTanksHit[8];

	float32 m_fLifeTimer;
	float32 m_fExplodeRadius;
	float32 m_fMaxRadius;
	float32 m_fExplosionTimer;
	
	static uint32 s_uiModelID;
	static uint32 s_uiGreenTextureID;
	static uint32 s_uiPurpleTextureID;
	static uint32 s_uiUnarmedTextureID;
	static uint32 s_uiSoundID;
	static uint32 s_uiExpldSoundID;
	static uint32 s_uiEmptySoundID;

	D3DXVECTOR3 m_vec3Position;

	static uint32 s_uiExTextureID;
	static uint32 s_uiExModelID;

	EFacePosition m_ePosition;

	bool m_bIsActive;
	bool m_bIsExploding;
	bool m_bIsArmed;

	static float32 s_fActivateTime;

private:

}; 

#endif // __IGFEB10_MODULE_MINE_H__

