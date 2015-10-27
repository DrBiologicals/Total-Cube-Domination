// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   cube.cpp
//  Description :   cube.cppfor implementation of cube.h
//  Author      :   Michael McQuarrie
//  Mail        :  michael.mcquarrie@mediadesign.school.nz
//


// Library Includes
#include <fstream>

// Local Includes
#include "../../Engine/TotalCubeDomination.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/TextureManager.h"
#include "../../engine/graphics and sound/lightManager.h"
#include "../Player Objects/Power up/powerupmanager.h"
#include "../Player Objects/playermanager.h"
#include "wall.h"
#include "tower/tower.h"
#include "flagplate.h"
#include "faultymagplate.h"
#include "flag.h"
#include "flamegrate.h"
#include "ammo.h"
#include "breakablebarrier.h"
#include "skybox.h"
#include "../../igutils.h"

// This Includes

#include "cube.h"

// Static Variables
CCube* CCube::s_pInstance = 0;

// Static Function Prototypes


// Implementation
CCube::CCube()                                                                                                                                                                                                                                                   
: m_uiTextureID(BAD_ID)
, m_uiModelID(BAD_ID)
, m_pGreenFlagPlate(0)
, m_pPurpleFlagPlate(0)
, m_pGreenFlag(0)
, m_pPurpleFlag(0)
, m_pSkyBox(0)
, m_pWallVB(0)
, m_uiWallTextureID(BAD_ID)
{
	memset(&m_atFacePassability, true, sizeof(m_atFacePassability));
	memset(&m_eTileType, TILE_NONE, sizeof(m_eTileType));
	memset(&m_pTile, 0, sizeof(m_pTile));
}

CCube::~CCube()
{
	for (uint32 i = 0; i < m_vecWall.size(); ++i)
	{
		delete m_vecWall[i];
	}
	for (uint32 i = 0; i < m_vecTower.size(); ++i)
	{
		delete m_vecTower[i];
	}
	for (uint32 i = 0; i < m_vecFlameGrate.size(); ++i)
	{
		delete m_vecFlameGrate[i];
	}
    for (uint32 i = 0; i < m_vecFaultyMagPlates.size(); ++i)
	{
		delete m_vecFaultyMagPlates[i];
	}
	for (uint32 i = 0; i < m_vecAmmoPlate.size(); ++i)
	{
		delete m_vecAmmoPlate[i];
	}
    for (uint32 i = 0; i < m_vecBreakablBarriers.size(); ++i)
	{
		delete m_vecBreakablBarriers[i];
    }

	m_vecTower.clear();
	m_vecWall.clear();
	m_vecFlameGrate.clear();
	m_vecAmmoPlate.clear();
    m_vecFaultyMagPlates.clear();
    m_vecBreakablBarriers.clear();

	// Delete flag plates.
	delete m_pGreenFlagPlate;
	m_pGreenFlagPlate = 0;

	delete m_pPurpleFlagPlate;
	m_pPurpleFlagPlate = 0;

	// Delete flags.
	delete m_pGreenFlag;
	m_pGreenFlag = 0;

	delete m_pPurpleFlag;
	m_pPurpleFlag = 0;

	delete m_pSkyBox;
	m_pSkyBox = 0;

	if (m_pWallVB)
	{
		m_pWallVB->Release();
		m_pWallVB = 0;
	}

	s_pInstance = 0;
}

