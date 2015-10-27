// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flagparticleemitter.cpp
//  Description :   flagparticleemitter.cppfor implementation of flagparticleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../defines.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "emittermanager.h"
#include "../terrain objects/flag.h"

// This Includes
#include "particle.h"
#include "flagparticleemitter.h"

// Static Variables
uint32 CFlagParticleEmitter::s_uiTextureID = BAD_ID;

// Static Function Prototypes


// Implementation
CFlagParticleEmitter::CFlagParticleEmitter()
: m_eFace(FACE_NONE)
, m_pFlag(0)
, m_fSpawnTimer(0.0f)
{

}

CFlagParticleEmitter::~CFlagParticleEmitter()
{
	m_pFlag = 0;
}

/*
* 
* @author Michael McQuarrie
* @param _iNumPaticles The number of particles wanted
* @param _vec3Origin the origin of the emitter
* @param _pFlag The flag that owns it
* @return true when done
*/
bool
CFlagParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, CFlag* _pFlag)
{
	// set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

	m_pFlag = _pFlag;

	m_fEmitRate = 0.2f;

	m_vec3Origin = _vec3Origin;

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

    // create the vertex buffer
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticleSize),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);

	D3DXMatrixIdentity(&m_matWorld);

	AddParticle();

	/*m_matWorld._41 = m_pFlag->GetWorldMatrix()._41;
	m_matWorld._42 = m_pFlag->GetWorldMatrix()._42;
	m_matWorld._43 = m_pFlag->GetWorldMatrix()._43;*/

	D3DXMatrixIdentity(&m_matWorld);
		
    CEntity::Initialise();

	return (true);
}

/*
* 
* @author Michael McQuarrie
* @param _fDeltaTick 
* @return void
*/
void
CFlagParticleEmitter::Process(float32 _fDeltaTick)
{
	m_vec3Origin = m_pFlag->GetPosition();

	if (m_dwVertexBufferSize > m_vecParticles.size())
	{
		m_fSpawnTimer += _fDeltaTick;
		if (m_fSpawnTimer > m_fEmitRate)
		{
			m_fSpawnTimer = 0.0f;
			//Adding particles to the emitter
			AddParticle();
		}
	}
	//Check if particles are still alive
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if(iter->bAlive)
		{
			//Adding the velocity to move the particles
			iter->vec3Position += iter->vec3Velocity * _fDeltaTick * 5.0f;

			iter->colour.a = 1.0f - iter->fLifeTime;

			//Adding to the life counter
			iter->fLifeTime += _fDeltaTick;
			if(iter->fAge <= iter->fLifeTime)
			{
				m_fSpawnTimer += _fDeltaTick;
				if (m_fSpawnTimer >= m_fEmitRate)
				{
					m_fSpawnTimer = 0.0f;
					iter->fLifeTime = 0.0f;
					Resetparticle(&(*iter));
				}
			}
		}
	}
	
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);

	//Lastly Remove the dead particles
	CheckAlive();
}

/*
* 
* @author Michael McQuarrie
* @param _pParticle The particle that needs to be reset
* @return void
*/
void
CFlagParticleEmitter::Resetparticle(TParticle *_pParticle)
{
	//Initalise origin

	_pParticle->vec3Position = m_vec3Origin += m_pFlag->GetUp() * 4.18f;

	float32 fAngleHor = D3DXToRadian(rand() % 360);
	float32 fAngleVer = -D3DXToRadian((rand() % 61) + 60);

	D3DXMATRIX yawMat;
	D3DXMATRIX pitchMat;

	D3DXMatrixRotationAxis(&yawMat, &m_pFlag->GetUp(), fAngleHor);
	D3DXMatrixRotationAxis(&pitchMat, &m_pFlag->GetRight(), fAngleVer);

	_pParticle->vec3Velocity = m_pFlag->GetDirection();

	D3DXVec3TransformCoord(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity, &pitchMat);
	D3DXVec3TransformCoord(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity, &yawMat);
	//Setting it

    D3DXVec3Normalize(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity);

	_pParticle->vec3Velocity += m_pFlag->GetUp();

	//Setting the life timer
	_pParticle->fAge = 1.0f;
	_pParticle->fLifeTime = 0.0f;
	_pParticle->colour = (m_pFlag->GetTeam() == TEAM_GREEN)?(KCOLTEAM_GREEN):(KCOLTEAM_PURPLE);
    _pParticle->bAlive = true;

}

/*
*	Adds a particle to the vector 
*
* @author Michael McQuarrie
* 
* @return void
*/
void
CFlagParticleEmitter::AddParticle()
{
	TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* Sets the states for particles 
*
* @author Michael McQuarrie
* 
* @return void
*/
void
CFlagParticleEmitter::PreDraw()
{
	// Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

	//float32 fSize = 4.0f;

	//pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
/*
* Draws the particles
*
* @author Michael McQuarrie
* 
* @return void
*/
void
CFlagParticleEmitter::Draw()
{
	if (!m_pVertexBuffer)
    {
        return;
    }
	if (!IsEmpty() )
	{
		//First PreDraw it
		TVertexParticleSize* pv;
		DWORD dwNumParticlesInBatch = 0;
		PreDraw();

		//Get the renderer 
        CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

		//Get the texture
        CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);

		//Set Matrix
        pRenderer->SetWorldMatrix(m_matWorld);

		//Set FVF and source things
		pRenderer->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE);
		pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TVertexParticleSize) );

		SortParticles();

		m_pVertexBuffer->Lock(NULL, 0, (void**)&pv, D3DLOCK_DISCARD);

		//Doing colour things
		for (int32 i = 0; i < static_cast<int32>(m_vecParticles.size() ); ++i)
		{
			if (m_vecParticles[i].bAlive)
			{
				pv->vec3Position = m_vecParticles[i].vec3Position;
				const D3DXCOLOR& kr = m_vecParticles[i].colour;
				pv->colour = D3DCOLOR_COLORVALUE(kr.r, kr.g, kr.b, 1.0f - kr.a);
				pv->fsize = m_vecParticles[i].fLifeTime + 0.5f;
				pv++;
				++dwNumParticlesInBatch;
			}
			
		}
		m_pVertexBuffer->Unlock();
		//Draw it 
		if (IsAlive() == true)
		{
			pRenderer->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesInBatch);
		}
		//End the drawing
		PostDraw();
	}
}
/*
* Shutdown the states for particles 
*
* @author Michael McQuarrie
* 
* @return void
*/
void
CFlagParticleEmitter::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	//float32 fSize = 1.0f;

	//pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* Sets the states for particles 
*
* @author Michael McQuarrie
* 
* @return void
*/
bool
CFlagParticleEmitter::CheckAlive()
{
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if(iter->bAlive)
		{
			SetAlive(true);
			break;
		}
		else
		{
			SetAlive(false);
		}
	}

	return(IsAlive());
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CFlagParticleEmitter::OnDeviceLost()
{
    if (m_pVertexBuffer)
    {
        m_pVertexBuffer->Release();
        m_pVertexBuffer = 0;
    }
}

/*
* OnDeviceReset
* @author Rigardt de Vries
* @return void
*/
void
CFlagParticleEmitter::OnDeviceReset()
{
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticleSize),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);
}

/*
* Sets the alive state
*
* @author Michael McQuarrie
* 
* @return void
*/
void
CFlagParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

void 
CFlagParticleEmitter::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}
