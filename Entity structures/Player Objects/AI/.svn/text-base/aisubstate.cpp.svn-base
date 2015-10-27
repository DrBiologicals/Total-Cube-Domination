// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstate.cpp
//  Description :   aisubstate.cpp for implementation of aisubstate.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "pathfinder.h"
#include "../tank.h"
#include "../playermanager.h"
#include "../humanplayer.h"
#include "../tank.h"
#include "../../terrain objects/wall.h"

// This Includes
#include "aisubstate.h"

// Static Variables
CCube* CAISubstate::s_pCube = 0;

// Static Function Prototypes

// Implementation

CAISubstate::CAISubstate()
: m_pTank(0)
, m_iSPTID(-1)
{

}

CAISubstate::~CAISubstate()
{

}

void
CAISubstate::Process(float32 _fDeltaTick)
{

}

EDirection CAISubstate::GetClosestNode()
{
	TSPT* pSPT = CPathfinder::GetInstance().GetSPT(m_iSPTID);
	EFacePosition eFace = m_pTank->GetFacePosition();
	D3DXVECTOR2 vecPosition = m_pTank->GetPosition2D();

	if(pSPT==0)
	{
		return(DIRECTION_NONE);
	}

	if(eFace==FACE_NONE)
	{
		return(DIRECTION_NONE);
	}
	else if((vecPosition.x<0)||(vecPosition.y<0)||(vecPosition.x>=g_uiSideLength)||(vecPosition.y>=g_uiSideLength))
	{
		return(DIRECTION_NONE);
	}

	float32 fX = vecPosition.x;
	float32 fY = vecPosition.y;
	int8 iX = static_cast<int8>(vecPosition.x);
	int8 iY = static_cast<int8>(vecPosition.y);

	EFacePosition eCurrFace = eFace;
	EDirection chosenDirection = DIRECTION_NONE;
	float32 fCurrentCost = pSPT->aCost[eFace][iY*g_uiSideLength + iX];
	float32 fCost = fCurrentCost;

	std::vector<EDirection> possibleDirections;

	if(iX<=0)
	{
		eCurrFace = CPathfinder::GetFaceToLeft(eFace);
		if(eCurrFace!=FACE_NONE)
		{
			fCurrentCost = pSPT->aCost[eCurrFace][iY*g_uiSideLength + g_uiSideLength-1];
			if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
			{
				fCost = fCurrentCost;
				chosenDirection = DIRECTION_LEFT;
			}
		}
	}
	else
	{
		fCurrentCost = pSPT->aCost[eFace][iY*g_uiSideLength + iX-1];
		if((fCurrentCost!=0.0f)&&((fCurrentCost<fCost)||(fCost==-1)))
		{
			fCost = fCurrentCost;
			possibleDirections.push_back(DIRECTION_LEFT);
		}
	}
	if(iX>=g_uiSideLength-1)
	{
		eCurrFace = CPathfinder::GetFaceToRight(eFace);
		if(eCurrFace!=FACE_NONE)
		{
			fCurrentCost = pSPT->aCost[eCurrFace][iY*g_uiSideLength];
			if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
			{
				fCost = fCurrentCost;
				chosenDirection = DIRECTION_RIGHT;
			}
		}
	}
	else
	{
		fCurrentCost = pSPT->aCost[eFace][iY*g_uiSideLength + iX+1];
		if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
		{
			fCost = fCurrentCost;
			possibleDirections.push_back(DIRECTION_RIGHT);
		}
	}

	if(iY<=0)
	{
		eCurrFace = CPathfinder::GetFaceAbove(eFace);
		if(eCurrFace!=FACE_NONE)
		{
			fCurrentCost = pSPT->aCost[eCurrFace][(g_uiSideLength-1)*g_uiSideLength + iX];
			if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
			{
				fCost = fCurrentCost;
				possibleDirections.push_back(DIRECTION_UP);
				chosenDirection = DIRECTION_UP;
			}
		}
	}
	else
	{
		fCurrentCost = pSPT->aCost[eFace][(iY-1)*g_uiSideLength + iX];
		if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
		{
			fCost = fCurrentCost;
			possibleDirections.push_back(DIRECTION_UP);
		}
	}
	if(iY>=g_uiSideLength-1)
	{
		eCurrFace = CPathfinder::GetFaceBelow(eFace);
		if(eCurrFace!=FACE_NONE)
		{
			fCurrentCost = pSPT->aCost[eCurrFace][iX];
			if((fCurrentCost!=0.0f)&&(fCurrentCost<fCost))
			{
				fCost = fCurrentCost;
				chosenDirection = DIRECTION_DOWN;
			}
		}
	}
	else
	{
		fCurrentCost = pSPT->aCost[eFace][(iY+1)*g_uiSideLength + iX];
		if(fCurrentCost!=0.0f)
		{
			if(fCurrentCost<fCost)
			{
				fCost = fCurrentCost;
				possibleDirections.push_back(DIRECTION_DOWN);
			}
		}
	}

	if(chosenDirection==DIRECTION_NONE)
	{
		CPathfinder& rPathfinder = CPathfinder::GetInstance();
		float32 fCurrCost = rPathfinder.GetWeight(iX,iY,eCurrFace);
		{
			int32 iTotal = static_cast<int32>(possibleDirections.size());
			if(iTotal>0)
			{
				int32 iRandomSelect = static_cast<int32>(RandomFloat() * iTotal);
				chosenDirection = possibleDirections[iRandomSelect];
			}
		}
	}

	return(chosenDirection);
}

