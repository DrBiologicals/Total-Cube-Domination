// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logutil.cpp
//  Description :   
//  Author      :   
//  Mail        :   
//

// Library Includes

// Local Includes

// This Include
#include "logutil.h"

// Static Variables

// Static Function Prototypes

// Implementation
/**
*
* This function logs a message through the game's logging system
*
* @author Daniel Jay
* @param _kpcMessage The message to log
* @param _eType The type of logging message
*
*/

#ifdef _DEBUG
void LogMessage(const char* _kpcMessage, ELogMessageType _eType)
{
	CTotalCubeDomination::GetInstance().LogMessage(_kpcMessage, _eType);
}
#endif // _DEBUG