/*
* 
* @author Michael McQuarrie
* @param _vec3Position The posistion of the cube
* @param _uiTextureID the texture id
* @param _uiModelID The model ID
* @param _kcpFileName The file name
* @return true when done
*/
bool
CCube::Initialise(uint32 _uiTextureID, uint32 _uiModelID)
{
	//Getting Entity
	CEntity::Initialise();

	//Setting world matrix
	D3DXMatrixIdentity(&m_matWorld);

	//Setting texture and Model
	m_uiTextureID = _uiTextureID;
	m_uiModelID = _uiModelID;

	//Making a bounding box
	D3DXVECTOR3* pFirstVertex = 0;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(m_uiModelID)->GetModel();

	pMesh->LockVertexBuffer(0, (void**)&pFirstVertex);

	D3DXComputeBoundingBox(pFirstVertex, 
							pMesh->GetNumVertices(),
							pMesh->GetNumBytesPerVertex(), 
							&m_tOBB.m_vec3Min, &m_tOBB.m_vec3Max);

	pMesh->UnlockVertexBuffer();

    // Bounding boxes for face transitions
    m_aTransitionBoxes[TRANSITION_FRONT_TOP] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_FRONT_TOP].m_vec3Max += D3DXVECTOR3(0.0f, 46.0f, -46.0f);
    m_aTransitionBoxes[TRANSITION_FRONT_TOP].m_vec3Min += D3DXVECTOR3(0.0f, 46.0f, -46.0f);

    m_aTransitionBoxes[TRANSITION_FRONT_LEFT] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_FRONT_LEFT].m_vec3Max += D3DXVECTOR3(-46.0f, 0.0f, -46.0f);
    m_aTransitionBoxes[TRANSITION_FRONT_LEFT].m_vec3Min += D3DXVECTOR3(-46.0f, 0.0f, -46.0f);

    m_aTransitionBoxes[TRANSITION_FRONT_RIGHT] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_FRONT_RIGHT].m_vec3Max += D3DXVECTOR3(46.0f, 0.0f, -46.0f);
    m_aTransitionBoxes[TRANSITION_FRONT_RIGHT].m_vec3Min += D3DXVECTOR3(46.0f, 0.0f, -46.0f);

    m_aTransitionBoxes[TRANSITION_BACK_BOTTOM] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_BACK_BOTTOM].m_vec3Max += D3DXVECTOR3(0.0f, -46.0f, 46.0f);
    m_aTransitionBoxes[TRANSITION_BACK_BOTTOM].m_vec3Min += D3DXVECTOR3(0.0f, -46.0f, 46.0f);

    m_aTransitionBoxes[TRANSITION_BACK_LEFT] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_BACK_LEFT].m_vec3Max += D3DXVECTOR3(-46.0f, 0.0f, 46.0f);
    m_aTransitionBoxes[TRANSITION_BACK_LEFT].m_vec3Min += D3DXVECTOR3(-46.0f, 0.0f, 46.0f);

    m_aTransitionBoxes[TRANSITION_BACK_RIGHT] = m_tOBB;

    m_aTransitionBoxes[TRANSITION_BACK_RIGHT].m_vec3Max += D3DXVECTOR3(46.0f, 0.0f, 46.0f);
    m_aTransitionBoxes[TRANSITION_BACK_RIGHT].m_vec3Min += D3DXVECTOR3(46.0f, 0.0f, 46.0f);


	m_aBlockBoxes[BLOCK_LEFT_TOP] = m_tOBB;
	m_aBlockBoxes[BLOCK_LEFT_TOP].m_vec3Max += D3DXVECTOR3(-45.0f, 45.0f, 0.0f);
	m_aBlockBoxes[BLOCK_LEFT_TOP].m_vec3Min += D3DXVECTOR3(-45.0f, 45.0f, 0.0f);

	m_aBlockBoxes[BLOCK_BACK_TOP] = m_tOBB;
	m_aBlockBoxes[BLOCK_BACK_TOP].m_vec3Max += D3DXVECTOR3(0.0f, 45.0f, 45.0f);
	m_aBlockBoxes[BLOCK_BACK_TOP].m_vec3Min += D3DXVECTOR3(0.0f, 45.0f, 45.0f);

	m_aBlockBoxes[BLOCK_RIGHT_TOP] = m_tOBB;
	m_aBlockBoxes[BLOCK_RIGHT_TOP].m_vec3Max += D3DXVECTOR3(45.0f, 45.0f, 0.0f);
	m_aBlockBoxes[BLOCK_RIGHT_TOP].m_vec3Min += D3DXVECTOR3(45.0f, 45.0f, 0.0f);

	m_aBlockBoxes[BLOCK_LEFT_BOTTOM] = m_tOBB;
	m_aBlockBoxes[BLOCK_LEFT_BOTTOM].m_vec3Max += D3DXVECTOR3(-45.0f, -45.0f, 0.0f);
	m_aBlockBoxes[BLOCK_LEFT_BOTTOM].m_vec3Min += D3DXVECTOR3(-45.0f, -45.0f, 0.0f);

	m_aBlockBoxes[BLOCK_FRONT_BOTTOM] = m_tOBB;
	m_aBlockBoxes[BLOCK_FRONT_BOTTOM].m_vec3Max += D3DXVECTOR3(0.0f, -45.0f, -45.0f);
	m_aBlockBoxes[BLOCK_FRONT_BOTTOM].m_vec3Min += D3DXVECTOR3(0.0f, -45.0f, -45.0f);

	m_aBlockBoxes[BLOCK_RIGHT_BOTTOM] = m_tOBB;
	m_aBlockBoxes[BLOCK_RIGHT_BOTTOM].m_vec3Max += D3DXVECTOR3(45.0f, -45.0f, 0.0f);
	m_aBlockBoxes[BLOCK_RIGHT_BOTTOM].m_vec3Min += D3DXVECTOR3(45.0f, -45.0f, 0.0f);

	//set the sides' tiles to default normal tile type
	//m_eTileType[i][j] = TILE_NORMAL;

	CreateAABB();

	if(!s_pInstance)
	{
		s_pInstance = this;
	}

	return(true);
}

