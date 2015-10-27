//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logFile.h
//  Description :   CLogFile declaration file.
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB10_MODULE_LOGFILE_H__
#define __IGFEB10_MODULE_LOGFILE_H__

// Library Includes
#include <fstream>

// Local Includes
#include "ilogtarget.h"

// Types

// Constants

// Prototypes

class CLogFile: public ILogTarget
{
	// Member Functions
public:
	CLogFile();
	~CLogFile();

	bool Initialise(const char* _kpcFileName);
	void Process(float32 _fDeltaTick);
	void WriteLine(const char* _kpcMessage);

protected:

private:

	// Member Variables
public:

protected:
	std::ofstream m_outputFile;

private:

};

#endif // __IGFEB10_MODULE_LOGFILE_H__
