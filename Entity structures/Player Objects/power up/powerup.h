// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   powerup.h
//  Description :   Declaration for Cpowerup
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_POWERUP_H__
#define __IGFEB10_MODULE_POWERUP_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../../renderentity.h"
#include "../../../defines.h"
#include "../../Terrain objects/tile.h"
// Types

// Prototypes
enum EPowerUpType
{
	POWERUP_INVISIBILITY,
	POWERUP_OVERSHIELD,
	POWERUP_MAX
};

class CPowerUp : public CRenderEntity
{
	// Member Functions
public:
	CPowerUp();
	virtual ~CPowerUp();

	bool Initialise(const D3DXVECTOR3& _rvec3Position, EPowerUpType _ePowerUpType, EFacePosition _eFace, uint32 _uiModelID,
					uint32 _uiTextureID);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	uint32 GetTextureID();
	uint32 GetModelID();

	EPowerUpType GetPowerUpType();

	void SetActive(bool _bIsActive);
	bool IsActive();

protected:

private:

	// Member Variables
public:

protected:
	EPowerUpType m_ePowerUpType;
	bool m_bIsActive;

    EFacePosition m_eFace;
    D3DXVECTOR3 m_vec3Position;

    uint32 m_uiModelID;
    uint32 m_uiTextureID;

private:

}; 

#endif // __IGFEB10_MODULE_POWERUP_H__

