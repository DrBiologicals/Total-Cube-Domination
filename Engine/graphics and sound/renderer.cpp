// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   renderer.cpp
//  Description :   renderer.cppfor implementation of renderer.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../viewport/viewport.h"
#include "modelmanager.h"
#include "texturemanager.h"
#include "spritemanager.h"
#include "lightmanager.h"
#include "../../entity structures/particle/emittermanager.h"
#include "fontmanager.h"
#include "billboardmanager.h"
#ifdef _DEBUG
#include "../../logutil.h"
#endif _DEBUG

// This Include
#include "renderer.h"

// Static Variables

// Static Function Prototypes

// Implementation
CRenderer::CRenderer()
: m_hWindow(0)
, m_pDirect3D(0)
, m_pDevice(0)
, m_iScreenWidth(0)
, m_iScreenHeight(0)
, m_ClearColour(0)
, m_bFullscreen(false)
{
}

CRenderer::~CRenderer()
{
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = 0;
	}

	if (m_pDirect3D)
	{
		m_pDirect3D->Release();
		m_pDirect3D = 0;
	}

	for (uint32 i = 0; i < m_vecViewports.size(); ++i)
	{
		delete m_vecViewports[i];
	}

	m_vecViewports.clear();
}

/**
*
* This function initialises the renderer
*
* @author Daniel Jay
* @param _hWindow A handle to the renderer's window
* @param _iHeight The height of the backbuffer
* @param _iWidth The width of the backbuffer
* @param _bFullScreen Whether the window is fullscreen or not
* @return The success or failure of the initialisation
*
*/
bool 
CRenderer::Initialise(HWND _hWindow, int32 _iWidth, int32 _iHeight, bool _bFullScreen)
{
	// Populate member data using parameters
	m_iScreenWidth = _iWidth;
	m_iScreenHeight = _iHeight;
	m_hWindow = _hWindow;
	m_bFullscreen = _bFullScreen;

	// Struct declarations
	D3DDISPLAYMODE CurrentMode;
	D3DCAPS9 DeviceCaps;

	memset(&CurrentMode, 0, sizeof(CurrentMode));
	memset(&DeviceCaps, 0, sizeof(DeviceCaps));
	memset(&m_D3DPresentParams, 0, sizeof(m_D3DPresentParams));

	// Create Direct3D Object
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_pDirect3D)
	{
#ifdef _DEBUG
		LogMessage("Direct3D interface creation failed", LOG_MESSAGE_INIT);
#endif // _DEBUG

		MessageBox(_hWindow, "Direct3D initialisation failed", "Error", MB_ICONERROR | MB_OK);

		return (false);
	}

	// Get information on the current default adapter
	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &CurrentMode);
	m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps);

	DWORD dwVertexProcessing = 0;

	if(DeviceCaps.VertexProcessingCaps != 0)
	{
		dwVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	}
	else
	{
		dwVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	m_D3DPresentParams.BackBufferHeight = m_iScreenHeight;
	m_D3DPresentParams.BackBufferWidth = m_iScreenWidth;
	m_D3DPresentParams.BackBufferCount = 1;
	m_D3DPresentParams.EnableAutoDepthStencil = TRUE;
	m_D3DPresentParams.AutoDepthStencilFormat = D3DFMT_D24X8;
	m_D3DPresentParams.hDeviceWindow = m_hWindow;
	m_D3DPresentParams.Windowed = !m_bFullscreen;
	m_D3DPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    //m_D3DPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if(m_bFullscreen)
	{
		m_D3DPresentParams.FullScreen_RefreshRateInHz = CurrentMode.RefreshRate;
		m_D3DPresentParams.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_D3DPresentParams.SwapEffect = D3DSWAPEFFECT_FLIP;
	}
	else
	{
		m_D3DPresentParams.BackBufferFormat = CurrentMode.Format;
	}

	// Check to see if the selected resolution is supported
	int32 iAdapterModes = m_pDirect3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, m_D3DPresentParams.BackBufferFormat);
	bool bResolutionSupported = false;

	for (int32 i = 0; i < iAdapterModes; ++i)
	{
		D3DDISPLAYMODE DisplayMode;

		memset(&DisplayMode, 0, sizeof(DisplayMode));

		m_pDirect3D->EnumAdapterModes(D3DADAPTER_DEFAULT, m_D3DPresentParams.BackBufferFormat, i, &DisplayMode);

		if ((m_iScreenWidth == static_cast<int32>(DisplayMode.Width)) &&
			(m_iScreenHeight == static_cast<int32>(DisplayMode.Height)))
		{
			bResolutionSupported = true;
		}
	}

	if (!bResolutionSupported)
	{
#ifdef _DEBUG
		LogMessage("Direct3D device creation failed: Unsupported resolution", LOG_MESSAGE_INIT);
#endif // _DEBUG

		return (false);
	}

	if(FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL, 
								m_hWindow,
								dwVertexProcessing,
								&m_D3DPresentParams,
								&m_pDevice)))
	{
#ifdef _DEBUG
		LogMessage("Direct3D device creation failed: Unknown error", LOG_MESSAGE_INIT);
#endif // _DEBUG

		return (false);
	}

	// Set render states
    m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, DeviceCaps.MaxAnisotropy);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//m_pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	//m_pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

    float32 f = 1.0f;

    m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)(&f));

	return(true);
}

