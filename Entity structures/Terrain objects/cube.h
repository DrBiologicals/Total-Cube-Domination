// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   cube.h
//  Description :   Declaration for Ccube
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//


#ifndef __IGFEB10_MODULE_CUBE_H__
#define __IGFEB10_MODULE_CUBE_H__

// Library Includes
#include <d3d9.h>
#include <vector>
// Local Includes
#include "../../defines.h"
#include "../renderentity.h"
#include "tile.h"

// Types
const DWORD MESH_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

struct TMeshVertex
{
	D3DXVECTOR3 vec3Pos;
	D3DXVECTOR3 vec3Normal;
	D3DXVECTOR2 vec2UV;
};

struct TFaceTraversibilityArray
{
	bool m_abArray[15][15];
};

// Prototypes
class CFlagPlate;
class CFlag;
class CFaultyMagPlate;
class CFlameGrate;
class CAmmo;
class CBreakableBarrier;
class CWall;
class CTower;
class CSkyBox;

class CCube : public CRenderEntity
{
	// Member Functions
public:
	CCube();
	virtual ~CCube();

	bool Initialise(uint32 _uiTextureID, uint32 _uiModelID);

	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	bool LoadMap(const char* _kpcFileName);

	const TFaceTraversibilityArray& GetPassabilityArray(EFacePosition _eFace) const;

    const TBoundingBox& GetEdgeAABB(uint32 _uiAABBID);
	TBoundingBox GetBlockEdgeAABB(uint32 _uiAABBID);

	std::vector<CWall*>& GetWalls();
	std::vector<CTower*>& GetTowers();
	std::vector<CFlameGrate*>& GetFlameGrate();
	std::vector<CFaultyMagPlate*>& GetFaultyMagPlates();
	std::vector<CAmmo*>& GetAmmoPlate();
    std::vector<CBreakableBarrier*>& GetBreakableBarrier();

	CFlag* GetFlag(ETeam _eTeam);
	CFlagPlate* GetFlagPlate(ETeam _eTeam);

	static CCube* GetCube();

protected:
	void CreateWallBuffer(uint32 _uiWallModelID);

private:

	// Member Variables
public:

protected:
	uint32 m_uiTextureID;
	uint32 m_uiModelID;
	
	std::vector<CWall*> m_vecWall;
	std::vector<CTower*> m_vecTower;
	std::vector<CFlameGrate*> m_vecFlameGrate;
	std::vector<CFaultyMagPlate*> m_vecFaultyMagPlates;
	std::vector<CAmmo*> m_vecAmmoPlate;
    std::vector<CBreakableBarrier*> m_vecBreakablBarriers;

	CFlagPlate* m_pGreenFlagPlate;
	CFlagPlate* m_pPurpleFlagPlate;

	// Flags.
	CFlag* m_pGreenFlag;
	CFlag* m_pPurpleFlag;

	uint32 m_uiWallTextureID;
	LPDIRECT3DVERTEXBUFFER9 m_pWallVB;
	
    TBoundingBox m_aTransitionBoxes[TRANSITION_MAX];
	TBoundingBox m_aBlockBoxes[TRANSITION_MAX];

	TFaceTraversibilityArray m_atFacePassability[6];

	ETileType m_eTileType[g_uiTileHeight][g_uiTileWidth];
	CTile* m_pTile[g_uiTileHeight][g_uiTileWidth];

	uint32 sprite;

	CSkyBox* m_pSkyBox;

	static CCube* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_CUBE_H__

