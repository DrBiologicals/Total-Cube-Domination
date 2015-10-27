// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstateFlee.cpp
//  Description :   aisubstateFlee.cpp for implementation of aisubstateFlee.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "pathfinder.h"

// This Includes
#include "aisubstateFlee.h"

// Static Variables

// Static Function Prototypes

// Implementation 

CAISubstateFlee::CAISubstateFlee()
{

}

CAISubstateFlee::~CAISubstateFlee()
{
	
}

bool CAISubstateFlee::Initialise(CTank* _pTank)
{
	m_pTank = _pTank;
	return(true);
}

void
CAISubstateFlee::Process(float32 _fDeltaTick)
{
	//move away from the target
	//try not to move towards another enemy
	//try not to move into a dead end
	FireAtEnemy();
}