#ifdef _DEBUG
void
CRenderer::Process(float32 _fDeltaTick)
{
    for (uint32 i = 0; i < m_vecViewports.size(); ++i)
    {
        m_vecViewports[i]->Process(_fDeltaTick);
    }
}
#endif // _DEBUG

/**
*
* This function sets the renderer's backbuffer clear colour
*
* @author Daniel Jay
* @param _fRed The red component of the colour
* @param _fGreen The green component of the colour
* @param _fBlue The blue component of the colour
*
*/
void
CRenderer::SetClearColour(float32 _fRed, float32 _fGreen, float32 _fBlue)
{
	m_ClearColour = D3DCOLOR_COLORVALUE(_fRed, _fGreen, _fBlue, 1.0f);
}

/**
*
* This function clears the renderer's buffers
*
* @author Daniel Jay
* @param _bTarget The red component of the colour
* @param _bDepth The green component of the colour
* @param _bStencil The blue component of the colour
*
*/
void 
CRenderer::Clear(bool _bTarget, bool _bDepth, bool _bStencil)
{
	DWORD dwClearFlags = 0;

	if(_bTarget)
	{
		dwClearFlags |= D3DCLEAR_TARGET;
	}
	
	if(_bDepth)
	{
		dwClearFlags |= D3DCLEAR_ZBUFFER;
	}

	if(_bStencil)
	{
		dwClearFlags |= D3DCLEAR_STENCIL;
	}

	m_pDevice->Clear( 0, 0, dwClearFlags, m_ClearColour, 1.0, 0);
}

/**
*
* This function sets the number of viewports for the renderer
*
* @author Daniel Jay
* @param _uiNumViewports The new number of viewports
*
*/
void 
CRenderer::SetNumViewports(uint32 _uiNumViewports)
{
	for (uint32 i = 0; i < m_vecViewports.size(); ++i)
	{
		delete m_vecViewports[i];
	}

	m_vecViewports.clear();

	for (uint32 i = 0; i < _uiNumViewports; ++i)
	{
		m_vecViewports.push_back(new CViewport);

		if (_uiNumViewports / 2 == 2)
		{
			// Four viewports
			m_vecViewports.back()->Initialise((i % 2) * (m_iScreenWidth / 2),
				(i / 2) * (m_iScreenHeight / 2), m_iScreenWidth / 2, m_iScreenHeight / 2);

			m_vecViewports.back()->SetSizeType(VIEWPORTSIZE_SMALL);
		}
		else if (_uiNumViewports / 2 == 1)
		{
			if (_uiNumViewports % 2)
			{
				// Three viewports
				if (!i)
				{
					// Top viewport
					m_vecViewports.back()->Initialise(0, 0, 
					m_iScreenWidth, m_iScreenHeight / 2);

					m_vecViewports.back()->SetSizeType(VIEWPORTSIZE_WIDE);
				}
				else
				{
					// Bottom viewport
					m_vecViewports.back()->Initialise(((i - 1) % 2) * (m_iScreenWidth / 2), 
						m_iScreenHeight / 2, m_iScreenWidth / 2, 
						m_iScreenHeight / 2);

					m_vecViewports.back()->SetSizeType(VIEWPORTSIZE_SMALL);
				}
			}
			else
			{
				// Two viewports
				m_vecViewports.back()->Initialise(0, i * (m_iScreenHeight / 2), 
					m_iScreenWidth, m_iScreenHeight / 2);

				m_vecViewports.back()->SetSizeType(VIEWPORTSIZE_WIDE);
			}
		}
		else
		{
			// One viewport
			m_vecViewports.back()->Initialise(0, 0, m_iScreenWidth, m_iScreenHeight);

			m_vecViewports.back()->SetSizeType(VIEWPORTSIZE_LARGE);
		}
	}
}

/**
*
* This function returns a pointer to the viewport at a certain index
*
* @author Daniel Jay
* @param _uiViewportIndex The index of the viewport
* @return A pointer to the viewport
*
*/
CViewport*
CRenderer::GetViewport(uint32 _uiViewportIndex)
{
    if (_uiViewportIndex < m_vecViewports.size())
    {
	    return (m_vecViewports[_uiViewportIndex]);
    }

    return (0);
}

