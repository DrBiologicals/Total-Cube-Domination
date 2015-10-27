//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logManager.cpp
//  Description :   CLogManager implementation file.
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "ilogtarget.h"

// This Include
#include "logmanager.h"

// Static Variables

// Static Function Prototypes

// Implementation

// Constructor
CLogManager::CLogManager()
{
}

// Destructor
CLogManager::~CLogManager()
{
	for (std::list<ILogTarget*>::iterator iter = m_listLogTargets.begin();
		iter != m_listLogTargets.end(); ++iter)
	{
		delete *iter;
	}

	m_listLogTargets.clear();
}

/**
*
* This function adds a log target to the manager's list of targets to log to and update
* 
* @author Daniel Jay
* @param _pLogTarget A pointer to the log target to be added
*
*/
void
CLogManager::AddLogTarget(ILogTarget* _pLogTarget)
{
	m_listLogTargets.push_back(_pLogTarget);
}

/**
*
* This function logs a message to the manager's log targets
* 
* @author Daniel Jay
* @param _kpcMessage A pointer to the message to be logged
*
*/
void
CLogManager::WriteLine(const char* _kpcMessage)
{
	for (std::list<ILogTarget*>::iterator iter = m_listLogTargets.begin();
		iter != m_listLogTargets.end(); ++iter)
	{
		(*iter)->WriteLine(_kpcMessage);
	}
}

/**
*
* This function processes all the log targets registered in this manager
* 
* @author Daniel Jay
* @param _fDeltaTick The time difference between the current and last frame
*
*/
void
CLogManager::Process(float32 _fDeltaTick)
{
	for (std::list<ILogTarget*>::iterator iter = m_listLogTargets.begin();
		iter != m_listLogTargets.end(); ++iter)
	{
		(*iter)->Process(_fDeltaTick);
	}
}