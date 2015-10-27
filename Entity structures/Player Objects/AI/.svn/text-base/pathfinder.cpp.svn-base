// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   pathfinder.cpp
//  Description :   pathfinder.cppfor implementation of pathfinder.h
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <cmath>
#include <string>
#include <sstream>

// Local Includes
#include "../../../engine/game/gamestate.h"
#include "../../Terrain objects/cube.h"
#include "../../Terrain objects/wall.h"
#include "../../Terrain objects/ammo.h"
#include "../../Terrain objects/flamegrate.h"
#include "../../Terrain objects/tile.h"
#include "../../Terrain objects/Tower/tower.h"
#include "../../Terrain objects/breakablebarrier.h"
#include "../../Terrain objects/faultymagplate.h"
#include "../../Terrain objects/flag.h"
#include "../../Terrain objects/flagplate.h"
#ifdef _DEBUG
#include "../../../Engine/Totalcubedomination.h"
#endif // _DEBUG
#include "aihelper.h"

// This Includes
#include "pathfinder.h"

// Static Variables
CPathfinder* CPathfinder::s_pInstance = 0;

// Static Function Prototypes

// Implementation
#define indexSide(y,x) (y*g_uiSideLength + x)
#define indexSideF(y,x) (static_cast<int16>(y)*g_uiSideLength + static_cast<int16>(x))
#define rindexYSide(node) (node/g_uiSideLength)
#define rindexXSide(node) (node-(node/g_uiSideLength*g_uiSideLength))

CPathfinder::CPathfinder()
: bInit(false)
, m_uiGreenFlagSPTID(BAD_ID)
, m_uiPurpleFlagSPTID(BAD_ID)
, m_uiGreenFlagPlateSPTID(BAD_ID)
, m_uiPurpleFlagPlateSPTID(BAD_ID)
, m_fMagWeight(1.0f)
{
	//m_pGreenFlagSPT = CreateSPT(flagtilePosition, 0);
	//m_pPurpleFlagSPT = CreateSPT(flagtilePosition, 0);
	//memset(&m_fWeight, float32(0.0f), sizeof(m_fWeight));
	//memset(&m_fWeightMod, float32(0.0f), sizeof(m_fWeightMod));
	#ifdef _DEBUG_PATHFINDER
	CTotalCubeDomination::GetInstance().LogMessage("pathfinder created", LOG_MESSAGE_PATHS);
	#endif // _DEBUG_PATHFINDER
}

CPathfinder::~CPathfinder()
{
	uint32 uiLength = static_cast<uint32>(m_vSPT.size());
	#ifdef _DEBUG_PATHFINDER
	std::ostringstream sstream;
	sstream<<"total paths left for deconstruct is "<<uiLength;
	CTotalCubeDomination::GetInstance().LogMessage(sstream.str().c_str(), LOG_MESSAGE_PATHS);
	#endif // _DEBUG_PATHFINDER
	while(uiLength>0)
	{
		delete m_vSPT[uiLength-1];
		m_vSPT.pop_back();
		uiLength = static_cast<uint32>(m_vSPT.size());
	}
}

bool
CPathfinder::Initialise(CCube* _pCube)
{
	m_pCube = _pCube;

	for(uint32 ui=0; ui<6; ++ui)
	{
		for(uint32 ui2=0; ui2<g_uiSideNodeTotal; ++ui2)
		{
			m_vecSideType[ui][ui2] = 0; 
		}
	}
	for(uint32 ui=0; ui<6; ++ui)
	{
		m_apSideTrav[ui] = &m_pCube->GetPassabilityArray(static_cast<EFacePosition>(ui));
		#ifdef _DEBUG_PATHFINDER
			//LogTravMap(static_cast<EFacePosition>(ui));
		#endif //_DEBUG_PATHFINDER
	}

	SetTileArrays();

	std::vector<CWall*> vecWall = m_pCube->GetWalls();
	uint8 uiTileType = 1;
	//side length (in units) minus half the tile size (as tiles are centered)
	//float32 fUnitLengthHalf = static_cast<float32>(g_uiSideLength * g_uiTileSize)/2;
	//float32 fModifier = fUnitLengthHalf - (static_cast<float32>(g_uiTileSize)/2);
	for(uint32 ui=0; ui<static_cast<uint32>(vecWall.size()); ++ui)
	{
		//EFacePosition currFace = vecWall[ui]->GetFacePosition();
		
		m_vecSideType[vecWall[ui]->GetFacePosition()][indexSide(vecWall[ui]->GetY(),vecWall[ui]->GetX())] = uiTileType;
		//GetX()&GetY() returns int32 in tile units, from top-left corner (1 = 3 normal units)
	}

	CFlag* pFlag = m_pCube->GetFlag(TEAM_GREEN);
	D3DXVECTOR2 vec2Pos;
	ConvertUnit3DtoTile2D(pFlag->GetFace(),pFlag->GetPosition(),vec2Pos);
	CreateSPT(m_uiGreenFlagSPTID,static_cast<int32>(vec2Pos.x),static_cast<int32>(vec2Pos.y),pFlag->GetFace());
	pFlag = m_pCube->GetFlag(TEAM_PURPLE);
	ConvertUnit3DtoTile2D(pFlag->GetFace(),pFlag->GetPosition(),vec2Pos);
	CreateSPT(m_uiPurpleFlagSPTID,static_cast<int32>(vec2Pos.x),static_cast<int32>(vec2Pos.y),pFlag->GetFace());

	CFlagPlate* pFlagPlate = m_pCube->GetFlagPlate(TEAM_GREEN);
	CreateSPT(m_uiGreenFlagPlateSPTID,pFlagPlate->GetX(),pFlagPlate->GetY(),pFlagPlate->GetFacePosition());
	pFlagPlate = m_pCube->GetFlagPlate(TEAM_PURPLE);
	CreateSPT(m_uiPurpleFlagPlateSPTID,pFlagPlate->GetX(),pFlagPlate->GetY(),pFlagPlate->GetFacePosition());

	#ifdef _DEBUG_PATHFINDER
	std::ostringstream outStream;
	
	CTotalCubeDomination::GetInstance().LogMessage("pathfinder initialised", LOG_MESSAGE_INIT);
	#endif // _DEBUG_PATHFINDER

	bInit = true;

	return true;
}