/**
* 
* Returns the number of vieports.
* 
* @author Rebeccah Cox
* @return uint32 - size of m_vecViewports.
*/
uint32
CRenderer::GetNumViewports()
{
	return(static_cast<uint32>(m_vecViewports.size()));
}

/**
*
* This function adds an object to a viewport's render queue
*
* @author Daniel Jay
* @param _pEntity A pointer to the object
* @param _uiDrawFlags The render flags for the object
* @param _uiViewport The viewport's index
*
*/
void 
CRenderer::AddToViewport(CRenderEntity* _pEntity, uint32 _uiDrawFlags, uint32 _uiViewport)
{
	m_vecViewports[_uiViewport]->AddToViewport(_pEntity, _uiDrawFlags);
}

/**
*
* This function adds an object to all viewports' render queues
*
* @author Daniel Jay
* @param _pEntity A pointer to the object
* @param _uiDrawFlags The render flags for the object
*
*/
void 
CRenderer::AddToAllViewports(CRenderEntity* _pEntity, uint32 _uiDrawFlags)
{
	for (uint32 i = 0; i < m_vecViewports.size(); ++i)
	{
		m_vecViewports[i]->AddToViewport(_pEntity, _uiDrawFlags);
	}
}

/**
*
* This function starts the renderer's draw cycle
*
* @author Daniel Jay
*
*/
void 
CRenderer::StartRender()
{
	// Begin the render
	m_pDevice->BeginScene();
}

/**
*
* This function ends the renderer's draw cycle
*
* @author Daniel Jay
*
*/
void 
CRenderer::EndRender()
{
	m_pDevice->EndScene();

	// Present frame buffer
	if (m_pDevice->Present(0,0,0,0) == D3DERR_DEVICELOST)
	{
		CModelManager::GetInstance().OnDeviceLost();
		CTextureManager::GetInstance().OnDeviceLost();
		CFontManager::GetInstance().OnDeviceLost();
        CEmitterManager::GetInstance().OnDeviceLost();
        CLightManager::GetInstance().OnDeviceLost();
		CSpriteManager::GetInstance().OnDeviceLost();
		CBillboardManager::GetInstance().OnDeviceLost();

		while (m_pDevice->TestCooperativeLevel() != D3DERR_DEVICENOTRESET)
		{
			Sleep(250);
		}

		m_pDevice->Reset(&m_D3DPresentParams);

		CModelManager::GetInstance().OnDeviceReset();
		CTextureManager::GetInstance().OnDeviceReset();
		CFontManager::GetInstance().OnDeviceReset();
        CEmitterManager::GetInstance().OnDeviceReset();
        CLightManager::GetInstance().OnDeviceReset();
		CSpriteManager::GetInstance().OnDeviceReset();
		CBillboardManager::GetInstance().OnDeviceReset();
	    
		m_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

		float32 f = 1.0f;

		m_pDevice->SetRenderState(D3DRS_POINTSCALE_C, *(DWORD*)(&f));

        D3DMATERIAL9 material;

        ZeroMemory(&material, sizeof(material) );
        material.Ambient.a = 1.0f;
        material.Ambient.g = 1.0f;
        material.Ambient.r = 1.0f;
        material.Ambient.b = 1.0f;

        m_pDevice->SetMaterial(&material);
	}
}

/**
*
* This function renders the contents of all the renderer's viewports
*
* @author Daniel Jay
*
*/
void 
CRenderer::Render()
{
	StartRender();

	for (uint32 i = 0; i < m_vecViewports.size(); ++i)
	{
		m_vecViewports[i]->Draw(*this);
	}

	EndRender();
}

/**
*
* This function sets the renderer's world matrix
*
* @author Daniel Jay
* @param _rWorld A reference to the world matrix to set
*
*/
void 
CRenderer::SetWorldMatrix(const D3DXMATRIX& _rWorld)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &_rWorld);
}

/**
*
* This function sets the renderer's view matrix
*
* @author Daniel Jay
* @param _rView A reference to the view matrix to set
*
*/
void 
CRenderer::SetViewMatrix(const D3DXMATRIX& _rView)
{
	m_matView = _rView;
	m_pDevice->SetTransform(D3DTS_VIEW, &_rView);
}

/**
*
* This function sets the renderer's projection matrix
*
* @author Daniel Jay
* @param _rProjection A reference to the projection matrix to set
*
*/
void 
CRenderer::SetProjectionMatrix(const D3DXMATRIX& _rProjection)
{
	m_pDevice->SetTransform(D3DTS_PROJECTION, &_rProjection);
}

const D3DXMATRIX& 
CRenderer::GetViewMatrix() const
{
	return (m_matView);
}

LPDIRECT3DDEVICE9 
CRenderer::GetDevice()
{
	return(m_pDevice);
}

const int32
CRenderer::GetScreenWidth()
{
	return (m_iScreenWidth);
}

const int32
CRenderer::GetScreenHeight()
{
	return (m_iScreenHeight);
}
