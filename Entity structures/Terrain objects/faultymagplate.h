// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   faultymagplate.h
//  Description :   Declaration for Cfaultymagplate
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_FAULTYMAGPLATE_H__
#define __IGFEB10_MODULE_FAULTYMAGPLATE_H__

// Library Includes

// Local Includes
#include "../Player Objects/tank.h"
#include "../../defines.h"
#include "tile.h"

// Types

// Prototypes


class CFaultyMagPlate : public CTile
{
	// Member Functions
public:
	 CFaultyMagPlate();
	virtual ~CFaultyMagPlate();

	bool Initialise(int32 _iX, int32 _iY, EFacePosition _eFace, uint32 _uiModelID, uint32 _uiTextureID, EFileDirection _eDir);
	 virtual void Process(float32 _fDeltaTick);
	 virtual void Draw();

	 void CauseEffect(CTank& _rTank);
     void RemoveCauseEffect(CTank& _rTank);

	 EDirection GetDirection() const;

protected:

private:

	// Member Variables
public:

protected:
    D3DXVECTOR3 m_vec3EffectDirection;
	EDirection m_eDirection;

private:

}; 

#endif // __IGFEB10_MODULE_FAULTYMAGPLATE_H__

