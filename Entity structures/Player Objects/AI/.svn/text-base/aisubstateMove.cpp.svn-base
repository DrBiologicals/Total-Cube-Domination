// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstateMove.cpp
//  Description :   aisubstateMove.cpp for implementation of aisubstateMove.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes
#include <sstream>

// Local Includes
#include "pathfinder.h"
#include "../tank.h"
#include "../../../defines.h"
#include "../../../Engine/Totalcubedomination.h"

// This Includes
#include "aisubstateMove.h"

// Static Variables
CTank* CAISubstateMove::s_pTank = 0;
// Static Function Prototypes

// Implementation

CAISubstateMove::CAISubstateMove()
: m_eTransDir(DIRECTION_NONE)
, m_eWanderDir(DIRECTION_NONE)
{
	
}

CAISubstateMove::~CAISubstateMove()
{

}

bool CAISubstateMove::Initialise(CTank* _pTank)
{
	m_pTank = _pTank;
	if(s_pTank==0)
	{
		s_pTank = _pTank;
	}
	return(true);
}

/*
* this processes the state
* @author		Cameron MacIntosh
* @param		
*/

void CAISubstateMove::Process(float32 _fDeltaTick)
{
	//move towards a target (target probably isn't enemy)

	//check pathfinder to return closest node
	//EFacePosition eFace = m_pTank->GetFacePosition();
	const D3DXVECTOR2& vec2Pos = m_pTank->GetPosition2D();
	int32 iOldX = static_cast<int32>(vec2Pos.x);
	int32 iOldY = static_cast<int32>(vec2Pos.y);

	EDirection eMoveDir = DIRECTION_NONE;

	if(m_iSPTID!=-1)
	{
		eMoveDir = GetClosestNode();
		if(eMoveDir!=DIRECTION_NONE)
		{
			//m_pTank->Move(_fDeltaTick, eMoveDir);
			m_eTransDir = eMoveDir;
		}
		else
		{
			//forces the tank onto the next side during a transition
			eMoveDir = m_eTransDir;
		}
		m_eWanderDir = DIRECTION_NONE;
	}
	else
	{
		eMoveDir = Wander();
	}

	if(DIRECTION_NONE!=eMoveDir)
	{
		m_pTank->Move(_fDeltaTick, eMoveDir);
	}
	else
	{
		
	}

	#ifdef _DEBUG_PATHFINDER
	if(m_pTank==s_pTank)
	{
		/*std::ostringstream outStream;
		D3DXVECTOR2 vec3Pos = m_pTank->GetPosition2D();
		outStream<<"x: "<<vec3Pos.x<<", y: "<<vec3Pos.y<<" face: "<<m_pTank->GetFacePosition()<<", Direction: "<<eMoveDir;
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);*/
	}
	#endif // _DEBUG_PATHFINDER

	const D3DXVECTOR2& vecNewPos = m_pTank->GetPosition2D();
	int32 iX = static_cast<int32>(vec2Pos.x);
	int32 iY = static_cast<int32>(vec2Pos.y);

	//if the tank has moved to another node
	if((iOldX!=iX)||
		(iOldY!=iY))
	{
		CPathfinder::GetInstance().AddWeightMod(iX,iY,1.2f);
	}

	FireAtEnemy();

	/*m_pTank->ShootPlasma();
	m_pTank->RotateTurret(fX, fY, _fDeltaTick)*/
}

void CAISubstateMove::SetTarget(int32 _iX, int32 _iY, EFacePosition _eFace)
{
	CPathfinder::GetInstance().CreateSPT(m_iSPTID, _iX, _iY, _eFace);
}

EDirection CAISubstateMove::WanderAround()
{
	CPathfinder& rPathfinder = CPathfinder::GetInstance();
	const D3DXVECTOR2& vec2Pos = m_pTank->GetPosition2D();
	const EFacePosition eFace = m_pTank->GetFacePosition();
	TSPT* pSPT = CPathfinder::GetInstance().GetSPT(m_iSPTID);

	EDirection chosenDirection = DIRECTION_NONE;

	float32 fX = vec2Pos.x;
	float32 fY = vec2Pos.y;
	int32 iX = static_cast<int32>(fX);
	int32 iY = static_cast<int32>(fY);
	fX -= static_cast<float32>(iX);
	fY -= static_cast<float32>(iY);
	CPathfinder::ConvertSidePosToPlane(eFace,iX,iY);
	fX += static_cast<float32>(iX);
	fY += static_cast<float32>(iY);
	
	float32 fCurrCost = 0.0f;
	float32 fThisCost = 0.0f;
	int32 iCurrTile = -1;

	//&&(m_vSPT[_iSPTID]->aCost[eCurrFace][(iCurrY-1)*g_uiSideLength + iCurrX]))

	if(m_eWanderDir==DIRECTION_NONE)
	{
		fThisCost = rPathfinder.GetWeight(iX,iY-1);
		//D3DXVECTOR2 vec2 = 
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_UP;
		}
		fThisCost = rPathfinder.GetWeight(iX,iY+1);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_DOWN;
		}
		fThisCost = rPathfinder.GetWeight(iX-1,iY);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_LEFT;
		}
		fThisCost = rPathfinder.GetWeight(iX+1,iY);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_RIGHT;
		}
		if(chosenDirection!=DIRECTION_NONE)
		{
			m_eWanderDir = chosenDirection;
		}
	}

	return (chosenDirection);
}

EDirection CAISubstateMove::Wander()
{
	CPathfinder& rPathfinder = CPathfinder::GetInstance();
	const D3DXVECTOR2& vec2Pos = m_pTank->GetPosition2D();
	const EFacePosition eFace = m_pTank->GetFacePosition();

	EDirection chosenDirection = DIRECTION_NONE;

	float32 fX = vec2Pos.x;
	float32 fY = vec2Pos.y;
	int32 iX = static_cast<int32>(fX);
	int32 iY = static_cast<int32>(fY);
	fX -= static_cast<float32>(iX);
	fY -= static_cast<float32>(iY);
	CPathfinder::ConvertSidePosToPlane(eFace,iX,iY);
	fX += static_cast<float32>(iX);
	fY += static_cast<float32>(iY);
	
	float32 fCurrCost = 0.0f;
	float32 fThisCost = 0.0f;
	int32 iCurrTile = -1;

	if(m_eWanderDir==DIRECTION_NONE)
	{
		fThisCost = rPathfinder.GetWeight(iX,iY-1);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_UP;
		}
		fThisCost = rPathfinder.GetWeight(iX,iY+1);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_DOWN;
		}
		fThisCost = rPathfinder.GetWeight(iX-1,iY);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_LEFT;
		}
		fThisCost = rPathfinder.GetWeight(iX+1,iY);
		if((fThisCost!=0.0f)&&((fCurrCost==0.0f)||(fThisCost<fCurrCost)))
		{
			fCurrCost = fThisCost;
			chosenDirection = DIRECTION_RIGHT;
		}
		if(chosenDirection!=DIRECTION_NONE)
		{
			m_eWanderDir = chosenDirection;
		}
	}

	return (chosenDirection);
}