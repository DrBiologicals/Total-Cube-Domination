//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logDebugOutput.cpp
//  Description :   CLogDebugOutput implementation file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes

// This Include
#include "logdebugoutput.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLogDebugOutput::CLogDebugOutput()
{
}

CLogDebugOutput::~CLogDebugOutput()
{
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
CLogDebugOutput::Process(float32 _fDeltaTick)
{
}

/**
*
* This function writes a message to the IDE's output window
* 
* @author Daniel Jay
* @param _kpcMessage A pointer to the message to be logged
*
*/
void
CLogDebugOutput::WriteLine(const char* _kpcMessage)
{
	OutputDebugString(_kpcMessage);
	OutputDebugString("\r");
}