/*
* 
* @author Michael McQuarrie
* 
* @return void
*/
void
CCube::Draw()
{
	//Set the world matrix
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);
	CTextureManager::GetInstance().SetTexture(0,m_uiTextureID);
	//Draw the model
	CModelManager::GetInstance().Draw(m_uiModelID);

	LPDIRECT3DDEVICE9 pDevice = CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice();

	CTextureManager::GetInstance().SetTexture(0, m_uiWallTextureID);

	pDevice->SetFVF(MESH_FVF);
	pDevice->SetStreamSource(0, m_pWallVB, 0, static_cast<uint32>(sizeof(TMeshVertex)));
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, static_cast<uint32>(10 * m_vecWall.size()));
}

/*
* 
* @author Michael McQuarrie
* @param _fDeltaTick The delta tick
* @return void
*/
void
CCube::Process(float32 _fDeltaTick)
{
	//Add to the viewport
    for (uint32 ui = 0; ui < m_vecBreakablBarriers.size(); ++ui)
    {
        if (m_vecBreakablBarriers[ui])
        {
            if (m_vecBreakablBarriers[ui]->IsDestroyed() == true)
            {
		        m_atFacePassability[m_vecBreakablBarriers[ui]->GetFacePosition()].m_abArray[m_vecBreakablBarriers[ui]->GetY()][m_vecBreakablBarriers[ui]->GetX()] = true;

                delete m_vecBreakablBarriers[ui];
                m_vecBreakablBarriers[ui] = 0;
            }
        }
    }

	CPowerUpManager::GetInstance().Process(_fDeltaTick);

	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
}

