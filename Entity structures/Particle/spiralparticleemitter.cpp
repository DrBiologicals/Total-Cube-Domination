// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   spiralparticleemitter.cpp
//  Description :   spiralparticleemitter.cppfor implementation of spiralparticleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "../player objects/tank.h"
#include "emittermanager.h"

// This Includes
#include "spiralparticleemitter.h"
#include "particle.h"

// Static Variables

// Static Function Prototypes
uint32 CSpiralParticleEmitter::s_uiTextureID = BAD_ID;

// Implementation

CSpiralParticleEmitter::CSpiralParticleEmitter()
: m_fSpawnTimer(0.0f)
, m_eFace(FACE_NONE)
, m_fRotationAngle(0.0f)
, m_pTank(0)
{
}

CSpiralParticleEmitter::~CSpiralParticleEmitter()
{
    m_pTank = 0;
}

/*
* This function initialises the emitter variables
* @author Rigardt de Vries
* @param _iNumParticles             the number of particles for the emitter.
* @param _vec3Origin                the origin of the emitter.
* @return true if the initialisation is successful, flase if not
*/
bool
CSpiralParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, CTank* _pTank)
{
    // set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

    m_vec3Origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    m_pTank = _pTank;

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

    // create the vertex buffer
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticle),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);

	D3DXMatrixIdentity(&m_matWorld);

	m_matWorld._41 = _vec3Origin.x;
	m_matWorld._42 = _vec3Origin.y;
	m_matWorld._43 = _vec3Origin.z;

	if (_vec3Origin.x == 22.5f)
	{
		m_eFace = FACE_RIGHT;
	}
	else if (_vec3Origin.x <= -22.5f)
	{
		m_eFace = FACE_LEFT;
	}
	else if (_vec3Origin.y >= 22.5f)
	{
		m_eFace = FACE_TOP;
	}
	else if (_vec3Origin.y <= -22.5f)
	{
		m_eFace = FACE_BOTTOM;
	}
	else if (_vec3Origin.z >= 22.5f)
	{
		m_eFace = FACE_BACK;
	}
	else if (_vec3Origin.z <= -22.5f)
	{
		m_eFace = FACE_FRONT;
	}
		
    CEntity::Initialise();

    m_fEmitRate = 0.02f;

    return (true);
}

