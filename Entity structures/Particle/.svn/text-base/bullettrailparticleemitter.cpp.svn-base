// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bullettrailparticleemitter.cpp
//  Description :   bullettrailparticleemitter.cppfor implementation of bullettrailparticleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../defines.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../player objects/bullet.h"
#include "../player objects/tank.h"
#include "emittermanager.h"

// This Includes
#include "bullettrailparticleemitter.h"
#include "particle.h"

// Static Variables
uint32 CBulletTrailParticleEmitter::s_uiTextureID = BAD_ID;

// Static Function Prototypes

// Implementation

CBulletTrailParticleEmitter::CBulletTrailParticleEmitter()
: m_fEmitRate(0.03f)
, m_fEmitTimer(0.0f)
, m_pBullet(0)
, m_eTeam(TEAM_NEUTRAL)
{
}

CBulletTrailParticleEmitter::~CBulletTrailParticleEmitter()
{
    m_pBullet = 0;
}

/*
* This function initialises the bullet trail particle emitter
* @author Rigardt de vries
* @param _iNumparticles             the number of particles in the emitter
* @param _vec3Origin                the origin of the particle emitter
* @param _pBullet                   the bullet that the emitter follows
* @param _eTeam                     the team of the bullet.
* @return true if successful initialised.
*/
bool
CBulletTrailParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, CBullet* _pBullet, ETeam _eTeam)
{
     // set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

    m_vec3Origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    // create the vertex buffer
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticleSize),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);

	D3DXMatrixIdentity(&m_matWorld);

    m_eType = PARTICLE_EXPLODE;
	m_eTeam = _eTeam;

	m_matWorld._41 = _vec3Origin.x;
	m_matWorld._42 = _vec3Origin.y;
	m_matWorld._43 = _vec3Origin.z;

    m_pBullet = _pBullet;
    m_pTankOwner = m_pBullet->GetTankOwner();
		
    CEntity::Initialise();

	return (true);
}

