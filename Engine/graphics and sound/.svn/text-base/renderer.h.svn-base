// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   renderer.h
//  Description :   Declaration for Crenderer
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_RENDERER_H__
#define __IGFEB10_MODULE_RENDERER_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

// Local Includes

// Types

// Prototypes
class CViewport;
class CRenderEntity;

class CRenderer
{
	// Member Functions
public:
	CRenderer();
	~CRenderer();

	bool Initialise(HWND _hGameWindow, int32 _iWidth, int32 _iHeight, bool _bFullscreen);

	void SetClearColour(float32 _fRed, float32 _fGreen, float32 _fBlue);

	void Clear(bool _bTarget, bool _bDepth, bool _bStencil);

	void SetNumViewports(uint32 _uiNumViewports);
	CViewport* GetViewport(uint32 _uiViewportIndex);
	uint32 GetNumViewports();

	void AddToViewport(CRenderEntity* _pEntity, uint32 _uiDrawFlags, uint32 _uiViewport);
	void AddToAllViewports(CRenderEntity* _pEntity, uint32 _uiDrawFlags);

	void StartRender();
	void EndRender();

	void Render();

#ifdef _DEBUG
    void Process(float32 _fDeltaTick);
#endif // _DEBUG

	void SetWorldMatrix(const D3DXMATRIX& _rWorld);
	void SetViewMatrix(const D3DXMATRIX& _rView);
	void SetProjectionMatrix(const D3DXMATRIX& _rProjection);

	const D3DXMATRIX& GetViewMatrix() const;

	LPDIRECT3DDEVICE9 GetDevice();

	const int32 GetScreenWidth();
	const int32 GetScreenHeight();

protected:

private:

	// Member Variables
public:

protected:
	D3DXMATRIX m_matView;

	HWND m_hWindow;

	LPDIRECT3D9 m_pDirect3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	
	D3DCOLOR m_ClearColour;

	int32 m_iScreenWidth;
	int32 m_iScreenHeight;

	D3DPRESENT_PARAMETERS m_D3DPresentParams;

	std::vector<CViewport*> m_vecViewports;

	bool m_bFullscreen;

private:

}; 

#endif // __IGFEB10_MODULE_RENDERER_H__