void
CPathfinder::Process(float32 _fDeltaTick)
{
	//removes, with time, the modified weight values.
	float32 fAmtReg = 0.1f*_fDeltaTick;
	float32 fAmtOrig = 0.0f;
	float32* pfWeight = 0;
	for(int32 i=0; i<g_uiTileHeight; ++i)
	{
		for(int32 j=0; j<g_uiTileWidth; ++j)
		{
			pfWeight = &m_fWeightMod[i][j];
			fAmtOrig = (*pfWeight);
			if((*pfWeight)>0.0f)
			{
				(*pfWeight) -= fAmtReg;
				if((*pfWeight)<0.0f)
				{
					(*pfWeight) = 0.0f;
					(*pfWeight) = RandomFloat();
				}
			}
			else if((*pfWeight)<0.0f)
			{
				(*pfWeight) += fAmtReg;
				if((*pfWeight)>0.0f)
				{
					(*pfWeight) = 0.0f;
					(*pfWeight) = RandomFloat();
				}
			}
			else if(fAmtOrig==0)
			{
				(*pfWeight) = RandomFloat();
			}
			m_fWeight[i][j] += (*pfWeight)-fAmtOrig;
		}
	}
}

TSPT* CPathfinder::GetSPT(int32 _iSPTID)
{
	if(_iSPTID<static_cast<int32>(m_vSPT.size()))
	{
		return(m_vSPT[_iSPTID]);
	}
	else
	{
		return(0);
	}
}


/*
* Creates a path by using A* with the Manhattan Distance heuristic
* @author			Cameron MacIntosh
* @param _vtPath	a reference to the output
* @param _tOrigin	the origin node (where the path moves from)
* @param _tTarget	the rate of change (1 is linear)
* @param _fRange	the maximum movement cost it will calculate to
* @return bool		returns if the path creation was successful
*/
bool CPathfinder::CreatePathAStar(pathVector& _vtPath, const TNode& _tOrigin, const TNode& _tTarget, float32 _fRange)
{
	/*
	//for debugging
	std::ostringstream outStream;

	//clear old path information
	_vtPath.erase(_vtPath.begin(),_vtPath.end()-1);
	
	//early exits
	if(m_apSideTrav[_tTarget.eFace]->m_abArray[_tTarget.iY][_tTarget.iX])
	{
		//the target is not traversable, so no path can be made.
		return false;
	}
	else if((_tOrigin.eFace==_tTarget.eFace)&&(_tOrigin.iX==_tTarget.iX)&&(_tOrigin.iY==_tTarget.iY))
	{
		//target is found, but path is empty since no movement is needed.
		return true;
	}

	//create variables needed to find the path
	TNodeCosts* pNodeCost = &m_tCostMap[_tOrigin.eFace][_tOrigin.iY][_tOrigin.iX];
	std::vector<TNodeCosts*> vtOpen;	//points to TNodeCosts, does not create any
	std::vector<TNodeCosts*> vtClosed;
	TNodeCosts* pCurrent = 0;
	//add the origin node to the open list
	vtOpen.push_back(pNodeCost);
	uint32 uiOpenLength = 1;
	//set the origin's costs to 0
	pNodeCost->fGCost = 0;
	pNodeCost->fHCost = 0;
	pNodeCost->fFCost = 0;

	while(0<uiOpenLength)
	{
		//find the lowest cost on the open list. Set it to the current node.
		pCurrent = vtOpen[uiOpenLength-1];	//sorted largest->smallest
		vtOpen.pop_back();
		//add the current node to the closed list
		vtClosed.push_back(pCurrent);

		EFacePosition eCurrFace = pCurrent->eFace;
		int32 iCurrX = pCurrent->iX;
		int32 iCurrY = pCurrent->iY;
		//check the four neighbor nodes
		EFacePosition eThisFace = eCurrFace;
		int32 iThisX = -1;
		int32 iThisY = -1;
		//if there is a walkable area to the left
		if(IsConnecting(DIRECTION_LEFT,D3DXVECTOR2(static_cast<float32>(iCurrX),static_cast<float32>(iCurrY)),eCurrFace))
		{
			if(iThisX<1)
			{
				eThisFace = GetFaceToLeft(eThisFace);
				iThisX = g_uiSideLength - 1;
			}
			else
			{
				eThisFace = eCurrFace;
				iThisX = iCurrX - 1;
			}
			//check if this node is on the closed list
			ENodeStatus& eNodeStatus = m_eStatusMap[eThisFace][iCurrY][iThisX];
			switch(eNodeStatus)
			{
				case NODE_UNUSED:
					//if this node is traversable
					if(m_apSideTrav[eThisFace]->m_abArray[iCurrY][iThisX])
					{
						vtOpen.push_back(&m_tCostMap[_tOrigin.eFace][iCurrY][iThisX]);
						eNodeStatus = NODE_OPEN;
						vtOpen[uiOpenLength]->iParentX = pCurrent->iX;
						vtOpen[uiOpenLength]->iParentY = pCurrent->iY;
						//add values to the node (G,H,F)
						vtOpen[uiOpenLength]->fGCost = pCurrent->fGCost + 1.0f; //alter this value for different tile types
						vtOpen[uiOpenLength]->fHCost = static_cast<float32>(abs(iThisX-_tTarget.iX) + abs(iThisY-_tTarget.iY));
						vtOpen[uiOpenLength]->fFCost = vtOpen[uiOpenLength]->fGCost + vtOpen[uiOpenLength]->fHCost;
						++uiOpenLength;
						//remember to sort this
					}
					else
					{
						//the node is not traversable, so close it
						eNodeStatus = NODE_CLOSED;
					}
					break;
				case NODE_OPEN:
					//check to see if new f value is less than recorded value
					float32 newG = pCurrent->fGCost + 1.0f;
					if(newG>m_tCostMap[_tOrigin.eFace][iCurrY][iThisX].fGCost)
					{
						vtOpen[uiOpenLength]->iParentX = pCurrent->iX;
						vtOpen[uiOpenLength]->iParentY = pCurrent->iY;
						vtOpen[uiOpenLength]->fGCost = newG;
						vtOpen[uiOpenLength]->fHCost = static_cast<float32>(abs(iThisX-_tTarget.iX) + abs(iCurrY-_tTarget.iY));
						vtOpen[uiOpenLength]->fFCost = vtOpen[uiOpenLength]->fGCost + vtOpen[uiOpenLength]->fHCost;
					}
					break;
			}
		}
		else if(IsConnecting(DIRECTION_RIGHT,D3DXVECTOR2(pCurrent->iX,pCurrent->iY),eCurrFace))
		{
			
		}

		//pNodeCost = &m_tCostMap[_tOrigin.eFace][_tOrigin.iY][_tOrigin.iX];

		uiOpenLength = static_cast<uint32>(vtOpen.size());
		//sort the open list so the from largest(0) to smallest (uiOpenLength-1)
		pCurrent = vtOpen[uiOpenLength-1];
		float32 fLastFVal = pCurrent->fFCost;
		for(uint32 i=uiOpenLength-2; i>=0; --i)
		{
			//if the fCost of this node is more than the new node,
			if(fLastFVal<vtOpen[i]->fFCost)
			{
				//move the new node to the position above it
				vtOpen.pop_back();
				vtOpen.insert(vtOpen.begin()+i+1,pCurrent);
			}
		}
	}
	
	//if path has been created
	if(true)
	{
#ifdef _DEBUG_PATHFINDER
		outStream<<"CreatePath() succeeded";
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
#endif //_DEBUG_PATHFINDER
		return(true);
	}

	//outStream<<"CreatePathAStar() failed!";
	//CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	*/
	return(false);
}
/**************
^above needs:
	two arrays which store if a node is open/closed/unadded.
**************/