bool 
CCube::LoadMap(const char* _kpcFileName)
{
	std::ifstream MapFile;

	// Open the map file
	MapFile.open(_kpcFileName, std::ios_base::binary);

	VALIDATE(MapFile.good());

	// Skip the map name
	MapFile.seekg(32, std::ios_base::beg);

	VALIDATE(MapFile.good());

	// Read the ambient colour
	D3DCOLOR MapAmbient = 0;

	MapFile.read((char*)&MapAmbient, sizeof(MapAmbient));

	D3DXCOLOR MapAmbientFloat(MapAmbient);

	VALIDATE(MapFile.good());

	// Set the map light
	D3DLIGHT9 AmbientLight;
	ZeroMemory(&AmbientLight, sizeof(AmbientLight));

	AmbientLight.Direction.x = 1.0f;
	AmbientLight.Type = D3DLIGHT_DIRECTIONAL;
	AmbientLight.Ambient = MapAmbientFloat;

	uint32 uiLightID = CLightManager::GetInstance().CreateLight(AmbientLight);
	CLightManager::GetInstance().SetLightActive(uiLightID, true);

	uint32 uiSkyboxModelID = CModelManager::GetInstance().CreateModel("models/obj_skybox.x");
    uint32 uiWallTlModelID = CModelManager::GetInstance().CreateModel("models/tile_wall.x");
    uint32 uiFlatTlModelID = CModelManager::GetInstance().CreateModel("models/tile_flat.x");
	uint32 uiAmmoPlModelID = CModelManager::GetInstance().CreateModel("models/tile_ammo_base.x");
	uint32 uiAmmoLtModelID = CModelManager::GetInstance().CreateModel("models/tile_ammo_light.x");
	uint32 uiFlagPlModelID = CModelManager::GetInstance().CreateModel("models/tile_flagplate.x");
	uint32 uiTowerBModelID = CModelManager::GetInstance().CreateModel("models/tile_tower_base.x");
	uint32 uiTurretModelID = CModelManager::GetInstance().CreateModel("models/tile_tower_turret.x");
	uint32 uiTmFlagModelID = CModelManager::GetInstance().CreateModel("models/obj_flag.x");
    
	uint32 uiSkyboxTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_skybox_dark.png");
	uint32 uiWallTlTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_wall_normal2.png");
	uint32 uiFlameGTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_flamegrate.png");
	uint32 uiAmmoPlTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_ammo.png");
	uint32 uiBrkBarTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_breakable_barrier.png");
	uint32 uiFlagPGTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_flagTile_green.png");
	uint32 uiFlagPPTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_flagTile_purple.png");
	uint32 uiTowerGTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_green.png");
	uint32 uiTowDsGTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_green_disable.png");
	uint32 uiTowerPTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_purple.png");
	uint32 uiTowDsPTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_purple_disable.png");
	uint32 uiTowerNTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_neutral.png");
	uint32 uiTowDsNTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_neutral_disable.png");
	uint32 uiFlagGrTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_flag_green.png");
	uint32 uiFlagPrTextureID = CTextureManager::GetInstance().CreateTexture("textures/obj_flag_purple.png");
	uint32 uiMagPltTextureID = CTextureManager::GetInstance().CreateTexture("textures/tile_faulty.png");

	m_uiWallTextureID = uiWallTlTextureID;

	// Load faces
	while (MapFile.good())
	{
		uint16 usFaceHeader = 0;

		MapFile.read((char*)&usFaceHeader, sizeof(usFaceHeader));

		uint32 uiFaceNumber = (usFaceHeader >> 11) & 0x7;
		uint32 uiNumberOfTiles = usFaceHeader & 0x7ff;

		// Load tiles on face
		for (uint32 i = 0; i < uiNumberOfTiles; ++i)
		{
			uint16 usTileData = 0;

			MapFile.read((char*)&usTileData, sizeof(usTileData));

			uint32 uiTileY = usTileData & 0x1f;
			uint32 uiTileX = (usTileData >> 5) & 0x1f;
			uint32 uiTileType = (usTileData >> 12) & 0xf;
			uint32 uiTileOwner = (usTileData >> 10) & 0x3;

			switch (uiTileType)
			{
				case FTILE_WALL:
				{
					CWall* pWall = new CWall;

					pWall->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, uiWallTlModelID);

					m_vecWall.push_back(pWall);
				}
				break;

				case FTILE_AMMO:
				{
					CAmmo* pAmmo = new CAmmo;

					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							pAmmo->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
								uiAmmoPlModelID, uiAmmoLtModelID, uiAmmoPlTextureID, TEAM_GREEN);
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							pAmmo->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
								uiAmmoPlModelID, uiAmmoLtModelID, uiAmmoPlTextureID, TEAM_PURPLE);
						}
						break;

						case FOWNER_NEUTRAL:
						{
							pAmmo->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
								uiAmmoPlModelID, uiAmmoLtModelID, uiAmmoPlTextureID, TEAM_NEUTRAL);
						}
						break;
					}

					m_vecAmmoPlate.push_back(pAmmo);
				}
				break;

				case FTILE_BARRIER:
				{
					CBreakableBarrier* pBB = new CBreakableBarrier;

					pBB->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
						uiWallTlModelID, uiBrkBarTextureID);

					m_vecBreakablBarriers.push_back(pBB);
				}
				break;

				case FTILE_FLAG_PLATE:
				{
					CFlagPlate* pFlagPlate = new CFlagPlate;

					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							VALIDATE(!m_pGreenFlagPlate);

							pFlagPlate->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
								TEAM_GREEN, uiFlagPlModelID, uiFlagPGTextureID);

							m_pGreenFlagPlate = pFlagPlate;

							m_pGreenFlag = new CFlag();
							m_pGreenFlag->Initialise(uiTmFlagModelID, uiFlagGrTextureID, TEAM_GREEN, m_pGreenFlagPlate);
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							VALIDATE(!m_pPurpleFlagPlate);

							pFlagPlate->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
								TEAM_PURPLE, uiFlagPlModelID, uiFlagPPTextureID);

							m_pPurpleFlagPlate = pFlagPlate;

							m_pPurpleFlag = new CFlag();
							m_pPurpleFlag->Initialise(uiTmFlagModelID, uiFlagPrTextureID, TEAM_PURPLE, m_pPurpleFlagPlate);
						}
						break;

						default: return (false);
					}
				}
				break;

				case FTILE_FLAME_GRATE:
				{
					CFlameGrate* pFlameGrate = new CFlameGrate;

					pFlameGrate->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, 
						uiFlatTlModelID, uiFlameGTextureID);

					m_vecFlameGrate.push_back(pFlameGrate);
				}
				break;

				case FTILE_MAG_PLATE:
				{
					CFaultyMagPlate* pMagPlate = new CFaultyMagPlate;

					pMagPlate->Initialise(uiTileX, uiTileY, static_cast<EFacePosition>(uiFaceNumber), 
						uiFlatTlModelID, uiMagPltTextureID, (EFileDirection)uiTileOwner);

					m_vecFaultyMagPlates.push_back(pMagPlate);
				}
				break;

				case FTILE_TOWER:
				{
					CTower* pTower = new CTower;

					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							pTower->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, TEAM_GREEN, 
								uiTowerGTextureID, uiTowDsGTextureID, uiTowerBModelID, uiTurretModelID);
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							pTower->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, TEAM_PURPLE, 
								uiTowerPTextureID, uiTowDsPTextureID, uiTowerBModelID, uiTurretModelID);
						}
						break;

						case FOWNER_NEUTRAL:
						{
							pTower->Initialise(static_cast<EFacePosition>(uiFaceNumber), uiTileX, uiTileY, TEAM_NEUTRAL, 
								uiTowerNTextureID, uiTowDsNTextureID, uiTowerBModelID, uiTurretModelID);
						}
						break;
					}

					m_vecTower.push_back(pTower);
				}
				break;

				case FTILE_PLAYER_SPAWN:
				{
					// Player spawn
					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							CPlayerManager::GetPlayerManagerInstance().AddSpawnLocation(uiTileX, uiTileY, (EFacePosition)(uiFaceNumber), TEAM_GREEN);
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							CPlayerManager::GetPlayerManagerInstance().AddSpawnLocation(uiTileX, uiTileY, (EFacePosition)(uiFaceNumber), TEAM_PURPLE);
						}
						break;

						case FOWNER_NEUTRAL:
						{
							CPlayerManager::GetPlayerManagerInstance().AddSpawnLocation(uiTileX, uiTileY, (EFacePosition)(uiFaceNumber), TEAM_GREEN);
							CPlayerManager::GetPlayerManagerInstance().AddSpawnLocation(uiTileX, uiTileY, (EFacePosition)(uiFaceNumber), TEAM_PURPLE);
						}
						break;
					}
				}
				break;

				case FTILE_POWER_SPAWN:
				{
					// Powerup spawn
					CPowerUpManager::GetInstance().AddSpawnLocation(static_cast<EFacePosition>(uiFaceNumber), 
						uiTileX, uiTileY);
				}
				break;

				default: return (false);
			}
		}
	}

	MapFile.close();

	VALIDATE(m_pGreenFlagPlate);
	VALIDATE(m_pPurpleFlagPlate);

	m_pSkyBox = new CSkyBox();
	m_pSkyBox->Initialise(uiSkyboxModelID, uiSkyboxTextureID);

	for (uint32 i = 0; i < m_vecWall.size(); ++i)
	{
		m_atFacePassability[m_vecWall[i]->GetFacePosition()].m_abArray[m_vecWall[i]->GetY()][m_vecWall[i]->GetX()] = m_vecWall[i]->IsTraversable();
	}
    for (uint32 i = 0; i < m_vecBreakablBarriers.size(); ++i)
	{
		m_atFacePassability[m_vecBreakablBarriers[i]->GetFacePosition()].m_abArray[m_vecBreakablBarriers[i]->GetY()][m_vecBreakablBarriers[i]->GetX()] = false;
	}
    for (uint32 i = 0; i < m_vecTower.size(); ++i)
	{
		m_atFacePassability[m_vecTower[i]->GetFacePosition()].m_abArray[m_vecTower[i]->GetY()][m_vecTower[i]->GetX()] = false;
	}

	CPowerUpManager::GetInstance().Initialise();

	CreateWallBuffer(uiWallTlModelID);

	return (true);
}

