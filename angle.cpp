// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   angle.cpp
//  Description :   
//  Author      :   
//

// Library Includes

// Local Includes

// This Includes
#include "angle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAngle::CAngle()
: m_fAngle(0.0f)
{
}

CAngle::~CAngle()
{
}

float32 
CAngle::GetAngle() const
{
	return (m_fAngle);
}

void 
CAngle::SetAngle(float32 _fAngle)
{
	m_fAngle = _fAngle;

	while (m_fAngle < 0.0f)
	{
		m_fAngle += kf2Pi;
	}

	while (m_fAngle >= kf2Pi)
	{
		m_fAngle -= kf2Pi;
	}
}

void 
CAngle::TurnTowardsAngle(const CAngle& _krTarget, float32 _fTurnAmount)
{
	if(_fTurnAmount)
	{
		float32 fRelativeTargetAngle = _krTarget.m_fAngle - m_fAngle;

		while (fRelativeTargetAngle <= -D3DX_PI)
		{
			fRelativeTargetAngle += kf2Pi;
		}

		while (fRelativeTargetAngle > D3DX_PI)
		{
			fRelativeTargetAngle -= kf2Pi;
		}

		float32 fNewAngle = m_fAngle;

		if (fRelativeTargetAngle > 0.0f)
		{
			fNewAngle += _fTurnAmount;

			if (fNewAngle - m_fAngle > fRelativeTargetAngle)
			{
				fNewAngle = m_fAngle + fRelativeTargetAngle;
			}
		}
		else if (fRelativeTargetAngle < 0.0f)
		{
			fNewAngle -= _fTurnAmount;

			if (fNewAngle - m_fAngle < fRelativeTargetAngle)
			{
				fNewAngle = m_fAngle + fRelativeTargetAngle;
			}
		}

		SetAngle(fNewAngle);
	}
}