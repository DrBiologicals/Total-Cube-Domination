// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   entity.h
//  Description :   Declaration for Centity
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_ENTITY_H__
#define __IGFEB10_MODULE_ENTITY_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../defines.h"
#include "../boundingbox.h"

// Types

// Prototypes

class CEntity
{
	// Member Functions
public:
	CEntity();
	virtual ~CEntity();

	virtual void Process(float32 _fDeltaTick) = 0;
	void Initialise();

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_ENTITY_H__

