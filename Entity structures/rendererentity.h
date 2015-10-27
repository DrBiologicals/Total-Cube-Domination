// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   rendererentity.h
//  Description :   Declaration for CRendererEntity
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_RENDERERENTITY_H__
#define __IGFEB10_MODULE_RENDERERENTITY_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Prototypes


class CRendererEntity : public CEntity
{
	// Member Functions
public:
	CRendererEntity();
	virtual ~CRendererEntity();

	virtual void Process(float _fDeltaTick);
	virtual void Draw();

protected:

private:

	// Member Variables
public:

protected:

private:

}; 

#endif // __IGFEB10_MODULE_RENDERERENTITY_H__