//overall code by rigardt, turret rotation by Cameron
void CAISubstate::FireAtEnemy()
{
	//#ifndef _AI_NOSHOOT
	// should probably be placed in substate.cpp, or substateAttack.cpp
	// as this is supposed to only be a container for the current state(s),\
	//  and not make decisions itself.
    D3DXVECTOR3 vec3Distance;
	D3DXVECTOR3 vec3ShootDir;
	D3DXVECTOR3 vec3ShootRight;

    CTank* pTankTarget = 0;
	bool m_bWillShoot = false;

    // check through all tanks that are on the same face as this player.
    for (uint32 ui = 0; ui < 8; ++ui)
    {
	    // get pointer to a tank.
	    CTank* pTank = CPlayerManager::GetPlayerManagerInstance().GetPlayer(ui)->GetTank();

	    // make sure that the tank is not equal to this one.
	    if (m_pTank != CPlayerManager::GetPlayerManagerInstance().GetPlayer(ui)->GetTank() )
	    {
		    if (pTank->GetAlive() &&
			    pTank->GetPowerUp() != POWERUP_INVISIBILITY &&
                pTank->GetTeam() != m_pTank->GetTeam() &&
			    pTank->GetFacePosition() == m_pTank->GetFacePosition() &&
                !m_pTank->HasFlag())
            {
                // the tank found a target and will shoot at it at this point.
		        m_bWillShoot = true;
		        vec3ShootDir = pTank->GetPosition() - m_pTank->GetPosition();

		        if (D3DXVec3Length(&vec3Distance) > D3DXVec3Length(&vec3ShootDir) )
		        {
                    // sets the shoot directions and the target tank.
			        vec3Distance = vec3ShootDir;
                    pTankTarget = pTank;
		        }
			    
            }
	    }
    }

    // transforms the right coords.
    D3DXMATRIX mat;

    D3DXMatrixRotationAxis(&mat, &g_atUpRightDirectionVecs[m_pTank->GetFacePosition()].vec3Up, D3DXToRadian(90) );
    D3DXVec3TransformCoord(&vec3ShootRight, &vec3Distance, &mat);

	//vec3Distance += (vec3ShootRight*((RandomFloat()-0.5f)*0.5f));

    std::vector<CWall*> rvecWalls;

    if (!m_pTank->HasFlag())
    {
        // checks if the target exsists.
        if (pTankTarget)
        {
            std::vector<CWall*> rvecWallsOnFace;

            // declare some base variables.
            float32 fXTarget = pTankTarget->GetPosition2D().x;
            float32 fYTarget = pTankTarget->GetPosition2D().y;
            float32 fXPosition = m_pTank->GetPosition2D().x;
            float32 fYPosition = m_pTank->GetPosition2D().y;
            float32 fXMin = 0.0f;
            float32 fXMax = 0.0f;
            float32 fYMin = 0.0f;
            float32 fYMax = 0.0f;

            // set the x min and max
            if (fXTarget < fXPosition)
            {
                fXMin = fXTarget - 0.5f;
                fXMax = fXPosition + 0.5f;
            }
            else
            {
                fXMax = fXTarget + 0.5f;
                fXMin = fXPosition - 0.5f;
            }
            // set the y min and max
            if (fYTarget < fYPosition)
            {
                fYMin = fYTarget - 0.5f;
                fYMax = fYPosition + 0.5f;
            }
            else
            {
                fYMax = fYTarget + 0.5f;
                fYMin = fYPosition - 0.5f;
            }

            // local variable is destroyed after these braces
            {
                std::vector<CWall*> rvecWalls = CPathfinder::GetInstance().GetCube()->GetWalls();
                for (uint32 ui = 0; ui < rvecWalls.size(); ++ui)
                {
                    // checks the wall is on the same face as the tank.
                    if (rvecWalls[ui]->GetFacePosition() == m_pTank->GetFacePosition() )
                    {
                        // adds the wall in the vector of walls to be referenced.
                        rvecWallsOnFace.push_back(rvecWalls[ui]);
                    }
                }
            }

            // checks through all the walls that are on the same face as the tank.
            for (uint32 ui = 0; ui < rvecWallsOnFace.size(); ++ui)
            {
                // This is the check to see if the walls are inside the square made by the two tanks.
                if (rvecWallsOnFace[ui]->GetX() >= fXMin && rvecWallsOnFace[ui]->GetX() <= fXMax &&
                    rvecWallsOnFace[ui]->GetY() >= fYMin && rvecWallsOnFace[ui]->GetY() <= fYMax)
                {
                    // adds the wall into the a new vector of walls.
                    rvecWalls.push_back(rvecWallsOnFace[ui]);
                }
            }
        }

        // checks if the vector is empty.
        if (!rvecWalls.empty() )
        {
            //for (uint32 ui = 0; ui < rvecWalls.size(); ++ui)
            //{
            //    // checks if the shoot direction ray intersects with any of the wall  
            //    // that are in the vector.
            //    if (TRUE == D3DXBoxBoundProbe(&rvecWalls[ui]->GetBoundingBox().m_vec3Min, 
            //                                    &rvecWalls[ui]->GetBoundingBox().m_vec3Max, 
            //                                    &m_pTank->GetPosition(), &vec3ShootDir) )
            //    {
                    // if even one wall intersects the tank will not shoot.
                    m_bWillShoot = false;
                    //break;
                //}
            //}
		}

	    // actually shoot now
	    if (m_bWillShoot == true)
	    {
			D3DXVec3Normalize(&vec3ShootDir, &vec3Distance);
			D3DXVec3Normalize(&vec3ShootRight, &vec3ShootRight);
			//m_pTank->SetShootRightAndDir(vec3ShootDir, vec3ShootRight);

			//rotates the turret - Cameron
			D3DXVECTOR2 vec2;
			EFacePosition eFace = m_pTank->GetFacePosition();
			vec2.x = D3DXVec3Dot(&vec3ShootDir, &g_atUpRightDirectionVecs[eFace].vec3Right);
			vec2.y = D3DXVec3Dot(&vec3ShootDir, &g_atUpRightDirectionVecs[eFace].vec3Direction);
			m_pTank->RotateTurret(vec2.x, vec2.y, 0.5f);
			//

            int32 iRandomChanceValue = static_cast<int32>(RandomFloat() * 300);
            if (m_pTank->GetEMPCount() == 0)
            {
                m_pTank->ShootPlasma();
            }
            else if (iRandomChanceValue >= 1)
            {
		        m_pTank->ShootPlasma();
            }
            else if (D3DXVec3LengthSq(&vec3Distance) <= 18.0f)
            {
                m_pTank->ShootEMP();
            }
            else
            {
                m_pTank->ShootPlasma();
            }
	    }
    }

	//#endif //_AI_NOSHOOT
}

void CAISubstate::SetCube(CCube* _pCube)
{
	s_pCube = _pCube;
}