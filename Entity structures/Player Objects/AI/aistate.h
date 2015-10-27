// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistate.cpp
//  Description :   delcaration for CAIState
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISTATE_H__
#define __IGFEB10_MODULE_AISTATE_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes
#include "../../entity.h"
#include "../../../defines.h"
#include "aiplayer.h"
#include "aisubstate.h"
#include "aisubstateFlee.h"
#include "aisubstateMove.h"
#include "aisubstateAttack.h"
#include "pathfinder.h"
#include "../../Terrain objects/cube.h"
#include "../playermanager.h"
#include "../../../defines.h"
#include "../tank.h"
#include "aihelper.h"

// Types

// Prototypes
class CAIPlayer;

class CAIState : public CEntity
{
	// Member Functions
public:
	CAIState();
	virtual ~CAIState();
	virtual bool Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack);
	virtual bool InitGeneral();
	void CreateSubStates();

	virtual void Process(float32 _fDeltaTick);
	void ReportStateChange(EAIState _eNewState);

	static void SetCube(CCube* _pCube);

protected:

private:

	// Member Variables
public:

protected:
	CAIPlayer* m_pOwner;
	CTank* m_pTank;

	CAISubstateMove* m_pMove;
	CAISubstateFlee* m_pFlee;
	CAISubstateAttack* m_pAttack;

	ETeam m_eAllyTeam;
	ETeam m_eEnemyTeam;

	static CCube* s_pCube;
private:

}; 

#endif // __IGFEB10_MODULE_AISTATE_H__

