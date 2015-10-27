//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   debugcamera.h
//  Description :   debugcamera declaration (header) file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#pragma once

#if !defined(__IGFEB10_IG300_DEBUGCAMERA_H__)
#define __IGFEB10_IG300_DEBUGCAMERA_H__

// Library Includes

#ifdef _DEBUG
// Local Includes
#include "../../defines.h"
#include "../Input/input.h"
#include "camera.h"

// Types

// Constants

// Prototypes
class CViewport;

class CDebugCamera : public CCamera
{
    // Member Functions
public:
	CDebugCamera();
	virtual ~CDebugCamera();

	virtual void Process(float32 _fDeltaTick);

	// Functions not inherited from CCamera.
	void ProcessControls(float32 _fDeltaTick);

protected:

private:

    // Member Variables
public:

protected:

private:

};

#endif _DEBUG
#endif // __IGFEB10_IG300_DEBUGCAMERA_H__


