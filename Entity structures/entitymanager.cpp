// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   entitymanager.cpp
//  Description :   entitymanager.cppfor implementation of entitymanager.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "entity.h"

// This Includes

#include "entitymanager.h"


// Static Variables
CEntityManager* CEntityManager::s_pEntityManager = 0;
// Static Function Prototypes


// Implementation
CEntityManager::CEntityManager()
{
}

CEntityManager::~CEntityManager()
{
}

/*
* 
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CEntityManager::Process(float32 _fDeltaTick)
{
	for(std::list<CEntity*>::iterator iter = m_listEntities.begin(); 
		iter != m_listEntities.end(); ++iter)
	{
		(*iter)->Process(_fDeltaTick);
	}
}

/*
* 
* @author Michael McQuarrie
* @param _pEntity
* @return void
*/
void
CEntityManager::AddEntity(CEntity* _pEntity)
{
	m_listEntities.push_back(_pEntity);
}

/*
* 
* @author Michael McQuarrie
* @param _iEntityID
* @return void
*/
void
CEntityManager::RemoveEntity(CEntity* _pEntity)
{
	m_listEntities.remove(_pEntity);
}

/*
* 
* @author Michael McQuarrie
* 
* @return void
*/
void
CEntityManager::DestroyInstance()
{
	delete s_pEntityManager;
	s_pEntityManager = 0;
}

/*
* 
* @author Michael McQuarrie
* 
* @return void
*/
CEntityManager&
CEntityManager::GetInstance()
{
	if(s_pEntityManager == 0)
	{
		s_pEntityManager = new CEntityManager;
	}

	return(*s_pEntityManager);
}