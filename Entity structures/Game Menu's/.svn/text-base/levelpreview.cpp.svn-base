// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   levelpreview.cpp
//  Description :   levelpreview.cppfor implementation of levelpreview.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes
#include <fstream>

// Local Includes
#include "../../Engine/Graphics and sound/fontmanager.h"
#include "../../Engine/Graphics and sound/modelmanager.h"
#include "../../Engine/Graphics and sound/model.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/Graphics and sound/texture.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/billboardmanager.h"
#include "../../Engine/Graphics and sound/billboard.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../../Engine/Input/input.h"
#include "../../Engine/input/inputhandler.h"
#include "../../Engine/Game/menustate.h"
#include "../../Engine/Game/gamestate.h"

// This Includes
#include "levelpreview.h"

// Static Variables
uint32 CLevelPreviewer::s_uiModelID = BAD_ID;
uint32 CLevelPreviewer::s_uiTextureID = BAD_ID;
// Static Function Prototypes

// Implementation

CLevelPreviewer::CLevelPreviewer()
: m_fAngle(0.0f)
{
}

CLevelPreviewer::~CLevelPreviewer()
{
	UnLoadMap();
}
/**
* 
* Sets the cube as a menu item and then creates a texture and a model for the cube.
* 
* @author Carsten Scholz
* @return void.
*/
bool
CLevelPreviewer::Initialise(D3DXVECTOR3 _vec3Position)
{
	//Normal Initialise stuff for menus
	CMenuItem::Initialise();

	m_vec3Position = _vec3Position;
	
	D3DXMatrixIdentity(&m_matWorld);

	s_uiModelID = CModelManager::GetInstance().CreateModel("models/pvw_cube10p5.x");	// 0.7
	//s_uiModelID = CModelManager::GetInstance().CreateModel("models/pvw_cube9.x");	// 0.6
	//s_uiModelID = CModelManager::GetInstance().CreateModel("models/pvw_cube7p5.x");	// 0.5
	s_uiTextureID = CTextureManager::GetInstance().CreateTexture("textures/pvw_cube_normal.png");

	m_uiWallModel = CModelManager::GetInstance().CreateModel("models/preview/pvw_wall.x");
	m_uiWallTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_wall_normal2.png");
	m_uiBBTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_breakable_barrier.png");

	m_uiAmmoModel = CModelManager::GetInstance().CreateModel("models/preview/pvw_ammo.x");
	m_uiAmmoTexture = CTextureManager::GetInstance().CreateTexture("textures/preview/pvw_ammo.png");

	m_uiFlagModel = CModelManager::GetInstance().CreateModel("models/preview/pvw_flagtile.x");
	m_uiFlagGTexture = CTextureManager::GetInstance().CreateTexture("textures/preview/pvw_flagtile_green.png");
	m_uiFlagPTexture = CTextureManager::GetInstance().CreateTexture("textures/preview/pvw_flagtile_purple.png");

	m_uiFlatModel = CModelManager::GetInstance().CreateModel("models/preview/pvw_flat.x");
	m_uiFlameTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_flamegrate.png");
	m_uiMagTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_faulty.png");

	m_uiPowerModel = CModelManager::GetInstance().CreateModel("models/preview/pvw_obj_powerup.x");
	m_uiPowerTexture = CTextureManager::GetInstance().CreateTexture("textures/obj_powerup_invisible.png");

	m_uiTower1Model = CModelManager::GetInstance().CreateModel("models/preview/pvw_tower_base.x");
	m_uiTower2Model = CModelManager::GetInstance().CreateModel("models/preview/pvw_tower_turret.x");
	m_uiTowerNTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_neutral.png");
	m_uiTowerGTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_green.png");
	m_uiTowerPTexture = CTextureManager::GetInstance().CreateTexture("textures/tile_tower_purple.png");

	return (true);
}

/**
* 
* Process the rotation of the cube, then sets the viewport to draw to.
* 
* @author Daniel Jay
* @return void.
*/
void
CLevelPreviewer::Process(float32 _fDeltaTick)
{

	if(true == m_bIsActive)
	{
		//Process the cube moving animations if any
		m_fAngle += _fDeltaTick * LEVEL_CUBE_TURN_SPEED;

		D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_fAngle, D3DXToRadian(45.0f), D3DXToRadian(45.0f));
		
		//Add to the viewport
		CTotalCubeDomination::GetInstance().GetRenderer()->AddToViewport(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE, 0);
	}
}

/**
* 
* Sets the world matrix of the cube
* then gets the model and texture and draws them
* 
* @author Carsten Scholz
* @return void.
*/
void
CLevelPreviewer::Draw()
{
		// Grab the renderer.
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

	m_matWorld._41 = m_vec3Position.x;
	m_matWorld._42 = m_vec3Position.y;
	m_matWorld._43 = m_vec3Position.z;

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	pRenderer->SetWorldMatrix(m_matWorld);

	//Draw it
	CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
	CModelManager::GetInstance().Draw(s_uiModelID);

	D3DXMATRIX mat;
	TPreviewObject* pObj = 0;

	for (uint32 i = 0; i < m_vecObjects.size(); ++i)
	{
		pObj = m_vecObjects[i];

		mat = pObj->matWorld * m_matWorld;

		pRenderer->SetWorldMatrix(mat);

		CTextureManager::GetInstance().SetTexture(0, pObj->uiTexture);
		CModelManager::GetInstance().Draw(pObj->uiModel);
	}
}

