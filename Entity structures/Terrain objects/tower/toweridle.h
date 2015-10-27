// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   toweridle.h
//  Description :   Declaration for CTowerIdle
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TOWERIDLE_H__
#define __IGFEB10_MODULE_TOWERIDLE_H__

// Library Includes

// Local Includes
#include "toweraistate.h"

// Types

// Prototypes

class CTowerIdle : public CTowerAIState
{
	// Member Functions
public:
	CTowerIdle();
	virtual ~CTowerIdle();

	virtual bool Initialise(CTower* _pOwnerTower);
	virtual void Process(float32 _fDeltaTick);

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_TOWERIDLE_H__

