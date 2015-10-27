// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   entitymanager.h
//  Description :   Declaration for Centitymanager
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_ENTITYMANAGER_H__
#define __IGFEB10_MODULE_ENTITYMANAGER_H__

// Library Includes
#include <list>
#include "../defines.h"
// Local Includes

// Types

// Prototypes
class CEntity;

class CEntityManager
{
	// Member Functions
public:
	void Process(float32 _fDeltaTick);
	void AddEntity(CEntity* _pEntity);
	void RemoveEntity(CEntity* _pEntity);
	
	static CEntityManager& GetInstance();

	static void DestroyInstance();

protected:
	CEntityManager(const CEntityManager& _kr);
	CEntityManager& operator=(const CEntityManager& _kr);
private:
	CEntityManager();
	~CEntityManager();

	// Member Variables
public:

protected:

private:
	
	static CEntityManager* s_pEntityManager;
	std::list<CEntity*> m_listEntities;	

}; 

#endif // __IGFEB10_MODULE_ENTITYMANAGER_H__

