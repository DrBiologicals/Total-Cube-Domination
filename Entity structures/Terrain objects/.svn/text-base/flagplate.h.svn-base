// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagplate.h
//  Description :   Declaration for Cflagplate
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//
#ifndef __IGFEB10_MODULE_FLAGPLATE_H__
#define __IGFEB10_MODULE_FLAGPLATE_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "tile.h"
// Types

// Prototypes


class CFlagPlate : public CTile
{
	// Member Functions
public:
	CFlagPlate();
	virtual ~CFlagPlate();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, ETeam _eTeam, uint32 _uiTextureID, uint32 _uiModelID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	void RemoveFlag();
	void AddFlag();
	bool HasFlag();

	const D3DVECTOR* GetPosition();

protected:

private:

	// Member Variables
public:

protected:
	bool m_bHaveFlag;

private:

}; 

#endif // __IGFEB10_MODULE_FLAGPLATE_H__

