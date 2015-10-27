// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   ammo.h
//  Description :   Declaration for CAmmo
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AMMO_H__
#define __IGFEB10_MODULE_AMMO_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "tile.h"
// Types

// Prototypes

class CAmmo : public CTile
{
	// Member Functions
public:
	CAmmo();
	virtual ~CAmmo();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiLightModelID,
					uint32 _uiTexturesID, ETeam _eTeam);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	bool CanBeTriggered();
	void Trigger();

	ETeam GetTeam();

protected:

private:

	// Member Variables
public:

protected:
	int32 m_iLightModelID;
	bool m_bCanBeTriggered;
	float32 m_fAmmoTimer;

	ETeam m_eTeam;

private:

}; 

#endif // __IGFEB10_MODULE_AMMO_H__

