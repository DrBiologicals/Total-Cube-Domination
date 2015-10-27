// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstateMove.h
//  Description :   Declaration for CAISubstateMove
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISUBSTATEMOVE_H__
#define __IGFEB10_MODULE_AISUBSTATEMOVE_H__

// Library Includes

// Local Includes
#include "aisubstate.h"
#include "../../../defines.h"

// Types

// Prototypes
class CTank;
class CAIPlayer;

class CAISubstateMove : public CAISubstate
{
	// Member Functions
public:
	CAISubstateMove();
	virtual ~CAISubstateMove();
	bool Initialise(CTank* _pTank);

	virtual void Process(float32 _fDeltaTick);
	void SetTarget(int32 _iX, int32 _iY, EFacePosition _eFace);
	EDirection WanderAround();
	EDirection Wander();

protected:
	
private:

	// Member Variables
public:
	
protected:
	static CTank* s_pTank;
	//CAIPlayer* m_pOwner;
	EDirection m_eTransDir;
	EDirection m_eWanderDir;
	//m_fTransTime
private:
	
}; 

#endif // __IGFEB10_MODULE_AISUBSTATEMOVE_H__

