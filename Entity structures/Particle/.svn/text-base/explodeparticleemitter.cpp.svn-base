// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   explodeparticleemitter.cpp
//  Description :   explodeparticleemitter.cppfor implementation of explodeparticleemitter.h
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

// This Includes
#include "explodeparticleemitter.h"
#include "particle.h"

// Static Variables
uint32 CExplodeParticleEmitter::s_uiTextureID = BAD_ID;

// Static Function Prototypes

// Implementation

CExplodeParticleEmitter::CExplodeParticleEmitter()
: m_eTeam(TEAM_NEUTRAL)
{
}

CExplodeParticleEmitter::~CExplodeParticleEmitter()
{
}

/*
* Initialise
* @author Michael McQuarrie
* @param _iNumParticles
* @param _vec3Origin
* @return void
*/
bool
CExplodeParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3& _vec3Origin, ETeam _eTeam)
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

    m_eType = PARTICLE_EXPLODE;
	m_eTeam = _eTeam;

	m_matWorld._41 = _vec3Origin.x;
	m_matWorld._42 = _vec3Origin.y;
	m_matWorld._43 = _vec3Origin.z;

	for(uint32 ui = 0; ui < m_dwVertexBufferSize; ++ui)
	{
		//Adding particles to the emitter
		AddParticle();
	}
		
    CEntity::Initialise();

	return (true);
}

/*
* ResetEmitter Resets the Emitter
* @author Michael McQuarrie
* @param _pParticle
* @return void
*/
void
CExplodeParticleEmitter::Resetparticle(TParticle *_pParticle)
{   
	//Initalise origin
	_pParticle->vec3Position = m_vec3Origin;

	//Set to alive
	_pParticle->bAlive = true;

	//Setting it
    _pParticle->vec3Velocity.x = static_cast<float32>((rand() % 501) - 250);
    _pParticle->vec3Velocity.y = static_cast<float32>((rand() % 501) - 250);
    _pParticle->vec3Velocity.z = static_cast<float32>((rand() % 501) - 250);

    D3DXVec3Normalize(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity);

	//Setting the life timer
	////////////////////
	/// TEMP ///////////
	////////////////
	_pParticle->fAge = 1.0f;
	_pParticle->fLifeTime = 0.0f;
    _pParticle->vec3Position = m_vec3Origin;
	_pParticle->colour = KCOLYELLOW;
    _pParticle->bAlive = true;
}

/*
* AddParticle
* @author Michael McQuarrie
* @param _pParticle
* @return void
*/
void 
CExplodeParticleEmitter::AddParticle()
{
    TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

void
CExplodeParticleEmitter::Process(float32 _fDeltaTick)
{
	//Check if particles are still alive
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if(iter->bAlive)
		{
			//Adding the velocity to move the particles
            iter->vec3Position += iter->vec3Velocity * _fDeltaTick * 5.0f;

			if (iter->fLifeTime < 0.5f)
			{
				if(m_eTeam == TEAM_PURPLE)
				{
					D3DXColorLerp(&iter->colour, &KCOLBLUE, &KCOLTEAM_PURPLE, iter->fLifeTime * 2.0f);
				}
				else
				{
					D3DXColorLerp(&iter->colour, &KCOLYELLOW, &KCOLTEAM_GREEN, iter->fLifeTime * 2.0f);
				}
			}
			else
			{
				if(m_eTeam == TEAM_PURPLE)
				{
					D3DXColorLerp(&iter->colour, &KCOLTEAM_PURPLE, &KCOLGREY, (iter->fLifeTime - 0.5f) * 2.0f);
				}
				else
				{
					D3DXColorLerp(&iter->colour, &KCOLTEAM_GREEN, &KCOLGREY, (iter->fLifeTime - 0.5f) * 2.0f);
				}
			}

			//Adding to the life counter
			iter->fLifeTime += _fDeltaTick;
			if(iter->fAge <= iter->fLifeTime)
			{
				iter->bAlive = false;
			}
		}
	}
	
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);

	//Lastly Remove the dead particles
	CheckAlive();
}

/*
* PreDraw sets the pre draw states
* @author Michael McQuarrie
* @return void
*/
void
CExplodeParticleEmitter::PreDraw()
{
	// Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

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
CExplodeParticleEmitter::Draw()
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
		if (IsAlive() == true)
		{
			pRenderer->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesInBatch);
		}
		PostDraw();
	}
}

/*
* PostDraw sets the post draw states
* @author Michael McQuarrie
* @return void
*/
void
CExplodeParticleEmitter::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* RemoveDeadParticles 
* @author Michael McQuarrie
* @return void
*/
void
CExplodeParticleEmitter::RemoveDeadParticles()
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
CExplodeParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

bool
CExplodeParticleEmitter::CheckAlive()
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
CExplodeParticleEmitter::OnDeviceLost()
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
CExplodeParticleEmitter::OnDeviceReset()
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
CExplodeParticleEmitter::IsEmpty()
{
    return (m_bEmpty);
}

void 
CExplodeParticleEmitter::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}