/*
* Returns the SPT (shortest path tree) to a flag
* @author			Cameron Macintosh
* @param _eTeam		which flag's SPT to return
* @return			returns the SPT of the flag
*/
TSPT* CPathfinder::GetFlagSPT(ETeam _eTeam)
{
	if(_eTeam==TEAM_GREEN)
	{
		return(GetSPT(m_uiGreenFlagSPTID));
	}
	else
	{
		return(GetSPT(m_uiPurpleFlagSPTID));
	}
}

/*
* Returns the SPT to a flag plate
*/
TSPT* CPathfinder::GetFlagPlateSPT(ETeam _eTeam)
{
	if(_eTeam==TEAM_GREEN)
	{
		return(GetSPT(m_uiGreenFlagPlateSPTID));
	}
	else
	{
		return(GetSPT(m_uiPurpleFlagPlateSPTID));
	}
}

/*
* Creates a path from a target node
* @author			Cameron MacIntosh
* @param _target	the position of the target (on the face/ the entire cube as a 2D map?)
* @param _eFace		the face the node is on
* @param _range		the distance that the SPT will check for
* @param _dest		a pointer which holds access to the ID of the SPT, which will be output.
* @return bool		returns if the pathfinding succeeded (not if reached target).
*/
bool CPathfinder::CreateSPT(int32& _iSPTID, int32 _iTargetX, int32 _iTargetY, EFacePosition _eFace, int32 _fRange)
{
	std::ostringstream outStream;

	if((_iTargetX<0)||(_iTargetX>=15)||(_iTargetY<0)||(_iTargetY>=15)||(FACE_NONE==_eFace))
	{
		//CTotalCubeDomination::GetInstance().LogMessage("CreateSPT to target node on grid failed",LOG_MESSAGE_PATHS);
		return false;
	}

	uint32 uiCurrNode = indexSide(_iTargetY,_iTargetY);

	if(_iSPTID<0)
	{
		_iSPTID = static_cast<int32>(m_vSPT.size());
		m_vSPT.push_back(new TSPT);
	}
	
	for(uint32 ui=0; ui<6; ++ui)
	{
		//a val of 256 equates to float32's 0. (for this compiler/system). a bit hacky.
		memset(m_vSPT[_iSPTID]->aCost[ui], 256, sizeof(4)*g_uiSideNodeTotal);
	}
	
	float32 tileCost = 0.0f;
	std::vector<TNodeHelper> vecpNodes;
	int32 iNodeVecLast = 0;

	//if the target tile is traversable
	if(m_apSideTrav[_eFace]->m_abArray[_iTargetY][_iTargetX])
	{
		tileCost = 1.0f;
		m_vSPT[_iSPTID]->aCost[_eFace][indexSide(_iTargetY,_iTargetX)] = tileCost;
		vecpNodes.push_back(TNodeHelper());
		vecpNodes[iNodeVecLast].eFace = _eFace;
		vecpNodes[iNodeVecLast].iTile = indexSide(_iTargetY, _iTargetX);
		iNodeVecLast++;
	}
	EFacePosition eCurrFace = FACE_NONE;
	uiCurrNode = BAD_ID;
	int32 iCurrX = -1;
	int32 iCurrY = -1;
	float32 fCurrVal = 0;
	float32 fTileVal = 0;
	int32 nextNode = -1;
	EFacePosition eNextFace = FACE_NONE;

	float32 fWeight = 0.0f;
	int32 iX, iY = 0;
	EDirection eTileDir;

	while(0<static_cast<uint32>(vecpNodes.size()))
	{
		//check to see if the tile to the right is traversable, if so, set its value, and
		// add to vecpNodes.
		eCurrFace = vecpNodes[0].eFace;
		uiCurrNode = vecpNodes[0].iTile;
		iCurrX = rindexXSide(uiCurrNode);
		iCurrY = rindexYSide(uiCurrNode);
		fCurrVal = m_vSPT[_iSPTID]->aCost[eCurrFace][iCurrY*g_uiSideLength + iCurrX];

		if((iCurrX==14)&&(iCurrY==14)&&(eCurrFace==FACE_LEFT))
		{
			iX = iCurrX;
			iY = iCurrY;
			ConvertSidePosToPlane(eCurrFace, iX, iY);
			m_vSPT[_iSPTID]->aCost[eCurrFace][iCurrY*g_uiSideLength + iCurrX] += m_fWeight[iY][iX];
			fCurrVal = m_vSPT[_iSPTID]->aCost[eCurrFace][iCurrY*g_uiSideLength + iCurrX];
		}

		if(iCurrX>0)
		{
			if(m_apSideTrav[eCurrFace]->m_abArray[iCurrY][iCurrX-1])
			{
				iX = iCurrX-1;
				iY = iCurrY;
				ConvertSidePosToPlane(eCurrFace, iX, iY);
				nextNode = iCurrY*g_uiSideLength + iCurrX-1;//indexSide(currY,currX-1);
				fTileVal = m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_RIGHT==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_LEFT==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].eFace = eCurrFace;
					vecpNodes[iNodeVecLast].iTile = nextNode;
					iNodeVecLast++;
				}
			}
		}
		else
		{
			eNextFace = GetFaceToLeft(eCurrFace);			
			if((FACE_NONE!=eNextFace)&&(m_apSideTrav[eNextFace]->m_abArray[iCurrY][g_uiSideLength-1]))
			{
				iX = g_uiSideLength-1;
				iY = iCurrY;
				ConvertSidePosToPlane(eNextFace, iX, iY);
				nextNode = iCurrY*g_uiSideLength + (g_uiSideLength-1);
				fTileVal = m_vSPT[_iSPTID]->aCost[eNextFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_RIGHT==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_LEFT==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eNextFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eNextFace;
					iNodeVecLast++;
				}
			}
		}
		if(iCurrX<g_uiSideLength-1)
		{
			if(m_apSideTrav[eCurrFace]->m_abArray[iCurrY][iCurrX+1])
			{
				iX = iCurrX+1;
				iY = iCurrY;
				ConvertSidePosToPlane(eCurrFace, iX, iY);
				nextNode = iCurrY*g_uiSideLength + iCurrX+1;
				fTileVal = m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_LEFT==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_RIGHT==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eCurrFace;
					iNodeVecLast++;
				}
			}
		}
		else
		{
			eNextFace = GetFaceToRight(eCurrFace);
			if((FACE_NONE!=eNextFace)&&(m_apSideTrav[eNextFace]->m_abArray[iCurrY][0]))
			{
				iX = 0;
				iY = iCurrY;
				ConvertSidePosToPlane(eNextFace, iX, iY);
				nextNode = iCurrY*g_uiSideLength + (0);
				fTileVal = m_vSPT[_iSPTID]->aCost[eNextFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_LEFT==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_RIGHT==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eNextFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eNextFace;
					iNodeVecLast++;
				}
			}
		}
		if(iCurrY>0)
		{
			if(m_apSideTrav[eCurrFace]->m_abArray[iCurrY-1][iCurrX])
			{
				iX = iCurrX;
				iY = iCurrY-1;
				ConvertSidePosToPlane(eCurrFace, iX, iY);
				nextNode = (iCurrY-1)*g_uiSideLength + iCurrX;//indexSide(currY-1,currX);
				fTileVal = m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_DOWN==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_UP==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eCurrFace;
					iNodeVecLast++;
				}
			}
		}
		else
		{
			eNextFace = GetFaceAbove(eCurrFace);			
			if((FACE_NONE!=eNextFace)&&(m_apSideTrav[eNextFace]->m_abArray[g_uiSideLength-1][iCurrX]))
			{
				iX = iCurrX;
				iY = g_uiSideLength-1;
				ConvertSidePosToPlane(eNextFace, iX, iY);
				nextNode = (g_uiSideLength-1)*g_uiSideLength + iCurrX;
				fTileVal = m_vSPT[_iSPTID]->aCost[eNextFace][nextNode];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_DOWN==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_UP==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eNextFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eNextFace;
					iNodeVecLast++;
				}
			}
		}
		if(iCurrY<g_uiSideLength-1)
		{
			iX = iCurrX;
			iY = iCurrY+1;
			ConvertSidePosToPlane(eCurrFace, iX, iY);
			nextNode = (iCurrY+1)*g_uiSideLength + iCurrX;//indexSide(currY+1,currX);
			fTileVal = m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode];
			tileCost = fCurrVal+m_fWeight[iY][iX];
			if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_UP==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_DOWN==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
			if((fTileVal==0)||(fTileVal>tileCost))
			{
				if(m_apSideTrav[eCurrFace]->m_abArray[iCurrY+1][iCurrX])
				{
					m_vSPT[_iSPTID]->aCost[eCurrFace][nextNode] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = nextNode;
					vecpNodes[iNodeVecLast].eFace = eCurrFace;
					iNodeVecLast++;
				}
			}
		}
		else
		{
			eNextFace = GetFaceBelow(eCurrFace);			
			if((FACE_NONE!=eNextFace)&&(m_apSideTrav[eNextFace]->m_abArray[0][iCurrX]))
			{
				iX = iCurrX;
				iY = 0;
				ConvertSidePosToPlane(eNextFace, iX, iY);
				nextNode = iCurrX;
				fTileVal = m_vSPT[_iSPTID]->aCost[eNextFace][iCurrX];
				tileCost = fCurrVal+m_fWeight[iY][iX];
				if(TILE_MAG==m_eTileType[iY][iX])
				{
					eTileDir = dynamic_cast<CFaultyMagPlate*>(m_pTile[iY][iX])->GetDirection();
					if(DIRECTION_UP==eTileDir)
					{
						tileCost -= m_fMagWeight;
					}
					else if(DIRECTION_DOWN==eTileDir)
					{
						tileCost += m_fMagWeight;
					}
				}
				if((fTileVal==0)||(fTileVal>tileCost))
				{
					m_vSPT[_iSPTID]->aCost[eNextFace][iCurrX] = tileCost;
					vecpNodes.push_back(TNodeHelper());
					vecpNodes[iNodeVecLast].iTile = iCurrX;
					vecpNodes[iNodeVecLast].eFace = eNextFace;
					iNodeVecLast++;
				}
			}
		}

		//delete vecpNodes[0];
		vecpNodes.erase(vecpNodes.begin());//,vecpNodes.end());
		--iNodeVecLast;
	}
	
	#ifdef _DEBUG_PATHFINDER
	if(_iSPTID==3){
		for(uint32 ui=0; ui<6; ++ui)
		{
			//LogSPT(2,static_cast<EFacePosition>(ui));
		}
	}
	#endif //_DEBUG_PATHFINDER

	return true;

	/*//LogSPT(0);

	#ifdef _DEBUG_PATHFINDER
		outStream<<"CreateSPT("<<_iTargetX<<", "<<_iTargetY<<", "<<_eFace<<", "<<_fRange<<") failed";
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	#endif //_DEBUG_PATHFINDER

	return false;*/
}

