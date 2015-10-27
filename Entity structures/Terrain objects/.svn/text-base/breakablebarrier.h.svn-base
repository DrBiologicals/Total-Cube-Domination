// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   breakablebarrier.h
//  Description :   Declaration for Cbreakablebarrier
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BREAKABLEBARRIER_H__
#define __IGFEB10_MODULE_BREAKABLEBARRIER_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "tile.h"

// Types

// Prototypes


class CBreakableBarrier : public CTile
{
	// Member Functions
public:
	CBreakableBarrier();
	virtual	~CBreakableBarrier();

	bool Initialise(EFacePosition _ESide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiTextureID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	void Damage(int32 _iDamage);
    bool IsDestroyed();


protected:

private:

	// Member Variables
public:

protected:
	int32 m_iHealth;

private:

}; 

#endif // __IGFEB10_MODULE_BREAKABLEBARRIER_H__