/*
* Adds a particle to the emitter
* @author Rigardt de Vries
* @return void
*/
void
CSpiralParticleEmitter::AddParticle()
{
    TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* Resets a single particle.
* @author Rigardt de Vries
* @param _pParticle         the particle to be reset
* @return void
*/
void
CSpiralParticleEmitter::Resetparticle(TParticle *_pParticle)
{
    //Initalise origin
	_pParticle->vec3Position = m_vec3Origin;

	//Set to alive
	_pParticle->bAlive = true;

	//Setting it
	_pParticle->vec3Velocity = g_atUpRightDirectionVecs[m_eFace].vec3Up  * 15.0f;

	//Setting the life timer
	_pParticle->fAge = 0.6f;
	_pParticle->fLifeTime = 0.0f ;
	_pParticle->vec3Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    D3DXMATRIX matrix;

    D3DXMatrixIdentity(&matrix);

    D3DXMatrixRotationAxis(&matrix, &g_atUpRightDirectionVecs[m_eFace].vec3Up, m_fRotationAngle);

    D3DXVECTOR3 vec3Location;

	if (m_eFace == FACE_TOP || m_eFace == FACE_BOTTOM)
	{
		vec3Location = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
	else if (m_eFace == FACE_LEFT || m_eFace == FACE_RIGHT)
	{
		vec3Location = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else if (m_eFace == FACE_BACK || m_eFace == FACE_FRONT)
	{
		vec3Location = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

    D3DXVec3TransformNormal(&vec3Location, &vec3Location, &matrix);

    _pParticle->vec3Position = vec3Location * 1.0f;

	_pParticle->colour = KCOLTEAM_PURPLE;
}

/*
* Processes the emitter
* @author Rigardt de Vries
* @param _fDeltaTick        the game timer.
* @return void
*/
void
CSpiralParticleEmitter::Process(float32 _fDeltaTick)
{
    m_fRotationAngle += _fDeltaTick * 10;

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

    for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
        if(iter->bAlive)
	    {
		    //Adding the velocity to move the particles
            iter->vec3Position += iter->vec3Velocity * _fDeltaTick;

            if (m_pTank->GetTeam() == TEAM_GREEN)
            {
		        if (iter->fLifeTime < 0.3f)
		        {
			        D3DXColorLerp(&iter->colour, &KCOLYELLOW, &KCOLTEAM_GREEN, iter->fLifeTime * 3.333333f);
		        }
		        else
		        {
			        D3DXColorLerp(&iter->colour, &KCOLTEAM_GREEN, &KCOLYELLOW, (iter->fLifeTime - 0.3f) * 3.333333f);
                }
		    }
            else
            {
                if (iter->fLifeTime < 0.3f)
		        {
			        D3DXColorLerp(&iter->colour, &KCOLTEAM_PURPLE, &KCOLBLUE, iter->fLifeTime * 3.333333f);
		        }
		        else
		        {
			        D3DXColorLerp(&iter->colour, &KCOLBLUE, &KCOLTEAM_PURPLE, (iter->fLifeTime - 0.3f) * 3.333333f);
                }
            }

		    //Adding to the life counter
		    iter->fLifeTime += _fDeltaTick;
		    if(iter->fAge <= iter->fLifeTime)
		    {
			    {
				    iter->bAlive = false;
			    }
		    }
        }
	}
	
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);

    m_eFace = m_pTank->GetFacePosition();
    m_matWorld._41 = m_pTank->GetWorldMatrix()._41;
    m_matWorld._42 = m_pTank->GetWorldMatrix()._42;
    m_matWorld._43 = m_pTank->GetWorldMatrix()._43;
}

/*
* Set all the predraw render states
* @author Rigardt de Vries
* @return void
*/
void
CSpiralParticleEmitter::PreDraw()
{
    // Grab the renderer.
	//Set the render states for whatever emitter is needed
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    float32 fSize = 0.5f;

    pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));
}

/*
* Draw the particles in this emitter
* @author Rigardt de Vries
* @return void
*/
void
CSpiralParticleEmitter::Draw()
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
* Set all the post draw render states
* @author Rigardt de Vries
* @return void
*/
void
CSpiralParticleEmitter::PostDraw()
{
    CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

    float32 fSize = 1.0f;

    pDevice->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)(&fSize));
}

/*
* IsEmpty
* @author Rigardt de Vries
* @return bool
*/
bool
CSpiralParticleEmitter::IsEmpty()
{
	return (false);
}

/*
* Returns if the emitter is alive
* @author Rigardt de Vries
* @return bool
*/
bool 
CSpiralParticleEmitter::IsAlive()
{
    if (m_vecParticles.size() == 0)
    {
        return (true);
    }
    for (uint32 i = 0; i < m_vecParticles.size(); ++i)
	{
		if (m_vecParticles[i].bAlive)
		{
			return (true);
		}
	}
    return (false);
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CSpiralParticleEmitter::OnDeviceLost()
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
CSpiralParticleEmitter::OnDeviceReset()
{
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticle),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);
}

/*
* RemoveDeadParticles 
* @author Michael McQuarrie
* @return void
*/
void
CSpiralParticleEmitter::RemoveDeadParticles()
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
* @author Rigardt de Vries
* @param _bAlive 
* @return void
*/
void
CSpiralParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

/*
* Sets the static uint32 texture id
* @author Rigardt de Vries
* @param _uiID          the id for the texture
* @return void
*/
void
CSpiralParticleEmitter::SetTextureID(uint32 _uiID)
{
	s_uiTextureID = _uiID;
}