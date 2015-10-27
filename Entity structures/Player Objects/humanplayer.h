// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   humanplayer.h
//  Description :   Declaration for Chumanplayer
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_HUMANPLAYER_H__
#define __IGFEB10_MODULE_HUMANPLAYER_H__

// Library Includes
#include <windowsx.h>

// Local Includes
#include "player.h"

// Types

// Prototypes
class CTank;
class CHUD;
class CCamera;

class CHumanPlayer : public CPlayer
{
	// Member Functions
public:
	CHumanPlayer();
	virtual ~CHumanPlayer();

	virtual bool Initialise(CTank* _pTank, uint32 _uiControllerID,int32 _iPlayerID, ETeam _eTeam);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	virtual uint32 GetControllerID();

	void SetCamera(uint32 _uiID, uint32 _uiViewportNumber);

	bool GetIfDisabled();
	void SetIfDisabled(bool _bIsDisabled);

protected:

private:

	// Member Variables
public:

protected:
	uint32 m_uiController;
	CCamera* m_pCamera;
	CHUD* m_pHUD;
	bool m_bIsDisabled;
	float32 m_fScoutAnimation;
	float32 m_fScoutTimer;
	float32 m_fAutoAimMax;
private:

}; 

#endif // __IGFEB10_MODULE_HUMANPLAYER_H__