/*
* This adds a particle to the emitter
* @author Rigardt de Vries  
* @return void
*/
void
CBulletTrailParticleEmitter::AddParticle()
{
    TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* this resets a single particle
* @author Rigardt de Vries
* @param _pParticle         the particle to be reset
* @return void
*/
void
CBulletTrailParticleEmitter::Resetparticle(TParticle *_pParticle)
{
    //Initalise origin
	_pParticle->vec3Position = m_vec3Origin;

	//Set to alive
	_pParticle->bAlive = true;

	//Setting it
    _pParticle->vec3Velocity.x = m_pBullet->GetWorldMatrix()._31;
    _pParticle->vec3Velocity.y = m_pBullet->GetWorldMatrix()._32;
    _pParticle->vec3Velocity.z = m_pBullet->GetWorldMatrix()._33;

    D3DXVec3Normalize(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity);

	//Setting the life timer
	_pParticle->fAge = 0.1f;
	_pParticle->fLifeTime = 0.0f;
    _pParticle->vec3Position = m_vec3Origin;
    _pParticle->fSize = 0.2f;

    if (m_eTeam == TEAM_GREEN)
    {
        _pParticle->colour = KCOLTEAM_GREEN;
    }
    else
    {
        _pParticle->colour = KCOLTEAM_PURPLE;
    }
}

/*
* This function processes the emitter
* @author Rigardt de Vries
* @param _fDeltaTick            the game timer
* @return void
*/
void
CBulletTrailParticleEmitter::Process(float _fDeltaTick)
{
    if(!m_pBullet || CheckBullet() == false)
    {
        return;
    }
    
    if (m_dwVertexBufferSize > m_vecParticles.size())
	{
		m_fEmitTimer += _fDeltaTick;
		if (m_fEmitTimer > m_fEmitRate)
		{
			m_fEmitTimer = 0.0f;
			//Adding particles to the emitter
			AddParticle();
		}
	}

    //Check if particles are still alive
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
        if (iter->bAlive == false)
		{
			m_fEmitTimer += _fDeltaTick;
			if (m_fEmitTimer > m_fEmitRate)
			{
				m_fEmitTimer = 0.0f;
				
				iter->bAlive = true;
                Resetparticle(&(*iter));
			}
			
		}
		if(iter->bAlive)
		{
			//Adding the velocity to move the particles
            iter->vec3Position -= iter->vec3Velocity * _fDeltaTick * m_pBullet->GetMoveSpeed();

			iter->fSize = 1.0f - 1.0f * (iter->fLifeTime / iter->fAge);

			if (iter->fLifeTime == 0.0f)
			{
				int i = 0;
			}

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
					D3DXColorLerp(&iter->colour, &KCOLTEAM_GREEN, &KCOLYELLOW, (iter->fLifeTime - 0.5f) * 2.0f);
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

    m_matWorld._41 = m_pBullet->GetWorldMatrix()._41;
    m_matWorld._42 = m_pBullet->GetWorldMatrix()._42;
    m_matWorld._43 = m_pBullet->GetWorldMatrix()._43;
	
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);
}

/*
* set all the predraw render states
* @author Rigardt de Vries
* @return void
*/
void
CBulletTrailParticleEmitter::PreDraw()
{
	// Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

    //float32 fSize = 0.2f;

	//pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

/*
* Draw
* @author Rigardt de Vries
* @return void
*/
void
CBulletTrailParticleEmitter::Draw()
{
    if (!m_pVertexBuffer || !m_pBullet)
    {
        return;
    }

	if (!IsEmpty() )
	{
		TVertexParticleSize* pv;
		DWORD dwNumParticlesInBatch = 0;
		PreDraw();
        CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();
        CTextureManager::GetInstance().SetTexture(0, s_uiTextureID);
        pRenderer->SetWorldMatrix(m_matWorld);
        pRenderer->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE);
		pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TVertexParticleSize) );

		std::sort(m_vecParticles.begin(), m_vecParticles.end());

		m_pVertexBuffer->Lock(NULL, m_dwVertexBufferSize * sizeof(TVertexParticleSize), (void**)&pv, D3DLOCK_DISCARD);

		for (int32 i = 0; i < static_cast<int>(m_vecParticles.size() ); ++i)
		{
			if (m_vecParticles[i].bAlive)
			{
				pv->vec3Position = m_vecParticles[i].vec3Position;
				const D3DXCOLOR& kr = m_vecParticles[i].colour;
				pv->colour = D3DCOLOR_COLORVALUE(kr.r, kr.g, kr.b, kr.a);
                pv->fsize = m_vecParticles[i].fSize;
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
CBulletTrailParticleEmitter::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	//float32 fSize = 1.0f;

	//pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* CheckAlive
* @author Rigardt de Vries
* @return bool
*/
bool
CBulletTrailParticleEmitter::CheckAlive()
{
	return (m_bAlive);
}

/*
* IsEmpty
* @author Rigardt de Vries
* @return bool
*/
bool
CBulletTrailParticleEmitter::IsEmpty()
{
	return (false);
}

/*
* RemoveDeadParticles 
* @author Rigardt de Vries
* @return void
*/
void
CBulletTrailParticleEmitter::RemoveDeadParticles()
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
* Sets the m_bAlive variable
* @author Rigardt de Vries
* @param _bAlive            the replacement value.
* @return void
*/
void
CBulletTrailParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

/*
* set the static texture ID for the emitter
* @author Rigardt de Vries
* @param _uiID          the id for the textuer
* @return void
*/
void
CBulletTrailParticleEmitter::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}

/*
* returns a bool if for if the emitter is alvie 
* @author Rigardt de Vries
* @return m_bAlive
*/
bool 
CBulletTrailParticleEmitter::IsAlive()
{
    return (m_bAlive);
}

/*
* sets the bullet
* @author Rigardt de Vries
* @param _pBullet       the new bullet
* @return void
*/
void 
CBulletTrailParticleEmitter::SetBullet(CBullet *_pBullet)
{
    m_pBullet = _pBullet;
}

/*
* This function checks if the bullet is alive.
* @author Rigardt de Vries
* @return void
*/
bool
CBulletTrailParticleEmitter::CheckBullet()
{
    bool bBulletAlive = false;
    std::list<CBullet*> listBullets = m_pTankOwner->GetBulletList();
    for (std::list<CBullet*>::iterator iter = listBullets.begin(); 
		iter != listBullets.end(); ++iter)
	{
        if (m_pBullet == (*iter))
        {
            bBulletAlive = true;
            break;
        }
    }
    return (bBulletAlive);
}