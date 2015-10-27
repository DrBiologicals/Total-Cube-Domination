// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   collisionmanager.h
//  Description :   Declaration file for CCollisionManager
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_COLLISIONMANAGER_H__
#define __IGFEB10_MODULE_COLLISIONMANAGER_H__

// Library Includes
#include <d3dx9.h>

// Local Includes
#include "../../boundingbox.h"
#include "../../defines.h"

// Types

// Prototypes

class CCollisionManager
{
	// Member Functions
public:
	static CCollisionManager& GetInstance();
	static void DestroyInstance();

	bool CheckBoxToBoxCollision(const TBoundingBox& _pBoxOne, const TBoundingBox& _pBoxTwo);
	bool CheckPointToSphereCollision(const D3DXVECTOR3& _pObjectOnePosition, const D3DXVECTOR3& _pObjectTwoPosition,
										float32 _fObjectTwoRadius);

protected:
	CCollisionManager();
	~CCollisionManager();

private:

	// Member Variables
public:

protected:
	static CCollisionManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_COLLISIONMANAGER_H__