/*
* fill m_eTileType and m_pTile arrays, based on the position of each tile on the cube
*
* @author		Cameron MacIntosh
*/
void CPathfinder::SetTileArrays()
{
	//set default values
	for(int32 i=0; i<g_uiTileHeight; ++i)
	{
		for(int32 j=0; j<g_uiTileWidth; ++j)
		{
			m_pTile[i][j] = 0;
			m_fWeight[i][j] = 0.0f;
			m_fWeightMod[i][j] = 0.0f;
		}
	}

	//set tile type of all side tiles to the default value (TILE_NORMAL), and all non-sides to TILE_NONE
	int32 iY, iX = 0;
	for(uint32 i=0; i<g_uiSideLength; ++i)
	{
		for(uint32 j=0; j<g_uiSideLength; ++j)
		{
			m_eTileType[i][j+15] = TILE_NORMAL;		//FACE_TOP
			m_fWeight[i][j+15] = 1.0f;
			m_eTileType[i+30][j+45] = TILE_NORMAL;	//FACE_BOTTOM
			m_fWeight[i+30][j+45] = 1.0f;
			m_eTileType[i+15][j+15] = TILE_NORMAL;	//FACE_FRONT
			m_fWeight[i+15][j+15] = 1.0f;
			m_eTileType[i+15][j+45] = TILE_NORMAL;	//FACE_BACK
			m_fWeight[i+15][j+45] = 1.0f;
			m_eTileType[i+15][j] = TILE_NORMAL;		//FACE_LEFT
			m_fWeight[i+15][j] = 1.0f;
			m_eTileType[i+15][j+30] = TILE_NORMAL;	//FACE_RIGHT
			m_fWeight[i+15][j+30] = 1.0f;
			//null faces
			m_eTileType[i][j] = TILE_NONE;
			m_eTileType[i][j+30] = TILE_NONE;
			m_eTileType[i][j+45] = TILE_NONE;
			m_eTileType[i+30][j] = TILE_NONE;
			m_eTileType[i+30][j+15] = TILE_NONE;
			m_eTileType[i+30][j+30] = TILE_NONE;
		}
	}
	
	//fill m_eTileType with the type of each tile, and m_pTile with a pointer to each tile at their specified
	// positions.
	EFacePosition eFace = FACE_NONE;
	//TILE_WALL
	std::vector<CWall*>& rvecWall = m_pCube->GetWalls();
	CWall* pWall = 0;
	for (uint32 i = 0; i < rvecWall.size(); ++i)
	{
		pWall = rvecWall[i];
		eFace = pWall->GetFacePosition();
		iX = pWall->GetX();
		iY = pWall->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_WALL;
		m_pTile[iY][iX] = pWall;
		m_fWeight[iY][iX] = 0.0f;
	}
	//TILE_TOWER
	std::vector<CTower*>& rvecTower = m_pCube->GetTowers();
	CTower* pTower = 0;
	for (uint32 i = 0; i < rvecTower.size(); ++i)
	{
		pTower = rvecTower[i];
		eFace = pTower->GetFacePosition();
		iX = pTower->GetX();
		iY = pTower->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_TOWER;
		m_pTile[iY][iX] = pTower;
		m_fWeight[iY][iX] = 0.0f;
	}
	//TILE_BB
	std::vector<CBreakableBarrier*>& rvecBarrier = m_pCube->GetBreakableBarrier();
	CBreakableBarrier* pBarrier = 0;
	for (uint32 i = 0; i < rvecBarrier.size(); ++i)
	{
		pBarrier = rvecBarrier[i];
		eFace = pBarrier->GetFacePosition();
		iX = pBarrier->GetX();
		iY = pBarrier->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_TOWER;
		m_pTile[iY][iX] = pBarrier;
		m_fWeight[iY][iX] = 1.2f;
	}
	//TILE_FLAME
	std::vector<CFlameGrate*>& rvecFlameGrate = m_pCube->GetFlameGrate();
	CFlameGrate* pFlameGrate = 0;
	for (uint32 i = 0; i < rvecFlameGrate.size(); ++i)
	{
		pFlameGrate = rvecFlameGrate[i];
		eFace = pFlameGrate->GetFacePosition();
		iX = pFlameGrate->GetX();
		iY = pFlameGrate->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_FLAME;
		m_pTile[iY][iX] = pFlameGrate;
		m_fWeight[iY][iX] = 4.0f;
	}
	//TILE_AMMO
	std::vector<CAmmo*>& rvecAmmo = m_pCube->GetAmmoPlate();
	CAmmo* pAmmo = 0;
	for (uint32 i = 0; i < rvecAmmo.size(); ++i)
	{
		pAmmo = rvecAmmo[i];
		eFace = pAmmo->GetFacePosition();
		iX = pAmmo->GetX();
		iY = pAmmo->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_AMMO;
		m_pTile[iY][iX] = pAmmo;
		m_fWeight[iY][iX] = 1.7f;
	}
	//TILE_MAG
	std::vector<CFaultyMagPlate*>& rvecFaultyMag = m_pCube->GetFaultyMagPlates();
	CFaultyMagPlate* pFaultyMag = 0;
	for (uint32 i = 0; i < rvecFaultyMag.size(); ++i)
	{
		pFaultyMag = rvecFaultyMag[i];
		eFace = pFaultyMag->GetFacePosition();
		iX = pFaultyMag->GetX();
		iY = pFaultyMag->GetY();
		ConvertSidePosToPlane(eFace,iX,iY);
		m_eTileType[iY][iX] = TILE_MAG;
		m_pTile[iY][iX] = pFaultyMag;
		m_fWeight[iY][iX] = 1.0f;
	}
	//TILE_FLAG - green
	CFlagPlate* pFlagPlate = m_pCube->GetFlagPlate(TEAM_GREEN);
	eFace = pFlagPlate->GetFacePosition();
	iX = pFlagPlate->GetX();
	iY = pFlagPlate->GetY();
	ConvertSidePosToPlane(eFace,iX,iY);
	m_eTileType[iY][iX] = TILE_FLAG;
	m_pTile[iY][iX] = pFlagPlate;
	m_fWeight[iY][iX] = 1.0f;
	//TILE_FLAG - purple
	pFlagPlate = m_pCube->GetFlagPlate(TEAM_PURPLE);
	eFace = pFlagPlate->GetFacePosition();
	iX = pFlagPlate->GetX();
	iY = pFlagPlate->GetY();
	ConvertSidePosToPlane(eFace,iX,iY);
	m_eTileType[iY][iX] = TILE_FLAG;
	m_pTile[iY][iX] = pFlagPlate;
	m_fWeight[iY][iX] = 1.0f;

	/*std::ostringstream outStream;
	CTotalCubeDomination::GetInstance().LogMessage("Logging tile type: ", LOG_MESSAGE_PATHS);
	for(int32 i=0; i<g_uiTileHeight; ++i)
	{
		outStream.str("");
		for(int32 j=0; j<g_uiTileWidth; ++j)
		{
			outStream<<m_fWeight[i][j];
		}
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	}*/
}

