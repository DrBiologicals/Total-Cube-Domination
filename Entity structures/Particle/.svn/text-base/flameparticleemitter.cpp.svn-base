// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flameparticleemitter.cpp
//  Description :   flameparticleemitter.cppfor implementation of flameparticleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../terrain objects/flamegrate.h"
#include "emittermanager.h"

// This Includes
#include "flameparticleemitter.h"
#include "particle.h"

// Static Variables
uint32 CFlameParticleEmitter::s_uiTextureID = BAD_ID;

// Static Function Prototypes

// Implementation

CFlameParticleEmitter::CFlameParticleEmitter()
: m_pFlameplate(0)
, m_fSpawnTimer(0.0f)
{
}

CFlameParticleEmitter::~CFlameParticleEmitter()
{
	m_pFlameplate = 0;
}

/*
* initialise
* @author Rigardt de Vries
* @param _iNumParticles				the number of particles for the emitter
* @param _vec3Origin				the origin of the emitter
* @param _eType						the type of particle emitter
* @return
*/
bool
CFlameParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, CFlameGrate* pFlamePlate)
{
	// set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

    m_vec3Origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

    // create the vertex buffer
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticle),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);

	D3DXMatrixIdentity(&m_matWorld);

	m_pFlameplate = pFlamePlate;

	m_matWorld._41 = _vec3Origin.x;
	m_matWorld._42 = _vec3Origin.y;
	m_matWorld._43 = _vec3Origin.z;

	if (_vec3Origin.x == 22.5f)
	{
		m_eFace = FACE_RIGHT;
	}
	else if (_vec3Origin.x == -22.5f)
	{
		m_eFace = FACE_LEFT;
	}
	else if (_vec3Origin.y == 22.5f)
	{
		m_eFace = FACE_TOP;
	}
	else if (_vec3Origin.y == -22.5f)
	{
		m_eFace = FACE_BOTTOM;
	}
	else if (_vec3Origin.z == 22.5f)
	{
		m_eFace = FACE_BACK;
	}
	else if (_vec3Origin.z == -22.5f)
	{
		m_eFace = FACE_FRONT;
	}
		
    CEntity::Initialise();

    m_fEmitRate = 0.3f;

	return (true);
}

/*
* AddParticle
* @author Rigardt de Vries
* @return void
*/
void
CFlameParticleEmitter::AddParticle()
{
	TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* ResetParticle
* @author Rigardt de vries
* @param _pParticle			the particle that has to be reset.
* @return void
*/
void
CFlameParticleEmitter::Resetparticle(TParticle *_pParticle)
{
	//Initalise origin
	_pParticle->vec3Position = m_vec3Origin;

	//Set to alive
	_pParticle->bAlive = true;

	//Setting it
	_pParticle->vec3Velocity = g_atUpRightDirectionVecs[m_eFace].vec3Up;

    //D3DXVec3Normalize(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity);

	//Setting the life timer
	_pParticle->fAge = 0.6f;
	_pParticle->fLifeTime = 0.0f ;
	_pParticle->vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_eFace == FACE_TOP || m_eFace == FACE_BOTTOM)
	{
		_pParticle->vec3Position.x = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
		_pParticle->vec3Position.z = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
	}
	else if (m_eFace == FACE_LEFT || m_eFace == FACE_RIGHT)
	{
		_pParticle->vec3Position.z = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
		_pParticle->vec3Position.y = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
	}
	else if (m_eFace == FACE_BACK || m_eFace == FACE_FRONT)
	{
		_pParticle->vec3Position.y = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
		_pParticle->vec3Position.x = (static_cast<float32>(rand() % 301) * 0.01f) - 1.5f;
	}

	_pParticle->colour = KCOLYELLOW;
}

