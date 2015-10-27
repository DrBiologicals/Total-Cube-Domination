//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aiTest.h
//  Description :   CAiTest declaration file.
//  Author      :   Rebeccah Cox
//  Mail        :   rebeccah.cox@mediadesign.school.nz
//

#ifdef _DEBUG

#pragma once

#ifndef __IGFEB10_MODULE_AITEST_H__
#define __IGFEB10_MODULE_AITEST_H__

// Library Includes

// Local Includes
#include "test.h"
#include "../../Entity structures/Player Objects/AI/aiplayer.h"
#include "../../Entity structures/Player Objects/tank.h"
#include "../../Entity structures/Terrain Objects/flag.h"
#include "../../Entity structures/Terrain Objects/flagplate.h"

// Types

// Constants

// Prototypes

class CAiTest: public ITest
{
	// Member Functions
public:
	CAiTest();
	~CAiTest();

	void SetUp();
	void TearDown();
	bool RunTest();

	// Functions specific to this class.
	// Run test to check if AI players are initially set to the "Idle" state.
	bool InitialisedToIdleStateTest();
	// Run test to check if AI players choose "GetFlag" state in correct circumstance.
	bool GetFlagStateTest();
	// Run test to check if AI players choose "CaptureFlag" state in correct circumstance.
	bool CaptureFlagStateTest();
	// Run test to check if AI players choose "ProtectFlag" state in correct circumstance.
	bool ProtectFlagStateTest();
	// Run test to check if AI players choose "ProtectPlayer" state in correct circumstance.
	bool ProtectPlayerStateTest();

protected:

private:

	// Member Variables
public:

protected:

private:
	CAIPlayer* m_apAiPlayers[3];
	CTank* m_apAiTanks[3];
	CFlag* m_pFlag;
	CFlagPlate* m_pFlagPlate;

};

#endif // __IGFEB10_MODULE_AITEST_H__
#endif // _DEBUG