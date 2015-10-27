// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   programstate.h
//  Description :   Declaration for CProgramState
//  Author      :   
//  Mail        :   @mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PROGRAMSTATE_H__
#define __IGFEB10_MODULE_PROGRAMSTATE_H__

// Library Includes

// Local Includes

// Types

// Prototypes
class CTotalCubeDomination;

class CProgramState
{
	// Member Functions
public:
	CProgramState();
	virtual ~CProgramState();

	virtual bool Initialise() = 0;

	void SetOwner(CTotalCubeDomination* _pOwner);
	virtual void Process(float32 _fDeltaTick) = 0;

	static bool IsPlayerGreen(uint32 _uiControllerID);
	static uint32 GetLevelNumber();
	static uint32 GetNumPlayers();
	static uint32 GetDifficulty();

	static void SetPlayerTeam(uint32 _uiPlayerID, bool _bIsGreen);
	static void SetLevelNumber(uint32 _uiLevelID);
	static void SetNumPlayer(uint32 _uiNumPlayers);
	static void SetDifficulty(uint32 _uiDifficulty);

protected:

private:

	// Member Variables
public:

protected:
	CTotalCubeDomination* m_pOwner;

	static bool s_bPlayerIsGreen[4];
	static uint32 s_uiNumPlayers;
	static uint32 s_uiLevelID;
	static uint32 s_uiDifficulty;

private:

}; 

#endif // __IGFEB10_MODULE_PROGRAMSTATE_H__

