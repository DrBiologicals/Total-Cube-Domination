// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   entity.cpp
//  Description :   entity.cppfor implementation of entity.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "entitymanager.h"

// This Includes

#include "entity.h"

// Static Variables

// Static Function Prototypes


// Implementation
CEntity::CEntity()
{

}

CEntity::~CEntity()
{
	CEntityManager::GetInstance().RemoveEntity(this);
}

void
CEntity::Initialise()
{
	CEntityManager::GetInstance().AddEntity(this);
}