void
CLevelPreviewer::LoadMap(const char *_kpcFileName)
{
	UnLoadMap();

	std::ifstream MapFile;

	MapFile.open(_kpcFileName, std::ios_base::binary);

	// Skip  map name and ambient colour
	MapFile.seekg(36, std::ios_base::beg);

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

			TPreviewObject* obj = new TPreviewObject;

			switch (uiTileType)
			{
				case FTILE_WALL:
				{
					obj->uiModel = m_uiWallModel;
					obj->uiTexture = m_uiWallTexture;
				}
				break;

				case FTILE_AMMO:
				{
					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							obj->uiModel = m_uiAmmoModel;
							obj->uiTexture = m_uiAmmoTexture;
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							obj->uiModel = m_uiAmmoModel;
							obj->uiTexture = m_uiAmmoTexture;
						}
						break;

						case FOWNER_NEUTRAL:
						{
							obj->uiModel = m_uiAmmoModel;
							obj->uiTexture = m_uiAmmoTexture;
						}
						break;
					}
				}
				break;

				case FTILE_BARRIER:
				{
					obj->uiModel = m_uiWallModel;
					obj->uiTexture = m_uiBBTexture;
				}
				break;

				case FTILE_FLAG_PLATE:
				{
					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							obj->uiModel = m_uiFlagModel;
							obj->uiTexture = m_uiFlagGTexture;
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							obj->uiModel = m_uiFlagModel;
							obj->uiTexture = m_uiFlagPTexture;
						}
						break;
					}
				}
				break;

				case FTILE_FLAME_GRATE:
				{
					obj->uiModel = m_uiFlatModel;
					obj->uiTexture = m_uiFlameTexture;
				}
				break;

				case FTILE_MAG_PLATE:
				{
					obj->uiModel = m_uiFlatModel;
					obj->uiTexture = m_uiMagTexture;
				}
				break;

				case FTILE_TOWER:
				{
					TPreviewObject* obj2 = new TPreviewObject;

					obj2->uiModel = m_uiTower2Model;
					obj->uiModel = m_uiTower1Model;

					switch (uiTileOwner)
					{
						case FOWNER_TEAM_GREEN:
						{
							obj2->uiTexture = m_uiTowerGTexture;
							obj->uiTexture = m_uiTowerGTexture;
						}
						break;

						case FOWNER_TEAM_PURPLE:
						{
							obj2->uiTexture = m_uiTowerPTexture;
							obj->uiTexture = m_uiTowerPTexture;
						}
						break;

						case FOWNER_NEUTRAL:
						{
							obj2->uiTexture = m_uiTowerNTexture;
							obj->uiTexture = m_uiTowerNTexture;
						}
						break;
					}

					D3DXVECTOR3 vec3Pos = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up * 5.25f;
					vec3Pos += g_atUpRightDirectionVecs[uiFaceNumber].vec3Right * ((uiTileX * 0.7f) - 4.9f);
					vec3Pos -= g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction * ((uiTileY * 0.7f) - 4.9f);

					D3DXMatrixIdentity(&obj2->matWorld);

					obj2->matWorld._11 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.x;
					obj2->matWorld._21 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.x;
					obj2->matWorld._31 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.x;
					obj2->matWorld._12 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.y;
					obj2->matWorld._22 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.y;
					obj2->matWorld._32 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.y;
					obj2->matWorld._13 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.z; 
					obj2->matWorld._23 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.z; 
					obj2->matWorld._33 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.z;
					obj2->matWorld._41 = vec3Pos.x;
					obj2->matWorld._42 = vec3Pos.y;
					obj2->matWorld._43 = vec3Pos.z;

					m_vecObjects.push_back(obj2);
				}
				break;

				case FTILE_POWER_SPAWN:
				{
					obj->uiModel = m_uiPowerModel;
					obj->uiTexture = m_uiPowerTexture;
				}
				break;

				default:
				{
					delete obj;
					obj = 0;
				}
				break;
			}

			if (!obj)
			{
				continue;
			}

			if (obj->uiTexture == 0xcccccccc)
			{
				int i = 0;
			}

			D3DXVECTOR3 vec3Pos = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up * 5.25f;
			vec3Pos += g_atUpRightDirectionVecs[uiFaceNumber].vec3Right * ((uiTileX * 0.7f) - 4.9f);
			vec3Pos -= g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction * ((uiTileY * 0.7f) - 4.9f);

			D3DXMatrixIdentity(&obj->matWorld);

			obj->matWorld._11 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.x;
			obj->matWorld._21 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.x;
			obj->matWorld._31 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.x;
			obj->matWorld._12 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.y;
			obj->matWorld._22 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.y;
			obj->matWorld._32 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.y;
			obj->matWorld._13 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Right.z; 
			obj->matWorld._23 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Up.z; 
			obj->matWorld._33 = g_atUpRightDirectionVecs[uiFaceNumber].vec3Direction.z;
			obj->matWorld._41 = vec3Pos.x;
			obj->matWorld._42 = vec3Pos.y;
			obj->matWorld._43 = vec3Pos.z;

			m_vecObjects.push_back(obj);
		}
	}

	MapFile.close();
}

void
CLevelPreviewer::UnLoadMap()
{
	for (uint32 i = 0; i < m_vecObjects.size(); ++i)
	{
		delete m_vecObjects[i];
	}

	m_vecObjects.clear();
}

D3DXMATRIX
CLevelPreviewer::GetWorldMatrix()
{
	return (m_matWorld);
}

/**
* 
* Resets to the state it needs to be in when entering the menu.
* 
* @author Rebeccah Cox
* @return void.
*/
void
CLevelPreviewer::Reset()
{
	//Initialise(m_vec3Position);
}