const TFaceTraversibilityArray& 
CCube::GetPassabilityArray(EFacePosition _eFace) const
{
	return (m_atFacePassability[_eFace]);
}

const TBoundingBox&
CCube::GetEdgeAABB(uint32 _uiAABBID)
{
    return (m_aTransitionBoxes[_uiAABBID]);
}
TBoundingBox
CCube::GetBlockEdgeAABB(uint32 _uiAABBID)
{
	return (m_aBlockBoxes[_uiAABBID]);
}

std::vector<CWall*>&
CCube::GetWalls()
{
	return(m_vecWall);
}

/*
* GetTowers
* @author Rigardt de Vries
* @return std::vector<CTower*>&
*/
std::vector<CTower*>&
CCube::GetTowers()
{
	return(m_vecTower);
}

/*
* GetBreakableBarrier
* @author Rigardt de Vries
* @return std::vector<CBreakablebarrier*>&
*/
std::vector<CBreakableBarrier*>&
CCube::GetBreakableBarrier()
{
    return (m_vecBreakablBarriers);
}

/*
* GetFaultyMagPlates
* @author Rigardt de Vries
* @return std::vector<CFaultyMagPlate*>&
*/
std::vector<CFaultyMagPlate*>&
CCube::GetFaultyMagPlates()
{
    return (m_vecFaultyMagPlates);
}

