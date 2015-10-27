// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   bulletwallparticles.cpp
//  Description :   bulletwallparticles.cppfor implementation of bulletwallparticles.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../defines.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "emittermanager.h"
#include "../player objects/bullet.h"

// This Includes

#include "bulletwallparticles.h"
#include "particle.h"

// Static Variables
uint32 CBulletWallParticles::s_uiTextureID = BAD_ID;


// Static Function Prototypes


// Implementation
CBulletWallParticles::CBulletWallParticles()
: m_pBullet(0)
{

}

CBulletWallParticles::~CBulletWallParticles()
{
	m_pBullet = 0;
}

/*
* Initialise
* @author Michael McQuarrie
* @param _iNumParticles
* @param _vec3Origin
* @return void
*/
bool
CBulletWallParticles::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, EParticleType _eType, CBullet* _pBullet)
{
	// set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

	m_pBullet = _pBullet;

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

	m_eType = PARTICLE_BULLET_WALL;

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
CBulletWallParticles::Resetparticle(TParticle *_pParticle)
{   
	// Initalise origin
	_pParticle->vec3Position = m_vec3Origin;

	// Set to alive
	_pParticle->bAlive = true;

	// Setting it
	_pParticle->vec3Velocity = -m_pBullet->GetDirection();
    float32 fOffset = (rand() % 100) / 100.0f;
    _pParticle->vec3Velocity += m_pBullet->GetRight() * (fOffset - 0.5f);
    fOffset = (rand() % 100) / 100.0f;
    _pParticle->vec3Velocity += m_pBullet->GetUp() * (fOffset - 0.5f);

    D3DXVec3Normalize(&_pParticle->vec3Velocity, &_pParticle->vec3Velocity);

	// Setting the life timer
	////////////////////
	/// TEMP ///////////
	////////////////
	_pParticle->fAge = 0.5f;
	_pParticle->fLifeTime = 0.0f;
    _pParticle->vec3Position = m_vec3Origin;
	_pParticle->colour = KCOLYELLOW;
    _pParticle->bAlive = true;
}

/*
* AddParticle
* @author Michael McQuarrie
* @return void
*/
void 
CBulletWallParticles::AddParticle()
{
    TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* Process
* @author Michael McQuarrie
* @param _fDeltaTick
* @return void
*/
void
CBulletWallParticles::Process(float32 _fDeltaTick)
{
	//Check if particles are still alive
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		if(iter->bAlive)
		{
			//Adding the velocity to move the particles
            iter->vec3Position += iter->vec3Velocity * _fDeltaTick * 5.0f;

			if (iter->fLifeTime < 0.25f)
			{
				
				D3DXColorLerp(&iter->colour, &KCOLYELLOW, &KCOLRED, iter->fLifeTime * 4.0f);
			}
			else
			{
				
				D3DXColorLerp(&iter->colour, &KCOLRED, &KCOLGREY, (iter->fLifeTime - 0.25f) * 4.0f);
				
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
CBulletWallParticles::PreDraw()
{
	// Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);


	float32 fSize = 0.25f;

	pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

/*
* Draw
* @author Michael McQuarrie
* @return void
*/
void
CBulletWallParticles::Draw()
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
CBulletWallParticles::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

    float32 fSize = 1.0f;

	pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* SetAlive 
* @author Michael McQuarrie
* @param _bAlive 
* @return void
*/
void
CBulletWallParticles::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}
/*
* Check Alive
* @author Michael McQuarrie
* @return void
*/
bool
CBulletWallParticles::CheckAlive()
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
CBulletWallParticles::OnDeviceLost()
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
CBulletWallParticles::OnDeviceReset()
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
* @author Michael McQuarrie
* @return bool
*/
bool 
CBulletWallParticles::IsEmpty()
{
    return (m_bEmpty);
}

/*
* SetTexture
* @author Michael McQuarrie
* @param _uiID
* @return void
*/
void 
CBulletWallParticles::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}