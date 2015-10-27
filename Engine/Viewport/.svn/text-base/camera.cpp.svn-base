// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   camera.cpp
//  Description :   camera.cppfor implementation of camera.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "viewport.h"

// This Includes
#include "camera.h"

// Static Variables

// Static Function Prototypes


// Implementation

CCamera::CCamera()
: m_fFar(0.0f)
, m_fFOV(0.0f)
, m_fNear(0.0f)
, m_uiID(BAD_ID)
, m_pViewport(0)
, m_fYaw(0.0f)
, m_fRoll(0.0f)
, m_fPitch(0.0f)
{
    m_vec3Look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
    m_vec3Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_vec3Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
    m_vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXMatrixIdentity(&m_matView);
    D3DXMatrixIdentity(&m_matProjection);
}

CCamera::~CCamera()
{
}

/*
* Initialise
* @author Rigardt de Vries
* @param _pViewPort		owning viewport
* @param _fFOV			field of view
* @param _eMode			camera mode
* @param _fNearClip		near clip plane
* @param _fFarClip		far clip plane
* @param _uiID			camera ID
* @return bool
*/
bool
CCamera::Initialise(CViewport* _pViewport, float32 _fFOV, 
				float32 _fNearClip, float32 _fFarClip, uint32 _uiID)
{
	if (!_pViewport)
	{
		return (false);
	}

	m_pViewport = _pViewport;

	m_fFar = _fFarClip;
	m_fNear = _fNearClip;
	m_fFOV = _fFOV;
	m_uiID = _uiID;

	ResetMatrices();

	return (true);
}

/*
* Process
* @author Rigardt de Vries
* @param _fDeltaTick	game timer
* @return void
*/
void 
CCamera::Process(float32 _fDeltaTick)
{
}

/*
* SetFOV
* @author Rigardt de Vries
* @param _fFOV			file of view
* @return void
*/
void 
CCamera::SetFOV(float32 _fFOV)
{
	m_fFOV = _fFOV;

	ResetMatrices();
}

/*
* SetClipPlanes
* @author Rigardt de Vries
* @param _fNear		the near clip plane
* @param _fFar		the far clip plane
* @return void
*/
void 
CCamera::SetClipPlanes(float32 _fNear, float32 _fFar)
{
	m_fNear = _fNear;
	m_fFar = _fFar;

	ResetMatrices();
}

/*
* ResetMatrices
* @author Rigardt de Vries
* @return void
*/
void 
CCamera::ResetMatrices()
{
	float32 fAspectRatio = static_cast<float32>(m_pViewport->GetWidth()) / static_cast<float32>(m_pViewport->GetHeight());

	D3DXMatrixPerspectiveFovLH(&m_matProjection, m_fFOV, fAspectRatio, m_fNear, m_fFar);
}

/*
* SetView3D
* @author Rigardt de Vries
* @param _rvectRight	the right vector
* @param _rvectUP		the up vector
* @param _rvectDir		the direction vector
* @param _rvectPos		the position vector
* @return void
*/
void 
CCamera::SetView3D(const D3DXVECTOR3& _krvec3Right, 
					const D3DXVECTOR3& _krvec3Up, 
					const D3DXVECTOR3& _krvec3Dir, 
					const D3DXVECTOR3& _krvec3Pos)
{
    m_vec3Look = _krvec3Dir;
    m_vec3Up = _krvec3Up;
    m_vec3Right = _krvec3Right;
    m_vec3Position = _krvec3Pos;
	
    m_matView._11 = m_vec3Right.x;
    m_matView._21 = m_vec3Right.y;
    m_matView._31 = m_vec3Right.z;
    m_matView._41 = -D3DXVec3Dot(&m_vec3Right, &m_vec3Position);

    m_matView._12 = m_vec3Up.x;
    m_matView._22 = m_vec3Up.y;
    m_matView._32 = m_vec3Up.z;
    m_matView._42 = -D3DXVec3Dot(&m_vec3Up, &m_vec3Position);

    m_matView._13 = m_vec3Look.x;
    m_matView._23 = m_vec3Look.y;
    m_matView._33 = m_vec3Look.z;
    m_matView._43 = -D3DXVec3Dot(&m_vec3Look, &m_vec3Position);
}

void 
CCamera::SetViewQuaternion(const D3DXVECTOR3& _krvec3Position, const D3DXQUATERNION& _krquatRotation)
{
	m_vec3Position = _krvec3Position;

	D3DXMATRIX mat;
	D3DXMatrixRotationQuaternion(&mat, &_krquatRotation);

	D3DXVec3TransformCoord(&m_vec3Look, &g_atUpRightDirectionVecs[FACE_TOP].vec3Direction, &mat);
	D3DXVec3TransformCoord(&m_vec3Up, &g_atUpRightDirectionVecs[FACE_TOP].vec3Up, &mat);
	D3DXVec3TransformCoord(&m_vec3Right, &g_atUpRightDirectionVecs[FACE_TOP].vec3Right, &mat);

	D3DXMatrixTransformation(&m_matView, 0, 0, 0, 0, &_krquatRotation, &_krvec3Position);
	D3DXMatrixInverse(&m_matView, 0, &m_matView);
}

/*
* GetPosition
* @author Rigardt de Vries
* @return D3DXVECTOR3&
*/
const D3DXVECTOR3&
CCamera::GetPosition() const
{
	return (m_vec3Position);
}

const D3DXVECTOR3&
CCamera::GetDirection() const
{
	return (m_vec3Look);
}

/*
* GetProjMatrix
* @author Rigardt de Vries
* @return D3DXMATRIX*
*/
const D3DXMATRIX&
CCamera::GetProjectionMatrix() const
{
	return (m_matProjection);
}

const D3DXMATRIX& 
CCamera::GetViewMatrix() const
{
	return (m_matView);
}

CViewport*
CCamera::GetViewport()
{
	return (m_pViewport);
}
