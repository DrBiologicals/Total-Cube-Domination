// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   wall.h
//  Description :   Declaration for Cwall
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_WALL_H__
#define __IGFEB10_MODULE_WALL_H__

// Library Includes

// Local Includes
#include "../../defines.h"
#include "tile.h"
// Types

// Prototypes


class CWall : public CTile
{
	// Member Functions
public:
	CWall();
	virtual ~CWall();

	bool Initialise(EFacePosition _eSide, int32 _iX, int32 _iY, uint32 uiWallModelID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();
	const D3DXVECTOR3& GetPosition();

    const D3DXVECTOR3& GetWallNormal(EWallSide _eSide) const;

protected:

private:

	// Member Variables
public:

protected:
    D3DXVECTOR3 m_vec3SideNormals[4];

private:

}; 

#endif // __IGFEB10_MODULE_WALL_H__

