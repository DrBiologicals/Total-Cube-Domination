// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aistateGetflag.cpp
//  Description :   aistateGetflag.cpp for implementation of aistateGetflag.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../terrain objects/cube.h"
#include "../../terrain objects/flagplate.h"
#include "../../terrain objects/flag.h"
#include "pathfinder.h"

// This Includes
#include "aistateProtectflag.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAIStateProtectFlag::CAIStateProtectFlag()
{
	
}

CAIStateProtectFlag::~CAIStateProtectFlag()
{
	m_pOwner->SetFlagGuard(m_eAllyTeam, false);
}

/*
* Initialises the class instance
*
* @author				Cameron MacIntosh
* @param _pOwner		the owning AIPlayer
* @param _pMove			an address of an instance of the Move substate
* @param _pFlee			an address of an instance of the Flee substate
* @param Attack			an address of an instance of the Attack substate
* @return				if it succeded. Don't use the instance if it returns false.
*/
bool CAIStateProtectFlag::Initialise(CAIPlayer* _pOwner, CAISubstateMove* _pMove, CAISubstateFlee* _pFlee,
		CAISubstateAttack* _pAttack)
{
	if(_pOwner!=0)
	{
		m_pOwner = _pOwner;
		m_pTank = m_pOwner->GetTank();

		m_pMove = _pMove;
		m_pFlee = _pFlee;
		m_pAttack = _pAttack;

		InitGeneral();

		m_pAllyFlag = s_pCube->GetFlag(m_eAllyTeam);
		m_pEnemyFlag = s_pCube->GetFlag(m_eEnemyTeam);
		
		m_pOwner->SetFlagGuard(m_eAllyTeam, true);

		/*
		//set the path to the flag (regardless of position)
		D3DXVECTOR2 _vec2Target(0,0);
		mFlagPos3Last = *m_pAllyFlag->GetPosition();

		CPathfinder::ConvertUnit3DtoTile2D(m_pAllyFlag->GetFace(), mFlagPos3Last, _vec2Target);
		m_pMove->SetTarget(static_cast<int16>(_vec2Target.x),static_cast<int16>(_vec2Target.y),m_pAllyFlag->GetFace());
		*/
		return(true);
	}
	return(false);
}

void
CAIStateProtectFlag::Process(float32 _fDeltaTick)
{
	//TSPT* pFlagSPT = CPathfinder::GetInstance().GetFlagSPT(m_eAllyTeam);
	//m_pMove->Process(_fDeltaTick);
	//if the enemy team's flag is still on it's plate
	if(m_pAllyFlag->IsFlagOnFlagPlate())
	{
		TSPT* pFlagSPT = CPathfinder::GetInstance().GetFlagPlateSPT(m_eAllyTeam);
		float32 fLastCost = 25;
		CTank* pTargetTank = 0;
		CPlayer* pPlayer = 0;
		CTank* pTank = 0;
		int32 iX = 0;
		int32 iY = 0;
		CPlayerManager* pPlayerManager = &CPlayerManager::GetPlayerManagerInstance();
		for(int32 i=0; i<8; ++i)
		{
		pPlayer = pPlayerManager->GetPlayer(i);
			if(pPlayer->GetTeam()==m_eEnemyTeam)
			{
				pTank = pPlayer->GetTank();
				iX = static_cast<int32>(pTank->GetPosition2D().x);
				iY = static_cast<int32>(pTank->GetPosition2D().y);
				float32 fCurrCost = pFlagSPT->aCost[pTank->GetFacePosition()][iY*g_uiSideLength+iX];
				if(fCurrCost<fLastCost)
				{
					pTargetTank = pTank;
				}
			}
		}
		//if an enemy tank is near, attack it.
		if(pTargetTank!=0)
		{
			D3DXVECTOR2 vec2 = pTargetTank->GetPosition2D();
			m_pMove->SetTarget(static_cast<int32>(vec2.x),static_cast<int32>(vec2.y),pTargetTank->GetFacePosition());
			m_pMove->Process(_fDeltaTick);
		}
		else
		{
			m_pMove->Process(_fDeltaTick);
		}
	}
	else
	{
		//pFlagSPT = CPathfinder::GetInstance().GetFlagPlateSPT(m_eAllyTeam);
		ReportStateChange(AI_STATE_RETRIEVEFLAG);
	}
	/*IDEAL
		- doesn't lead enemies to the flag, maybe blocks allies off outside a wider radius
		- may switch to protect flag if desired
	*/

}