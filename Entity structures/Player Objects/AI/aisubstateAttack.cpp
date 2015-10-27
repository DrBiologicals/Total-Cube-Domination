// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstateAttack.cpp
//  Description :   aisubstateAttack.cpp for implementation of aisubstateAttack.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes
#include "aisubstateAttack.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAISubstateAttack::CAISubstateAttack()
{

}

CAISubstateAttack::~CAISubstateAttack()
{

}

bool CAISubstateAttack::Initialise(CTank* _pTank)
{
	m_pTank = _pTank;
	return(true);
}

void
CAISubstateAttack::Process(float32 _fDeltaTick)
{
	//chase/attack enemy
	FireAtEnemy();
}

