//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   logFrameBuffer.h
//  Description :   CLogFrameBuffer declaration file.
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB10_MODULE_LOGFRAMEBUFFER_H__
#define __IGFEB10_MODULE_LOGFRAMEBUFFER_H__

// Library Includes
#include <d3dx9.h>
#include <string>
#include <list>

// Local Includes
#include "ilogTarget.h"

// Types

// Constants

// Prototypes

class CLogFrameBuffer: public ILogTarget
{
	// Member Functions
public:
	CLogFrameBuffer();
	~CLogFrameBuffer();

	bool Initialise(const RECT& _krTextRect);
	void Process(float _fDeltaTick);
	void Draw();
	void WriteLine(const char* _kpcMessage);

protected:

private:

	// Member Variables
public:

protected:
	ID3DXFont* m_pFont;

	float m_fTimer;
	std::list<std::string> m_listMessages;

	RECT m_textRect;

private:

};

#endif // __IGFEB10_MODULE_LOGFRAMEBUFFER_H__
