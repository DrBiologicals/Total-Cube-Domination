// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   angle.h
//  Description :
//  Author      :
//  Mail        :
//

#ifndef __IGFEB10_MODULE_ANGLE_H__
#define __IGFEB10_MODULE_ANGLE_H__

// Library Includes

// Local Includes

// Types

// Prototypes
const float32 kf2Pi = D3DX_PI * 2.0f;

class CAngle
{
	// Member Functions
public:
	CAngle();
	~CAngle();

	float32 GetAngle() const;
	void SetAngle(float32 _fAngle);

	void TurnTowardsAngle(const CAngle& _krTarget, float32 _fTurnAmount);

protected:

private:

	// Member Variables
public:

protected:
	float32 m_fAngle;

private:

}; 

#endif