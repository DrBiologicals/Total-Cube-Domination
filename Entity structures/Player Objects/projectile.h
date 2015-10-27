// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   projectile.h
//  Description :   Declaration for Cprojectile
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PROJECTILE_H__
#define __IGFEB10_MODULE_PROJECTILE_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../../defines.h"
#include "../renderentity.h"

// Types

// Prototypes
class CTank;

class CProjectile : public CRenderEntity
{
	// Member Functions
public:
	CProjectile();
	virtual ~CProjectile();

	virtual bool Initialise(D3DXVECTOR3 _vec3Position, CTank* _pTankOwner, D3DXVECTOR3 _vec3Direction,
							D3DXVECTOR3 _vec3Right) = 0;

	virtual void Process(float32 _fDeltaTick) = 0;
	virtual void Draw() = 0;

	virtual float32 GetMoveSpeed();
	virtual void SetMoveSpeed(float32 _fmoveSpeed);

    void SetFace(EFacePosition _eFaceposition);
	EFacePosition GetFacePosition();
    const D3DXVECTOR3& GetPosition() const;

	bool GetAlive();

	virtual void SetAlive(bool _bAlive);

	virtual void StartTransition(EFacePosition _eTargetFace) = 0;

protected:

private:

	// Member Variables
public:

protected:
	float32 m_fDamage;
	float32 m_fMovementSpeed;

	D3DXVECTOR3 m_vec3Position;
	D3DXVECTOR3 m_vec3Direction;
	D3DXVECTOR3 m_vec3Up;
	D3DXVECTOR3 m_vec3Right;

	bool m_bAlive;

    EFacePosition m_eFacePosition;

	float32 m_fOffset;

private:

}; 

#endif // __IGFEB10_MODULE_PROJECTILE_H__

