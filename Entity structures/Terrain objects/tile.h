// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   tile.h
//  Description :   Declaration for Ctile
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_TILE_H__
#define __IGFEB10_MODULE_TILE_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
// Local Includes
#include "../../defines.h"
#include "../renderentity.h"
#include "../../boundingbox.h"

// Types

// Prototypes

class CTile : public CRenderEntity
{
	// Member Functions
public:
	CTile();
	virtual ~CTile();

	virtual void Process(float32 _fDeltaTick) = 0;
	virtual void Draw() = 0;

	int32 GetX() const;
	int32 GetY() const;

	bool SetModel(int32 _iModelID);
	bool SetTexture(int32 _iTextureID);

	virtual bool IsTraversable() const;

	EFacePosition GetFacePosition() const;

protected:

private:

	// Member Variables
public:

protected:
	EFacePosition m_eFace;
	int32 m_iX;
	int32 m_iY;

	D3DXVECTOR3 m_vec3Position;

	D3DXVECTOR3 m_vec3Up;
	D3DXVECTOR3 m_vec3Right;
	D3DXVECTOR3 m_vec3Direction;

	int32 m_iTextureID;
	int32 m_iModelID;
	bool m_bTraversable;

private:

}; 

#endif // __IGFEB10_MODULE_TILE_H__

