// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   ammoplate.h
//  Description :   Declaration for Cammoplate
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AMMOPLATE_H__
#define __IGFEB10_MODULE_AMMOPLATE_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "../Player Objects/tank.h"
#include "tile.h"

// Types

// Prototypes
enum EFacePosition;

class CAmmoPlate : public CTile
{
	// Member Functions
public:
	CAmmoPlate();
	virtual ~CAmmoPlate();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY);
	
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();
	void CauseEffect(CTank& _rTank);

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_AMMOPLATE_H__

