//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logDebugOutput.h
//  Description :   CLogDebugOutput declaration file.
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB10_MODULE_LOGDEBUGOUTPUT_H__
#define __IGFEB10_MODULE_LOGDEBUGOUTPUT_H__

// Library Includes

// Local Includes
#include "ilogTarget.h"

// Types

// Constants

// Prototypes

class CLogDebugOutput: public ILogTarget
{
	// Member Functions
public:
	CLogDebugOutput();
	~CLogDebugOutput();

	void Process(float32 _fDeltaTick);
	void WriteLine(const char* _kpcMessage);

protected:

private:

	// Member Variables
public:

protected:

private:

};

#endif // __IGFEB10_MODULE_LOGDEBUGOUTPUT_H__