float32 CPathfinder::GetCost(int32 _iSPTID, float32 _fX, float32 _fY, EFacePosition _eFace) const
{
	if(_iSPTID<static_cast<int16>(m_vSPT.size()))
	{
		return(m_vSPT[_iSPTID]->aCost[_eFace][static_cast<int16>(_fY)*g_uiSideLength + static_cast<int16>(_fX)]);
	}
	return(0.0f);
}

float32 CPathfinder::GetWeight(int32 _iX, int32 _iY, EFacePosition _eFace) const
{
	ConvertSidePosToPlane(_eFace, _iX, _iY);
	return(m_fWeight[_iY][_iX]);
}

float32 CPathfinder::GetWeight(int32 _iX, int32 _iY) const
{
	//if the point is on the map
	if((_iY<0)||(_iY>=60))
	{
		return(0.0f);
	}
	//if the horizontal position  is outside the map's range, loop back through the other side
	while(_iX<0)
	{
		_iX += 60;
	}
	while(_iX>=60)
	{
		_iX -= 60;
	}
	return(m_fWeight[_iY][_iX]);
}

/*
* Creates a potential field
* @author			Cameron MacIntosh
* @param _target	the position of the target (on the face/ the entire cube as a 2D map?)
* @param _initial	the initial value for the potential field
* @param _exponent	the rate of change (1 is linear)
* @return ?			returns a pointer to the path?
*/
void CPathfinder::CreatePotentialField(int16 _targetX, int16 _targetY, float32 _initial, float32 _exponent)
{
	//this creates a potential field.
	//I should have two ways, one which will take in multiple sources of information,
	// and one which will cover only a single source
	//should I have a relative and absolute return?
}

