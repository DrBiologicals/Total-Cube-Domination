// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flamegrate.h
//  Description :   Declaration for Cflamegrate
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_FLAMEGRATE_H__
#define __IGFEB10_MODULE_FLAMEGRATE_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "../Player Objects/tank.h"
#include "tile.h"

// Types

// Prototypes


class CFlameGrate : public CTile
{
	// Member Functions
public:
	CFlameGrate();
	virtual ~CFlameGrate();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 _uiModelID, uint32 _uiTextureID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	bool GetActive();

	float32 GetDamagePerSecond();

protected:

private:

	// Member Variables
public:

protected:
	bool m_bActive;
	float32 m_fCurrentTime;
	int32 m_iBurstDelay;
	int32 m_iTimeLeft;
	int32 m_iEmitterID;
	float32 m_fDamagePerSecond;

	static uint32 s_uiSoundID;

private:

}; 

#endif // __IGFEB10_MODULE_FLAMEGRATE_H__

