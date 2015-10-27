// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   projectile.cpp
//  Description :   projectile.cppfor implementation of projectile.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "tank.h"

// This Includes
#include "projectile.h"

// Static Variables

// Static Function Prototypes

// Implementation

CProjectile::CProjectile()
: m_fDamage(0.0f)
, m_fMovementSpeed(0.0f)
, m_fOffset(1.07f)
, m_bAlive(true)
{
}

CProjectile::~CProjectile()
{
}

float32 
CProjectile::GetMoveSpeed()
{
	return (m_fMovementSpeed);
}

void
CProjectile::SetMoveSpeed(float32 _fMoveSpeed)
{
	m_fMovementSpeed = _fMoveSpeed;
}

/*
* GetPosition
* @author Rigardt de Vries
* @return D3DXVECTOR3&
*/
const D3DXVECTOR3&
CProjectile::GetPosition() const
{
    return (m_vec3Position);
}

/*
* SetFace
* @author Rigardt de Vries
* @param _eFacePosition         the new face
* @return void
*/
void 
CProjectile::SetFace(EFacePosition _eFacePosition)
{
    m_eFacePosition = _eFacePosition;
}


bool
CProjectile::GetAlive()
{
	return(m_bAlive);
}

void
CProjectile::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

/*
* GetFacePosition
* @athour Rigardt de Vries
* @return EFacePosition
*/
EFacePosition 
CProjectile::GetFacePosition()
{
	return (m_eFacePosition);
}