/*
* Creates a potential field
* @author			Cameron MacIntosh
* @param _eDir		If the first node in this direction is connecting, then the function returns true
* @param _vec2Pos	the position to check from, which holds the X and Y of the original node
* @param _eFace		the face of the original node
* @return			true if there is a connecting node in that direction, false if there is not
*/
bool CPathfinder::IsConnecting(EDirection _eDir, D3DXVECTOR2& _vec2Pos, EFacePosition _eFace)
{
	EFacePosition eNextFace = FACE_NONE;
	int32 iX = static_cast<int32>(_vec2Pos.x);
	int32 iY = static_cast<int32>(_vec2Pos.y);
	bool bIsConnected = false;
	switch (_eDir)
	{
	case DIRECTION_LEFT:
		if(iX>0)
		{
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX-1];
		}else{
			eNextFace = GetFaceToLeft(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][g_uiSideLength-1];
			}
		}
		break;
	case DIRECTION_RIGHT:
		if(iX<g_uiSideLength-1)
		{
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX+1];
		}else{
			eNextFace = GetFaceToRight(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][0];
			}
		}
		break;
	case DIRECTION_UP:
		if(iY>0)
		{
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY-1][iX];
		}else{
			eNextFace = GetFaceAbove(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[g_uiSideLength-1][iX];
			}
		}
		break;
	case DIRECTION_DOWN:
		if(iY<g_uiSideLength-1)
		{
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY+1][iX];
		}else{
			eNextFace = GetFaceBelow(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[0][iX];
			}
		}
		break;
	}
	return(bIsConnected);
}

