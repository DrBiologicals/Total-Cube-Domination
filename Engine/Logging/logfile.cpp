//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logFile.cpp
//  Description :   CLogFile implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "logFile.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLogFile::CLogFile()
{
}

CLogFile::~CLogFile()
{
	m_outputFile.close();
}

/**
*
* This function initialises the text file log target
* 
* @author Daniel Jay
* @param _kpcFileName A pointer to the file name of the log file
* @return Whether the file was successfully opened or not
*
*/
bool
CLogFile::Initialise(const char* _kpcFileName)
{
	m_outputFile.open(_kpcFileName);

	return (m_outputFile.good());
}

/**
*
* This function is empty
* 
* @author Daniel Jay
* @param _fDeltaTick The time difference between the current and last frames
*
*/
void
CLogFile::Process(float32 _fDeltaTick)
{
}

/**
*
* This function writes a message to the log text file
* 
* @author Daniel Jay
* @param _kpcMessage A pointer to the message to be logged
*
*/
void
CLogFile::WriteLine(const char* _kpcMessage)
{
	m_outputFile << _kpcMessage << std::endl;
}