//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logmanager.h
//  Description :   CLogManager declaration file
//  Author      :   Daniel Jay
//  Mail        :   ryan.jay@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB10_MODULE_LOGMANAGER_H__
#define __IGFEB10_MODULE_LOGMANAGER_H__

// Library Includes
#include <list>

// Local Includes

// Types

// Constants

// Prototypes
class ILogTarget;

class CLogManager
{
	// Member Functions
public:
	CLogManager();
	~CLogManager();

	void AddLogTarget(ILogTarget* _pLogTarget);
	void WriteLine(const char* _kpcMessage);
	void Process(float32 _fDeltaTick);

protected:

private:

	// Member Variables
public:

protected:
	std::list<ILogTarget*> m_listLogTargets;

private:

};

#endif // __IGFEB10_MODULE_LOGMANAGER_H__
