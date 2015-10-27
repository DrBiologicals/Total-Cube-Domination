//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   fixedcamera.h
//  Description :   fixedcamera declaration (header) file.
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#pragma once

#if !defined(__IGFEB10_IG300_FIXEDCAMERA_H__)
#define __IGFEB10_IG300_FIXEDCAMERA_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../../defines.h"

// Types

// Constants

// Prototypes
class CViewport;

class CCamera
{
    // Member Functions
public:
	CCamera();
	virtual ~CCamera();

	bool Initialise(CViewport *_pViewPort, float32 _fFOV,
								float32 _fNearClip, float32 _fFarClip, uint32 _uiID);

	virtual void Process(float32 _fDeltaTick);

	void SetClipPlanes(float32 _fNear, float32 _fFar);

	void SetFOV(float32 _fFOV);

	void SetView3D(const D3DXVECTOR3& _rvectRight,
						const D3DXVECTOR3& _rvectUp,
						const D3DXVECTOR3& _rvectDir,
						const D3DXVECTOR3& _rvectPos);

	void SetViewQuaternion(const D3DXVECTOR3& _krvec3Position,
		const D3DXQUATERNION& _krquatRotation);

	void ResetMatrices();

	void SetPosition(const D3DXVECTOR3& _krvec3Position);
	const D3DXVECTOR3& GetPosition() const;

	const D3DXVECTOR3& GetDirection() const;

	const D3DXMATRIX& GetProjectionMatrix() const;
	const D3DXMATRIX& GetViewMatrix() const;

	CViewport* GetViewport();

protected:

private:

    // Member Variables
public:

protected:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProjection;

	uint32 m_uiID;

	float32 m_fFOV;

	float32 m_fNear;
	float32 m_fFar;

	float32 m_fYaw;
	float32 m_fPitch;
	float32 m_fRoll;

	D3DXVECTOR3 m_vec3Right;
	D3DXVECTOR3 m_vec3Up;
	D3DXVECTOR3 m_vec3Look;
	D3DXVECTOR3 m_vec3Position;

	CViewport* m_pViewport;

private:
	
};

#endif // __IGFEB10_IG300_FIXEDCAMERA_H__