/*bool GetNextNode(EDirection _eDir, EFacePosition& _eFace, int32& _iX, int32& iY, int32& _iNodeVal)
{
	EFacePosition eNextFace = FACE_NONE;
	bool bIsConnected = false;
	switch (_eDir)
	{
	case DIRECTION_LEFT:
		if(iX>0)
		{
			iX -= 1;
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX];
		}else{
			eNextFace = GetFaceToLeft(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				iX = g_uiSideLength-1;
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][iX];
			}
		}
		break;
	case DIRECTION_RIGHT:
		if(iX<g_uiSideLength-1)
		{
			iX += 1;
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX];
		}else{
			eNextFace = GetFaceToRight(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				iX = 0;
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][iX];
			}
		}
		break;
	case DIRECTION_UP:
		if(iY>0)
		{
			iY -= 1;
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX];
		}else{
			eNextFace = GetFaceAbove(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				iY = g_uiSideLength-1;
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][iX];
			}
		}
		break;
	case DIRECTION_DOWN:
		if(iY<g_uiSideLength-1)
		{
			iY += 1;
			bIsConnected = m_apSideTrav[_eFace]->m_abArray[iY][iX];
		}else{
			eNextFace = GetFaceBelow(_eFace);
			if(eNextFace!=FACE_NONE)
			{
				iY = 0;
				bIsConnected = m_apSideTrav[eNextFace]->m_abArray[iY][iX];
			}
		}
		break;
	}
	_iNodeVal = indexSide(iY,iX);
	return(bIsConnected);
}*/

/*
* adds the desired amount as a weight modifier, which temporarily affects the weight of the desired tile.
*
* @author					Cameron MacIntosh
* @param _iX				the tile's x location (across all sides)
* @param _iY				the tile's y location (across all sides)
* @param _fAmtToAdd			the amount of weight to add
* @return EFacePosition		the new weight of the tile(not new weight modifier)
*/
float32 CPathfinder::AddWeightMod(int32 _iX, int32 _iY, float32 _fAmtToAdd)
{
	if(m_fWeight[_iY][_iX]!=0)
	{
		m_fWeight[_iY][_iX] += _fAmtToAdd;
		m_fWeightMod[_iY][_iX] += _fAmtToAdd;
		return(m_fWeight[_iY][_iX]);
	}
	return(0.0f);
}

/*
* returns the face conneted through the left of the entered face
* @author					Cameron MacIntosh
* @param _eFace				a face
* @return EFacePosition		the side connected to the left (or FACE_NULL if none)
*/
EFacePosition CPathfinder::GetFaceToLeft(EFacePosition _eFace)
{
	switch(_eFace)
	{
	case FACE_FRONT:
		return(FACE_LEFT);
	case FACE_BACK:
		return(FACE_RIGHT);
	case FACE_LEFT:
		return(FACE_BACK);
	case FACE_RIGHT:
		return(FACE_FRONT);
	default:
		return(FACE_NONE);
	}
}
EFacePosition CPathfinder::GetFaceToRight(EFacePosition _eFace)
{
	switch(_eFace)
	{
	case FACE_FRONT:
		return(FACE_RIGHT);
	case FACE_BACK:
		return(FACE_LEFT);
	case FACE_LEFT:
		return(FACE_FRONT);
	case FACE_RIGHT:
		return(FACE_BACK);
	default:
		return(FACE_NONE);
	}
}

EFacePosition CPathfinder::GetFaceAbove(EFacePosition _eFace)
{
	switch(_eFace)
	{
	case FACE_BOTTOM:
		return(FACE_BACK);
	case FACE_FRONT:
		return(FACE_TOP);
	default:
		return(FACE_NONE);
	}
}
EFacePosition CPathfinder::GetFaceBelow(EFacePosition _eFace)
{
	switch(_eFace)
	{
	case FACE_TOP:
		return(FACE_FRONT);
	case FACE_BACK:
		return(FACE_BOTTOM);
	default:
		return(FACE_NONE);
	}
}

/*
* converts 2D tile coordinates into a 3D vector in regular unit coordinates
* @author			Cameron MacIntosh
* @param _eFace		the face the target is on
* @param _vecPos2D	the 2D position (in tile units) to convert
* @param _vecPos3D	a reference for the in/out container that will store the result
*/
void
CPathfinder::ConvertTile2DtoUnit3D(EFacePosition _eFace, D3DXVECTOR2 _vecPos2D, D3DXVECTOR3& _vecPos3D)
{
	//the offset (axis-aligned/shortest distance from the center of the cube to the floor).
	D3DXVECTOR2 vecOffset(22.5f,22.5f);
	//convert from tile units to regular units
	_vecPos2D *= 3.0f;
	_vecPos2D -= vecOffset;
	//clear the referred vector
	memset(&_vecPos3D,0,sizeof(D3DXVECTOR3));
	//convert the 2D coordinates to 3D
	_vecPos3D += _vecPos2D.x*g_atUpRightDirectionVecs[_eFace].vec3Right;
	_vecPos3D -= _vecPos2D.y*g_atUpRightDirectionVecs[_eFace].vec3Direction;
	_vecPos3D += 22.5f*g_atUpRightDirectionVecs[_eFace].vec3Up;
}

/*
* converts 3D unit coordinates into a 2D vector in tile coordinates
* @author			Cameron MacIntosh
* @param _eFace		the face the target is on
* @param _vecPos3D	the 3D position (in regular units) to convert
* @param _vecPos2D	a reference for the in/out container that will store the result
*/
void
CPathfinder::ConvertUnit3DtoTile2D(EFacePosition& _eFace, const D3DXVECTOR3& _vecPos3D, D3DXVECTOR2& _vecPos2D)
{
	//project and convert into tile coords
    _vecPos2D.x = D3DXVec3Dot(&_vecPos3D, &g_atUpRightDirectionVecs[_eFace].vec3Right);
    _vecPos2D.y = -D3DXVec3Dot(&_vecPos3D, &g_atUpRightDirectionVecs[_eFace].vec3Direction);
	
    _vecPos2D += D3DXVECTOR2(22.5f, 22.5f);
    _vecPos2D *= 0.3333333f;
}

