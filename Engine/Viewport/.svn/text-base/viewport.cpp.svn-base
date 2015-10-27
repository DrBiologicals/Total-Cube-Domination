// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   viewport.cpp
//  Description :   viewport.cppfor implementation of viewport.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#ifdef _DEBUG
#include "debugcamera.h"
#else
#include "camera.h"
#endif // _DEBUG

#include "../graphics and sound/renderer.h"
#include "../../entity structures/renderentity.h"

// This Include
#include "viewport.h"

// Static Variables

// Static Function Prototypes

// Implementation

CViewport::CViewport()
: m_uiActiveCamera(BAD_ID)
, m_eSizeType(VIEWPORTSIZE_MAX)
{
	memset(&m_D3DViewport, 0, sizeof(m_D3DViewport));
}

CViewport::~CViewport()
{
	for(uint32 i = 0; i < m_vecCameras.size(); ++i)
	{
		delete m_vecCameras[i];
	}

	m_vecCameras.clear();
}

/**
*
* This function initialises the viewport
*
* @author Daniel Jay
* @param _uiX The x position of the viewport in screen coordinates
* @param _uiY The y position of the viewport in screen coordinates
* @param _uiWidth The width of the viewport in pixels
* @param _uiWidth The height of the viewport in pixels
* @return The success or failure of the initialisation
*
*/
bool 
CViewport::Initialise(uint32 _uiX,
				uint32 _uiY,
				uint32 _uiWidth,
				uint32 _uiHeight)
{
	//Create viewport struct
	m_D3DViewport.X = _uiX;
	m_D3DViewport.Y = _uiY;

	m_D3DViewport.Width = _uiWidth;
	m_D3DViewport.Height = _uiHeight;
	
	m_D3DViewport.MaxZ = 1.0f;
	m_D3DViewport.MinZ = 0.0f;

	return (true);
}

#ifdef _DEBUG
void
CViewport::Process(float32 _fDeltaTick)
{
    for (uint32 i = 0; i < m_vecCameras.size(); ++i)
    {
        m_vecCameras[i]->Process(_fDeltaTick);
    }
}
#endif // _DEBUG

/**
*
* This function adds an object to the viewport's render queue
*
* @author Daniel Jay
* @param _pEntity A pointer to the object
* @param _uiTypeFlags The render flags for the object
*
*/
void 
CViewport::AddToViewport(CRenderEntity* _pEntity, uint32 _uiTypeFlags)
{
	TRenderQueueItem tItem;
	tItem.m_pRenderEntity = _pEntity;
	tItem.m_uiFlags = _uiTypeFlags;

	/*const D3DXMATRIX& krmat = _pEntity->GetWorldMatrix();

	D3DXVECTOR3 vec3Position(krmat._41, krmat._42, krmat._43);

	D3DXVec3TransformCoord(&vec3Position, &vec3Position, &m_vecCameras[m_uiActiveCamera]->GetViewMatrix());

	tItem.m_fDepth = vec3Position.z;*/

	/*if (_uiTypeFlags & RENDERTYPE_SCREENALIGNED)
	{
		if (_uiTypeFlags & RENDERTYPE_ALPHABLEND)
		{
			const D3DXMATRIX& krmat = _pEntity->GetWorldMatrix();

			D3DXVECTOR3 vec3Position(krmat._41, krmat._42, krmat._43);

			vec3Position -= GetActiveCamera()->GetPosition();

			tItem.m_fDepth = D3DXVec3Dot(&vec3Position, &GetActiveCamera()->GetDirection());

			m_listScreenTransparentObjects.push_back(tItem);
		}
		else
		{
			m_listScreenOpaqueObjects.push_back(tItem);
		}
	}
	else
	{
		if (_uiTypeFlags & RENDERTYPE_ALPHABLEND)
		{
			const D3DXMATRIX& krmat = _pEntity->GetWorldMatrix();

			D3DXVECTOR3 vec3Position(krmat._41, krmat._42, krmat._43);

			vec3Position -= GetActiveCamera()->GetPosition();

			tItem.m_fDepth = D3DXVec3Dot(&vec3Position, &GetActiveCamera()->GetDirection());

			m_listTransparentObjects.push_back(tItem);
		}
		else
		{
			m_listOpaqueObjects.push_back(tItem);
		}
	}*/

	m_vecRenderQueue.push_back(tItem);
}