/*
* Process
* @author Rigardt de Vries
* @param _fDeltaTick			the game timer
* @return void
*/
void
CFlameParticleEmitter::Process(float32 _fDeltaTick)
{
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

	//Check if particles are still emmiting
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if (m_pFlameplate->GetActive() == true)
		{
			if (iter->bAlive == false)
			{
				m_fSpawnTimer += _fDeltaTick;
				if (m_fSpawnTimer > m_fEmitRate)
				{
					m_fSpawnTimer = 0.0f;
					
					iter->bAlive = true;
				}
				
			}
		}
		if(iter->bAlive)
		{
			//Adding the velocity to move the particles
            iter->vec3Position += iter->vec3Velocity * _fDeltaTick * 8.0f;

			if (iter->fLifeTime < 0.3f)
			{
				D3DXColorLerp(&iter->colour, &KCOLYELLOW, &KCOLRED, iter->fLifeTime * 3.333333f);
			}
			else
			{
				D3DXColorLerp(&iter->colour, &KCOLRED, &KCOLGREY, (iter->fLifeTime - 0.3f) * 3.333333f);
			}

			//Adding to the life counter
			iter->fLifeTime += _fDeltaTick;
			if(iter->fAge <= iter->fLifeTime)
			{
				if (m_pFlameplate->GetActive() == true)
				{
					Resetparticle(&(*iter));
				}
				else
				{
					iter->bAlive = false;
				}
			}
		}
	}
	
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);

	//Lastly Remove the dead particles
	CheckAlive();
}

/*
* PreDraw
* @author Rigardt de Vries
* @return void
*/
void
CFlameParticleEmitter::PreDraw()
{
	// Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

	float32 fSize = 2.0f;

	pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

/*
* Draw
* @author Rigardt de Vries
* @return void
*/
void
CFlameParticleEmitter::Draw()
{
    if (!m_pVertexBuffer)
    {
        return;
    }

	if (!IsEmpty() )
	{
		TVertexParticle* pv;
		DWORD dwNumParticlesInBatch = 0;
		PreDraw();
        CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
        CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
        pRenderer->SetWorldMatrix(m_matWorld);
		pRenderer->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TVertexParticle) );

		SortParticles();

		m_pVertexBuffer->Lock(NULL, 0, (void**)&pv, D3DLOCK_DISCARD);

		for (int32 i = 0; i < static_cast<int32>(m_vecParticles.size() ); ++i)
		{
			if (m_vecParticles[i].bAlive)
			{
				pv->vec3Position = m_vecParticles[i].vec3Position;
				const D3DXCOLOR& kr = m_vecParticles[i].colour;
				pv->colour = D3DCOLOR_COLORVALUE(kr.r, kr.g, kr.b, kr.a);
				pv++;
				++dwNumParticlesInBatch;
			}
			
		}
		m_pVertexBuffer->Unlock();
		if (dwNumParticlesInBatch)
		{
			pRenderer->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesInBatch);
		}
		PostDraw();
	}
}

/*
* PostDraw
* @author Rigardt de vries
* @return void
*/
void
CFlameParticleEmitter::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	float32 fSize = 1.0f;

	pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* CheckAlive
* @author Rigardt de Vries
* @return bool
*/
bool
CFlameParticleEmitter::CheckAlive()
{
	return (true);
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CFlameParticleEmitter::OnDeviceLost()
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
CFlameParticleEmitter::OnDeviceReset()
{
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticle),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CParticleEmitter::OnDeviceLost()
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
CParticleEmitter::OnDeviceReset()
{
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticle),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);
}

/*
* IsEmpty
* @author Rigardt de Vries
* @return bool
*/
bool
CFlameParticleEmitter::IsEmpty()
{
	return (false);
}

/*
* RemoveDeadParticles 
* @author Michael McQuarrie
* @return void
*/
void
CFlameParticleEmitter::RemoveDeadParticles()
{
	/*for(std::vector<TParticle*>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if(!(*iter)->bAlive)
		{
			m_vecParticles.remove(*iter);
		}
	}*/
}

/*
* SetAlive 
* @author Michael McQuarrie
* @param _bAlive 
* @return void
*/
void
CFlameParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

void
CFlameParticleEmitter::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}

bool 
CFlameParticleEmitter::IsAlive()
{
    return (true);
}