/*
* Converts a 2D point on a point to a point across all sides
* @author			Cameron MacIntosh
* @param _eFace		the face the point is on
* @param _vecPos2D	the 2D position on the face
* @return			the 2D position across all faces.
*/
static D3DXVECTOR2 ConvertSidePosToPlane(EFacePosition _eFace, const D3DXVECTOR2& _vecPos2D)
{
	//D3DXVECTOR2 vecPlanePos(_vecPos2D.x, _vecPos2D.y);
	switch(_eFace)
	{
	case FACE_TOP:
		return (D3DXVECTOR2(_vecPos2D.x+15.0f, _vecPos2D.y));
	case FACE_BOTTOM:
		return (D3DXVECTOR2(_vecPos2D.x+45.0f, _vecPos2D.y + 30.0f));
	case FACE_FRONT:
		return (D3DXVECTOR2(_vecPos2D.x+15.0f, _vecPos2D.y + 15.0f));
	case FACE_BACK:
		return (D3DXVECTOR2(_vecPos2D.x+45.0f, _vecPos2D.y + 15.0f));
	case FACE_LEFT:
		return (D3DXVECTOR2(_vecPos2D.x, _vecPos2D.y + 15.0f));
	case FACE_RIGHT:
		return (D3DXVECTOR2(_vecPos2D.x+30.0f, _vecPos2D.y + 15.0f));
	default:
		return (D3DXVECTOR2(0.0f,0.0f));
	}
	return (D3DXVECTOR2(0.0f,0.0f));
}

void CPathfinder::ConvertSidePosToPlane(EFacePosition _eFace, int32& _riX, int32& _riY)
{
	switch(_eFace)
	{
	case FACE_TOP:
		_riX += 15;
		return;
	case FACE_BOTTOM:
		_riX += 45;
		_riY += 30;
		return;
	case FACE_FRONT:
		_riX += 15;
		_riY += 15;
		return;
	case FACE_BACK:
		_riX += 45;
		_riY += 15;
		return;
	case FACE_LEFT:
		_riY += 15;
		return;
	case FACE_RIGHT:
		_riX += 30;
		_riY += 15;
		return;
	}
}

/*
* logs the SPT as a grid
* @author			Cameron MacIntosh
* @param _uiSPTID	the position of the target (on the face/ the entire cube as a 2D map?)
* @return bool		if the function succeeded
*/
#ifdef _DEBUG_PATHFINDER
bool CPathfinder::LogSPT(int16 _uiSPTID, EFacePosition _eFace)
{
	std::ostringstream outStream;
	outStream<<"SPT "<<_uiSPTID<<", side "<<_eFace;
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	float32 currVal = 0;
	if(static_cast<uint16>(m_vSPT.size()) > _uiSPTID)
	{
		outStream.str("");
		for(uint16 uiY=0; uiY<g_uiSideLength; ++uiY)
		{
			for(uint16 uiX=0; uiX<g_uiSideLength; ++uiX)
			{
				currVal = floorf(10*(m_vSPT[_uiSPTID]->aCost[_eFace][indexSide(uiY,uiX)]))/10;
				if(currVal<10)
				{
					if(currVal==static_cast<int32>(currVal))
					{
						outStream<<"   "<<currVal;
					}
					else
					{
						outStream<<" "<<currVal;
					}
				}
				else if(currVal>100)
				{
					outStream<<" "<<currVal;
				}
				else
				{
					outStream<<"  "<<currVal;
				}

			}
			CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
			outStream.str("");
		}
		return true;
	}
	
	outStream<<"LogSPT("<<_uiSPTID<<") failed!";
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	return false;
}

//writes the tile type array of a side to the log output
bool CPathfinder::LogTileMap(EFacePosition _eFace)
{
	std::ostringstream outStream;
	outStream<<"log for tile map (side "<<_eFace<<"):";
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);

	for(uint8 uiY=0; uiY<g_uiSideLength; ++uiY)
	{
		outStream.str("");
		for(uint8 uiX=0; uiX<g_uiSideLength; ++uiX)
		{
			//cast here, since otherwise it prints a character
			outStream<<static_cast<uint16>(m_vecSideType[_eFace][indexSide(uiY,uiX)]);
		}
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	}
	
	return true;
	outStream<<"LogTileMap("<<_eFace<<") failed!";
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	return false;
}

//writes the traversable array of a side to the log output
bool CPathfinder::LogTravMap(EFacePosition _eFace)
{
	std::ostringstream outStream;
	outStream<<"log for taversable map (side "<<_eFace<<"):";
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);

	for(uint8 uiY=0; uiY<g_uiSideLength; ++uiY)
	{
		outStream.str("");
		for(uint8 uiX=0; uiX<g_uiSideLength; ++uiX)
		{
			//cast here, since otherwise it prints a character
			outStream<<static_cast<uint16>(m_apSideTrav[_eFace]->m_abArray[uiY][uiX]);
		}
		CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	}
	
	return true;
	outStream<<"LogTravMap("<<_eFace<<") failed!";
	CTotalCubeDomination::GetInstance().LogMessage(outStream.str().c_str(), LOG_MESSAGE_PATHS);
	return false;
}
#endif // _DEBUG_PATHFINDER

/*
* Get the reference of the singleton
* @author		Cameron MacIntosh
* @return		a reference to the singleton
*/
CPathfinder&
CPathfinder::GetInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CPathfinder;
	}

	return(*s_pInstance);
}

/*
* deletes the singleton's instance
* @author		Cameron MacIntosh
*/
void
CPathfinder::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = 0;
}

/*
Requires--
- The ability to access a flameplate through it's 2D position (store in cube?)
- memory leak fix
- some access to a stored 2D array of the game (that's updated as altered)

Ideal--
- records worthwhile intersections
- places an increased cost on dead ends (when desirable)
- should be able to edit a path when barrier is destroyed
- calculates path over multiple process calls
- should it be able to store paths (ie. to flags), and if so, should it store all paths

other--

*/

/*
* GetCube
* @author Rigardt de Vries
* @return CCube*
*/
CCube*
CPathfinder::GetCube()
{
    return (m_pCube);
}