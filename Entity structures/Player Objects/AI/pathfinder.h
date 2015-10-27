// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   pathfinder.h
//  Description :   Declaration for Cpathfinder
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PATHFINDER_H__
#define __IGFEB10_MODULE_PATHFINDER_H__

#ifdef _DEBUG
	//#define _DEBUG_PATHFINDER
#endif //_DEBUG

// Library Includes
#include <vector>

// Local Includes
#include "../../entity.h"
#include "../../../defines.h"

// Types
typedef std::vector<TNode> pathVector;

// Prototypes
class CTank;
class CCube;
class CTile;
struct TFaceTraversibilityArray;
#ifdef _DEBUG
class CLogManager;
#endif // _DEBUG

enum EStoredSPT
{
	SPT_FLAG_G,
	SPT_FLAG_P,
	SPT_FLAGPLATE_G,
	SPT_FLAGPLATE_P,
	SPT_TANK,
	SPT_TOWER,
	SPT_POWERUP
};

struct TNodeHelper
{
	int32 iTile;
	EFacePosition eFace;
};

enum ENodeStatus
{
	NODE_CLOSED,	//nodes that have been checked AND nodes that can't be used (like walls) use this value.
	NODE_UNUSED,
	NODE_OPEN
};

struct TNodeCosts
{
	EFacePosition eFace;
	int16 iX, iY;
	int16 iParentID;
	float32 fGCost;
	float32 fHCost;
	float32 fFCost;
};

//#define TILE_MAX = g_uiSideLength * g_uiSideLength * 6

class CPathfinder : public CEntity
{
	// Member Functions
public:
	CPathfinder();
	~CPathfinder();
	virtual bool Initialise(CCube* _pCube);

	virtual void Process(float32 _fDeltaTick);
	
	TSPT* GetSPT(int32 _iSPTID);
	TSPT* GetFlagSPT(ETeam _eTeam);
	TSPT* GetFlagPlateSPT(ETeam _eTeam);

    CCube* GetCube();

	//bool GetSPT(CTank* _pCaller, void* _pTarget, float32 _fRange32 = -1);
	//bool GetSPT(CTank* _pCaller, int16 _iTargetX, int16 _iTargetY, float32 _fRange = -1);
	//bool CreateSPT(void* _pTarget, float32 _fRange = -1);
	bool CreateSPT(int32& _iSPTID, int32 _iTargetX, int32 _iTargetY, EFacePosition _eFace, int32 _fRange = -1);
	bool CreatePathAStar(pathVector& _vtPath, const TNode& _tOrigin, const TNode& _tTarget, float32 _fRange = 500);

	void CreatePotentialField(int16 _iTargetX, int16 _iTargetY, float32 _fInitial, float32 _fExponent = 1);

	void SetTileArrays();

	float32 GetCost(int32 _iSPTID, float32 _fX, float32 _fY, EFacePosition _eFace) const;
	float32 GetWeight(int32 _iX, int32 _iY, EFacePosition _eFace) const;
	float32 GetWeight(int32 _iX, int32 _iY) const;

	bool IsConnecting(EDirection _eDir, D3DXVECTOR2& _vec2Pos, EFacePosition _eFace);
	bool GetNextNode(EDirection _eDir, EFacePosition& _eFace, int32& _iX, int32& iY, int32& _iNodeVal);

	float32 AddWeightMod(int32 _iX, int32 _iY, float32 _fAmtToAdd); 

	static EFacePosition GetFaceToLeft(EFacePosition _eFace);
	static EFacePosition GetFaceToRight(EFacePosition _eFace);
	static EFacePosition GetFaceAbove(EFacePosition _eFace);
	static EFacePosition GetFaceBelow(EFacePosition _eFace);

	static void ConvertTile2DtoUnit3D(EFacePosition _eFace, D3DXVECTOR2 _vecPos2D, D3DXVECTOR3& _vecPos3D);
	static void ConvertUnit3DtoTile2D(EFacePosition& _eFace, const D3DXVECTOR3& _vecPos3D, D3DXVECTOR2& _vecPos2D);
	static D3DXVECTOR2 ConvertSidePosToPlane(EFacePosition _eFace, const D3DXVECTOR2& _vecPos2D);
	static void ConvertSidePosToPlane(EFacePosition _eFace, int32& _riX, int32& _riY);

	#ifdef _DEBUG_PATHFINDER
	bool LogSPT(int16 _uiSPTID, EFacePosition _eFace);
	bool LogTileMap(EFacePosition _eFace);
	bool LogTravMap(EFacePosition _eFace);
	#endif //_DEBUG_PATHFINDER

	static CPathfinder& GetInstance();
	static void DestroyInstance();

protected:

private:

	// Member Variables
public:

protected:
	CCube* m_pCube;
	uint8 m_vecSideType[6][g_uiSideNodeTotal];
	const TFaceTraversibilityArray* m_apSideTrav[6];

	std::vector<TSPT*> m_vSPT;
	pathVector m_vPath[16];
	static CPathfinder* s_pInstance;
	bool bInit;

	TNodeCosts m_tCostMap[6][g_uiSideLength][g_uiSideLength];	//eFace, iY, iX
	ENodeStatus m_eStatusMap[6][g_uiSideLength][g_uiSideLength];

	int32 m_uiGreenFlagSPTID;
	int32 m_uiPurpleFlagSPTID;
	int32 m_uiGreenFlagPlateSPTID;
	int32 m_uiPurpleFlagPlateSPTID;

	ETileType m_eTileType[g_uiTileHeight][g_uiTileWidth];
	CTile* m_pTile[g_uiTileHeight][g_uiTileWidth];

	float32 m_fWeight[g_uiTileHeight][g_uiTileWidth];
	float32 m_fWeightMod[g_uiTileHeight][g_uiTileWidth];

	float32 m_fMagWeight;

private:
	
}; 

#endif // __IGFEB10_MODULE_PATHFINDER_H__