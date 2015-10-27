// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   staticgraphic.h
//  Description :   Declaration for Cstaticgraphic
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_STATICGRAPHIC_H__
#define __IGFEB10_MODULE_STATICGRAPHIC_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "menuitem.h"

// Types

// Prototypes

class CStaticGraphic : public CMenuItem
{
	// Member Functions
public:
	CStaticGraphic();
	virtual ~CStaticGraphic();

	bool Initialise(uint32 _uiBillboardID);

	virtual void Process(float32 _fDeltaTick);
	void Draw();

	uint32 GetBillboardID();

	D3DXMATRIX GetWorldMatrix();

	virtual void Reset();

protected:

private:

	// Member Variables
public:

protected:
	uint32 m_uiBillboardID;

	D3DXVECTOR2 m_vec2Position;

private:

}; 

#endif // __IGFEB10_MODULE_STATICGRAPHIC_H__

