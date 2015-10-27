// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   collisionmanager.cpp
//  Description :   CCollisionManager implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Includes

#include "collisionmanager.h"

// Static Variables

// Static Function Prototypes
CCollisionManager* CCollisionManager::s_pInstance = 0;

// Implementation

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

/*
* GetInstance
* @author Rigardt de Vries
* @return CCollisionManager&
*/
CCollisionManager&
CCollisionManager::GetInstance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new CCollisionManager;
	}

	return(*s_pInstance);
}

/*
* DestroyInstance
* @author Rigardt de Vries
* 
* @return void
*/
void
CCollisionManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/**
* 
* Checks the positions of two bounding boxes against each other, and 
*	returns true if they have collided with each other. 
* 
* @author Rebeccah Cox
* @param TBoundingBox* _pBoxOne, TBoundingBox* _pBoxTwo
* @return bool bHaveCollided - returns true if there is a collision.
*/
bool
CCollisionManager::CheckBoxToBoxCollision(const TBoundingBox& _pBoxOne, const TBoundingBox& _pBoxTwo)
{
	if (_pBoxOne.m_vec3Max.x < _pBoxTwo.m_vec3Min.x) return (false);
	if (_pBoxOne.m_vec3Min.x > _pBoxTwo.m_vec3Max.x) return (false);
	if (_pBoxOne.m_vec3Max.y < _pBoxTwo.m_vec3Min.y) return (false);
	if (_pBoxOne.m_vec3Min.y > _pBoxTwo.m_vec3Max.y) return (false);
	if (_pBoxOne.m_vec3Max.z < _pBoxTwo.m_vec3Min.z) return (false);
	if (_pBoxOne.m_vec3Min.z > _pBoxTwo.m_vec3Max.z) return (false);

	return (true);
}

/**
* 
* Used to check collisions between game objects and a mine/EMP explosion. 
* Object one refers to the game object's position, object two refers to the 
*	center of the explosion and the radius of it. 
* 
* @author Rebeccah Cox
* @param D3DXVECTOR3* _pObjectOnePosition, D3DXVECTOR3* _pObjectTwoPosition, float32 _fObjectTwoRadius
* @return bool bHasCollided - returns true if there is a collision.
*/
bool
CCollisionManager::CheckPointToSphereCollision(const D3DXVECTOR3& _pObjectOnePosition, const D3DXVECTOR3& _pObjectTwoPosition,
										float32 _fObjectTwoRadius)
{
	bool bHaveCollided = false;

	D3DXVECTOR3 vec3Distance = _pObjectTwoPosition - _pObjectOnePosition;

	float32 fDistSquared = D3DXVec3LengthSq(&vec3Distance);

	if(_fObjectTwoRadius * _fObjectTwoRadius >= fDistSquared)
	{
		bHaveCollided = true;
	}

	return (bHaveCollided);
}
