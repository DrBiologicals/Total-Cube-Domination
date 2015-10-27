//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   viewport.h
//  Description :   viewport declaration (header) file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#pragma once

#if !defined(__IGFEB10_IG300_VIEWPORT_H__)
#define __IGFEB10_IG300_VIEWPORT_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <list>
#include <queue>

// Local Includes

// Types
enum EViewportSize
{
	VIEWPORTSIZE_SMALL,
	VIEWPORTSIZE_WIDE,
	VIEWPORTSIZE_LARGE,
	VIEWPORTSIZE_MAX
};

// Constants

// Prototypes
class CRenderEntity;
class CCamera;
class CRenderer;

struct TRenderQueueItem
{
	CRenderEntity* m_pRenderEntity;
	float32 m_fDepth;
	uint32 m_uiFlags;

	bool operator<(const TRenderQueueItem& _kr)
	{
		if (!(m_uiFlags & RENDERTYPE_ALPHABLEND) && _kr.m_uiFlags & RENDERTYPE_ALPHABLEND)
		{
			return (true);
		}
		/*else if (m_uiFlags & RENDERTYPE_ALPHABLEND && !(_kr.m_uiFlags & RENDERTYPE_ALPHABLEND))
		{
			return (false);
		}
		else if (m_uiFlags & RENDERTYPE_ALPHABLEND && _kr.m_uiFlags & RENDERTYPE_ALPHABLEND)
		{
			return (m_fDepth > _kr.m_fDepth);
		}
		else if (!(m_uiFlags & RENDERTYPE_ALPHABLEND || _kr.m_uiFlags & RENDERTYPE_ALPHABLEND))
		{
			return (m_fDepth < _kr.m_fDepth);
		}*/

		return (false);
	}
};

class CViewport
{
    // Member Functions
public:
	CViewport();
	~CViewport();

	bool Initialise(uint32 _uiX,
					uint32 _uiY,
					uint32 _uiWidth,
					uint32 _uiHeight);

#ifdef _DEBUG
    void Process(float32 _fDeltaTick);
#endif // _DEBUG

	void AddToViewport(CRenderEntity* _pEntity, uint32 _uiTypeFlags);

	void Draw(CRenderer& _rRenderer);

#ifdef _DEBUG
    uint32 CreateCamera(float32 _fFOV, float32 _fNearClip, float32 _fFarClip, bool bDebug = false);
#else
    uint32 CreateCamera(float32 _fFOV, float32 _fNearClip, float32 _fFarClip);
#endif // _DEBUG

	CCamera* GetCamera(uint32 _uiCameraID);

	void SetActiveCamera(uint32 _uiCameraID);
	CCamera* GetActiveCamera();

	D3DVIEWPORT9* GetD3DViewport();

	uint32 GetWidth() const;
	uint32 GetHeight() const;
	
	uint32 GetPosX() const;
	uint32 GetPosY() const;

	//Used in test harness manager.
	void ClearRenderQueue();

	void SetSizeType(EViewportSize _eSizeType);
	EViewportSize GetSizeType();

protected:

private:

    // Member Variables
public:

protected:
	D3DVIEWPORT9 m_D3DViewport;

	uint32 m_uiActiveCamera;

	std::vector<CCamera*> m_vecCameras;

	//std::list<TRenderQueueItem> m_listRenderQueue;
	/*std::list<TRenderQueueItem> m_listTransparentObjects;
	std::list<TRenderQueueItem> m_listScreenOpaqueObjects;
	std::list<TRenderQueueItem> m_listScreenTransparentObjects;
*/
	//std::queue<CRenderEntity*> m_queueRenderQueue;

	std::vector<TRenderQueueItem> m_vecRenderQueue;

	EViewportSize m_eSizeType;

private:

};

#endif // __IGFEB10_IG300_VIEWPORT_H__