/**
*
* This function renders the contents of the viewport
*
* @author Daniel Jay
* @param _rRenderer A reference to the renderer
*
*/
void
CViewport::Draw(CRenderer& _rRenderer)
{
	// Abort the draw call if there is no active camera
	if (m_uiActiveCamera == BAD_ID)
	{
		/*m_listOpaqueObjects.clear();
		m_listTransparentObjects.clear();
		m_listScreenOpaqueObjects.clear();
		m_listScreenTransparentObjects.clear();*/

		return;
	}

	LPDIRECT3DDEVICE9 pDevice = _rRenderer.GetDevice();

	pDevice->SetViewport(&m_D3DViewport);

	_rRenderer.Clear(true, true, false);

	_rRenderer.SetViewMatrix(m_vecCameras[m_uiActiveCamera]->GetViewMatrix());
	_rRenderer.SetProjectionMatrix(m_vecCameras[m_uiActiveCamera]->GetProjectionMatrix());

	//m_listOpaqueObjects.sort();
	//m_listTransparentObjects.sort();
	//m_listScreenTransparentObjects.reverse();
	//m_listScreenOpaqueObjects.sort();
	//m_listScreenTransparentObjects.sort();
	//m_listScreenTransparentObjects.reverse();

	/*while (!m_listOpaqueObjects.empty())
	{
		m_queueRenderQueue.push(m_listOpaqueObjects.back().m_pRenderEntity);
		m_listOpaqueObjects.pop_back();
	}

	while (!m_listScreenTransparentObjects.empty())
	{
		m_queueRenderQueue.push(m_listScreenTransparentObjects.front().m_pRenderEntity);
		m_listScreenTransparentObjects.pop_front();
	}*/

	/*while (!m_listRenderQueue.empty())
	{
		m_listRenderQueue.front().m_pRenderEntity->Draw();

		m_listRenderQueue.pop_front();
	}*/

	std::sort(m_vecRenderQueue.begin(), m_vecRenderQueue.end());

	bool bAlphaItemsStarted = false;

	for (uint32 i = 0; i < m_vecRenderQueue.size(); ++i)
	{
		if (!bAlphaItemsStarted)
		{
			if (m_vecRenderQueue[i].m_uiFlags & RENDERTYPE_ALPHABLEND)
			{
				bAlphaItemsStarted = true;
				pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			}
		}

		m_vecRenderQueue[i].m_pRenderEntity->Draw();
	}

	if (bAlphaItemsStarted)
	{
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	m_vecRenderQueue.clear();
}

#ifdef _DEBUG
/**
*
* This function creates and initialises a camera associated with the viewport
*
* @author Daniel Jay
* @param _fFOV The camera's field of view in radians
* @param _fNearClip The camera's near clip plane distance
* @param _fFarClip The camera's far clip plane distance
* @param _bDebug 
* @return The ID of the created camera, or BAD_ID if the function failed
*
*/
uint32
CViewport::CreateCamera(float32 _fFOV, float32 _fNearClip, float32 _fFarClip, bool _bDebug)
{
	// Create new camera
    CCamera* pCamera = 0;

    if (!_bDebug)
    {
	    pCamera = new CCamera;
    }
    else
    {
        pCamera = new CDebugCamera;
    }

	// Initialise the camera
	uint32 uiCameraID = static_cast<uint32>(m_vecCameras.size());

	if (!pCamera->Initialise(this, _fFOV, _fNearClip, _fFarClip, uiCameraID))
	{
		delete pCamera;
		pCamera = 0;

		return (BAD_ID);
	}

	m_vecCameras.push_back(pCamera);

	if (m_uiActiveCamera == BAD_ID)
	{
		m_uiActiveCamera = uiCameraID;
	}

	//Return the camera
	return (uiCameraID);
}
#else
/**
*
* This function creates and initialises a camera associated with the viewport
*
* @author Daniel Jay
* @param _fFOV The camera's field of view in radians
* @param _fNearClip The camera's near clip plane distance
* @param _fFarClip The camera's far clip plane distance
* @return The ID of the created camera, or BAD_ID if the function failed
*
*/
uint32
CViewport::CreateCamera(float32 _fFOV,
					float32 _fNearClip,
					float32 _fFarClip)
{
	//Create new camera.
	CCamera* pCamera = new CCamera;

	//Initialise the camera.
	uint32 uiCameraID = static_cast<uint32>(m_vecCameras.size());

	if (!pCamera->Initialise(this, _fFOV, _fNearClip, _fFarClip, uiCameraID))
	{
		delete pCamera;
		pCamera = 0;

		return (BAD_ID);
	}

	m_vecCameras.push_back(pCamera);

	if (m_uiActiveCamera == BAD_ID)
	{
		m_uiActiveCamera = uiCameraID;
	}

	//Return the camera
	return (uiCameraID);
}
#endif // _DEBUG

/**
*
* This function returns a pointer to the camera associated with an ID
*
* @author Daniel Jay
* @param _uiCameraID The ID of the camera
* @return A pointer to the camera
*
*/
CCamera* 
CViewport::GetCamera(uint32 _uiCameraID)
{
	return (m_vecCameras[_uiCameraID]);
}

/**
*
* This function sets which of its cameras the viewport is using
*
* @author Daniel Jay
* @param _uiCameraID The ID of the camera to use
*
*/
void 
CViewport::SetActiveCamera(uint32 _uiCameraID)
{
	m_uiActiveCamera = _uiCameraID;
}

/**
*
* This function returns a pointer to the active camera for the viewport
*
* @author Daniel Jay
* @return A pointer to the active camera
*
*/
CCamera* 
CViewport::GetActiveCamera()
{
	return (m_vecCameras[m_uiActiveCamera]);
}

/**
*
* This function returns a pointer to the viewport's D3D viewport struct
*
* @author Daniel Jay
* @return A pointer to the D3D viewport struct
*
*/
D3DVIEWPORT9* 
CViewport::GetD3DViewport()
{
	return (&m_D3DViewport);
}

/**
*
* This function returns the width of the viewport
*
* @author Daniel Jay
* @return The width of the viewport
*
*/
uint32
CViewport::GetWidth() const
{
	return (m_D3DViewport.Width);
}

/**
*
* This function returns the height of the viewport
*
* @author Daniel Jay
* @return The height of the viewport
*
*/
uint32
CViewport::GetHeight() const
{
	return (m_D3DViewport.Height);
}

/**
*
* This function returns the x position of the viewport
*
* @author Daniel Jay
* @return The x position of the viewport
*
*/
uint32
CViewport::GetPosX() const
{
	return (m_D3DViewport.X);
}

/**
*
* This function returns the y position of the viewport
*
* @author Daniel Jay
* @return The y position of the viewport
*
*/
uint32
CViewport::GetPosY() const
{
	return (m_D3DViewport.Y);
}


/**
* 
* Used in test harness manager, to call clear func on temp objects.
* 
* @author Rebeccah Cox
*/
void
CViewport::ClearRenderQueue()
{
	m_vecRenderQueue.clear();
}

void
CViewport::SetSizeType(EViewportSize _eSizeType)
{
	m_eSizeType = _eSizeType;
}

EViewportSize
CViewport::GetSizeType()
{
	return (m_eSizeType);
}
