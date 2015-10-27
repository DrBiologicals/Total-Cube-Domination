//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   igutils.h
//  Description :   igutils declaration file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//


#pragma once

#if !defined(__IGFEB10_IG200_IGUTILS_H__)
#define __IGFEB10_IG200_IGUTILS_H__

// Library Includes
#include <sstream>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
#define VALIDATE(a) if (!(a)) return (false)

template<typename T>
std::string ToString(const T& _value)
{
	std::ostringstream theStream;
	theStream << _value;
	return(theStream.str());
}

#endif // __IGFEB10_IG200_IGUTILS_H__
