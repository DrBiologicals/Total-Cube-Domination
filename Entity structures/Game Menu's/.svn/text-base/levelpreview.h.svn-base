// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   levelpreview.h
//  Description :   Declaration for Clevelpreview
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_LEVELPREVIEW_H__
#define __IGFEB10_MODULE_LEVELPREVIEW_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

// Local Includes
#include "../renderentity.h"
#include "menuitem.h"
//#include "../../angle.h"

// Types
const float32 LEVEL_CUBE_TURN_SPEED = 0.45f;

struct TPreviewObject
{
	uint32 uiModel;
	uint32 uiTexture;
	D3DXMATRIX matWorld;
};

// Prototypes
class CLevelPreviewer : public CMenuItem
{
	// Member Functions
public:
	CLevelPreviewer();
	~CLevelPreviewer();

	bool Initialise(D3DXVECTOR3 _vec3Position);

	void Process(float32 _fDeltaTick);
	void Draw();

	void LoadMap(const char* _kpcFileName);
	void UnLoadMap();

	D3DXMATRIX GetWorldMatrix();

	virtual void Reset();

protected:

private:

	// Member Variables
public:

protected:
	D3DXVECTOR3 m_vec3Position;

	std::vector<TPreviewObject*> m_vecObjects;

	static uint32 s_uiModelID;
	static uint32 s_uiTextureID;

	uint32 m_uiWallTexture;
	uint32 m_uiBBTexture;
	uint32 m_uiWallModel;
	uint32 m_uiAmmoModel;
	uint32 m_uiAmmoTexture;
	uint32 m_uiFlagModel;
	uint32 m_uiFlagPTexture;
	uint32 m_uiFlagGTexture;
	uint32 m_uiFlatModel;
	uint32 m_uiFlameTexture;
	uint32 m_uiMagTexture;
	uint32 m_uiPowerModel;
	uint32 m_uiPowerTexture;
	uint32 m_uiTower1Model;
	uint32 m_uiTower2Model;
	uint32 m_uiTowerNTexture;
	uint32 m_uiTowerGTexture;
	uint32 m_uiTowerPTexture;

	float32 m_fAngle;

private:

}; 

#endif // __IGFEB10_MODULE_LEVELPREVIEW_H__