std::vector<CFlameGrate*>&
CCube::GetFlameGrate()
{
	return(m_vecFlameGrate);
}
std::vector<CAmmo*>&
CCube::GetAmmoPlate()
{
	return(m_vecAmmoPlate);
}
/**
* 
* Returns a pointer to the green or purple flag, specified by the 
*	team passed in.
* 
* @author Rebeccah Cox
* @param ETeam _eTeam - which team the flag belongs to.
* @return CFlag* m_pGreenFlag OR m_pPurpleFlag
*/
CFlag*
CCube::GetFlag(ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		return (m_pGreenFlag);
	}
	else // TEAM_PURPLE
	{
		return (m_pPurpleFlag);
	}
}

CFlagPlate*
CCube::GetFlagPlate(ETeam _eTeam)
{
	if(TEAM_GREEN == _eTeam)
	{
		return (m_pGreenFlagPlate);
	}
	else // TEAM_PURPLE
	{
		return (m_pPurpleFlagPlate);
	}
}

void
CCube::CreateWallBuffer(uint32 _uiWallModelID)
{
	if (!m_vecWall.size()) return;

	LPD3DXMESH pMesh = CModelManager::GetInstance().GetModel(_uiWallModelID)->GetModel();

	CTotalCubeDomination::GetInstance().GetRenderer()->GetDevice()->
		CreateVertexBuffer(pMesh->GetNumVertices() * pMesh->GetNumBytesPerVertex() * m_vecWall.size(), 
		0, pMesh->GetFVF(), D3DPOOL_MANAGED, &m_pWallVB, 0);

	TMeshVertex* pWallVData;
	TMeshVertex* pVData = 0;
	uint16* pIData = 0;

	m_pWallVB->Lock(0, 0, (void**)&pWallVData, 0);

	pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVData);
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&pIData);

	for (uint32 i = 0; i < m_vecWall.size(); ++i)
	{
		const D3DXMATRIX& krWorldMat = m_vecWall[i]->GetWorldMatrix();

		for (uint32 j = 0; j < pMesh->GetNumVertices(); ++j)
		{
			pWallVData[i * pMesh->GetNumVertices() + j] = pVData[pIData[j]];

			D3DXVec3TransformCoord(&(pWallVData[i * pMesh->GetNumVertices() + j].vec3Pos),
				&(pWallVData[i * pMesh->GetNumVertices() + j].vec3Pos), &krWorldMat);
		}
	}

	pMesh->UnlockVertexBuffer();
	pMesh->UnlockIndexBuffer();

	m_pWallVB->Unlock();
}

CCube* CCube::GetCube()
{
	if(s_pInstance!=0)
	{
		return(s_pInstance);
	}
	return(0);
}