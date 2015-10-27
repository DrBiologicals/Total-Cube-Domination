// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   renderentity.h
//  Description :   Declaration for CRenderEntity
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_renderentity_H__
#define __IGFEB10_MODULE_renderentity_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Prototypes

class CRenderEntity : public CEntity
{
	// Member Functions
public:
	CRenderEntity();
	virtual ~CRenderEntity();

	virtual void Process(float32 _fDeltaTick) = 0;
	virtual void Draw() = 0;

    const D3DXMATRIX& GetWorldMatrix() const;
	void SetWorldMatrix(D3DXMATRIX& _rMatrix);

	const TBoundingBox& GetBoundingBox() const;

	void CreateAABB();

protected:

private:

	// Member Variables
public:

protected:
	D3DXMATRIX m_matWorld;
    TBoundingBox m_tAABB;
	TBoundingBox m_tOBB;

private:

}; 

#endif // __IGFEB10_MODULE_renderentity_H__

