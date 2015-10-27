// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   cpicparticleemitter.cpp
//  Description :   cpicparticleemitter.cppfor implementation of cpicparticleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../player objects/tank.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "../../engine/viewport/viewport.h"

// This Includes
#include "picparticleemitter.h"
#include "particle.h"

// Static Variables
uint32 CPICParticleEmitter::s_uiMoveID = BAD_ID;
uint32 CPICParticleEmitter::s_uiBulletDamageID = BAD_ID;
uint32 CPICParticleEmitter::s_uiBulletMoveID = BAD_ID;
uint32 CPICParticleEmitter::s_uiRadiusID = BAD_ID;
uint32 CPICParticleEmitter::s_uiShieldID = BAD_ID;

// Static Function Prototypes

// Implementation

CPICParticleEmitter::CPICParticleEmitter()
: m_pTank(0)
{
}

CPICParticleEmitter::~CPICParticleEmitter()
{
	m_pTank = 0;
}

/*
* Initialises the emitter
* @author Rigardt de Vries
* @param _iNumParticles			Number of particles.
* @param _vec3Origin			The origin of a particle.
* @param _pTank					the tank for the emitter.
* @return void
*/
bool
CPICParticleEmitter::Initialise(int32 _iNumParticles, const D3DXVECTOR3 &_vec3Origin, CTank *_pTank)
{
	 // Set the batch size (the number of particles)
    m_dwVertexBufferSize = _iNumParticles;

	// Set tank
	m_pTank = _pTank;

    m_vec3Origin = _vec3Origin;

	m_dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

    // Create the vertex buffer
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticleSize),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);

	D3DXMatrixIdentity(&m_matWorld);

    m_eType = PARTICLE_EXPLODE;
		
    CEntity::Initialise();

	return (true);
}

/*
* AddParticle
* @author Rigardt de Vries
* @param _pParticle
* @return void
*/
void
CPICParticleEmitter::AddParticle()
{
	TParticle TempParticle;
    Resetparticle(&TempParticle);
	m_vecParticles.push_back(TempParticle);
}

/*
* ResetEmitter Resets the Emitter
* @author Rigardt de Vries
* @param _pParticle			the reseting particle.
* @param _ePicType			the type of pic particle.
* @return void
*/
void
CPICParticleEmitter::Resetparticle(TParticle *_pParticle)
{
	//Set to alive
	_pParticle->bAlive = true;

	//Setting the life timer
	_pParticle->fAge = 2.0f;
	_pParticle->fLifeTime = 0.0f;
	if (m_ePICType == PIC_BULLET_DAMAGE)
	{
			_pParticle->colour = 0x44CC1111;
			_pParticle->vec3Position = m_pTank->GetPosition();
	}
	else if (m_ePICType == PIC_BULLET_SPEED)
	{
			_pParticle->colour = 0x44AA5511;
			_pParticle->vec3Position = m_pTank->GetPosition();
	}
	else if (m_ePICType == PIC_MOVE_SPEED)
	{
			_pParticle->colour = 0x442244CC;
			_pParticle->vec3Position = m_pTank->GetPosition();
	}
	else if (m_ePICType == PIC_EXPLODE_RADIUS)
	{
			_pParticle->colour = 0x44BBBB22;
			_pParticle->vec3Position = m_pTank->GetPosition();
	}
	else
	{
			_pParticle->colour = 0x4455DD55;
			_pParticle->vec3Position = m_pTank->GetPosition();
	}
	_pParticle->fSize = 2.5f;
	//_pParticle->vec3Velocity = g_atUpRightDirectionVecs[m_pTank->GetFacePosition()] .vec3Up;
}

/*
* Processes the Emitter
* @author Rigardt de Vries
* @param _fDeltaTick		the game timer
* @return void
*/
void
CPICParticleEmitter::Process(float32 _fDeltaTick)
{
	//Check if particles are still alive
	for(std::vector<TParticle>::iterator iter = m_vecParticles.begin(); 
		iter != m_vecParticles.end(); ++iter)
	{
		//Adding the velocity to move the particles
		iter->vec3Position = m_pTank->GetPosition();

		//Adding to the life counter
		iter->fSize += _fDeltaTick * 2.0f;
		iter->fLifeTime += _fDeltaTick;
		if(iter->fAge <= iter->fLifeTime)
		{
			iter->bAlive = false;
		}
	}
    CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_ALPHABLEND);
}

/*
* Sets the predraw render states for the Emitter
* @author Rigardt de Vries
* @return void
*/
void
CPICParticleEmitter::PreDraw()
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
}

/*
* draws the Emitter
* @author Rigardt de Vries
* @return void
*/
void
CPICParticleEmitter::Draw()
{
	if (!m_pVertexBuffer)
    {
        return;
    }
    if (!IsEmpty() )
	{
		TVertexParticleSize* pv;
		DWORD dwNumParticlesInBatch = 0;
		PreDraw();
        CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

		if (m_ePICType == PIC_BULLET_DAMAGE)
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiBulletDamageID);
		}
		else if (m_ePICType == PIC_BULLET_SPEED)
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiBulletMoveID);
		}
		else if (m_ePICType == PIC_MOVE_SPEED)
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiMoveID);
		}
		else if (m_ePICType == PIC_EXPLODE_RADIUS)
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiRadiusID);
		}
		else 
		{
			CTextureManager::GetInstance().SetTexture(0, s_uiShieldID);
		}

        pRenderer->SetWorldMatrix(m_matWorld);
		pRenderer->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE);
		pRenderer->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TVertexParticleSize) );

		SortParticles();

		m_pVertexBuffer->Lock(NULL, 0, (void**)&pv, D3DLOCK_DISCARD);

		for (int32 i = 0; i < static_cast<int32>(m_vecParticles.size() ); ++i)
		{
			pv->vec3Position = m_vecParticles[i].vec3Position;
			const D3DXCOLOR& kr = m_vecParticles[i].colour;
			pv->colour = D3DCOLOR_COLORVALUE(kr.r, kr.g, kr.b, kr.a);
			pv->fsize = m_vecParticles[i].fSize;
			pv++;
			++dwNumParticlesInBatch;			
		}
		m_pVertexBuffer->Unlock();
		//if (IsAlive() == true)
		//{
			pRenderer->GetDevice()->DrawPrimitive(D3DPT_POINTLIST, 0, dwNumParticlesInBatch);
		//}
		PostDraw();
	}
}

/*
* Sets the postdraw render states for the Emitter
* @author Rigardt de Vries
* @return void
*/
void
CPICParticleEmitter::PostDraw()
{
	CRenderer* pRenderer = CTotalCubeDomination::GetInstance().GetRenderer();

    LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

    pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

/*
* checks if the Emitter is alive
* @author Rigardt de Vries
* @return bool
*/
bool
CPICParticleEmitter::CheckAlive()
{
	return (true);
}

/*
* OnDeviceLost
* @author Rigardt de Vries
* @return void
*/
void
CPICParticleEmitter::OnDeviceLost()
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
CPICParticleEmitter::OnDeviceReset()
{
    CTotalCubeDomination::GetInstance().GetRenderer()
        ->GetDevice()->CreateVertexBuffer(	m_dwVertexBufferSize * sizeof(TVertexParticleSize),
							                D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							                m_dwFVF,
							                D3DPOOL_DEFAULT,
							                &m_pVertexBuffer, 0);
}

bool
CPICParticleEmitter::IsAlive()
{
	for (uint32 ui = 0; ui < m_vecParticles.size(); ++ui)
	{
		if (m_vecParticles[ui].bAlive == true)
		{
			return (true);
		}
	}

	return (false);
}

/*
* Return the Emitter's fullness
* @author Rigardt de Vries
* @return bool
*/
bool
CPICParticleEmitter::IsEmpty()
{
	return (false);
}

/*
* Set alive fo the emitter.
* @author Rigardt de Vries
* @param _bAlive		the new alive value
* @return void
*/
void
CPICParticleEmitter::SetAlive(bool _bAlive)
{

}

/*
* Set the textures ID
* @author Rigardt de Vries
* @return void
*/
void
CPICParticleEmitter::LoadAssets()
{
	if (BAD_ID == s_uiBulletDamageID)
	{
		s_uiBulletDamageID = CTextureManager::GetInstance().CreateTexture("textures/pic_bulletDamage.png");
	}
	if (BAD_ID == s_uiBulletMoveID)
	{
		s_uiBulletMoveID = CTextureManager::GetInstance().CreateTexture("textures/pic_bulletSpeed.png");
	}
	if (BAD_ID == s_uiMoveID)
	{
		s_uiMoveID = CTextureManager::GetInstance().CreateTexture("textures/pic_moveSpeed.png");
	}
	if (BAD_ID == s_uiShieldID)
	{
		s_uiShieldID = CTextureManager::GetInstance().CreateTexture("textures/pic_shield.png");
	}
	if (BAD_ID == s_uiRadiusID)
	{
		s_uiRadiusID = CTextureManager::GetInstance().CreateTexture("textures/pic_explodeRadius.png");
	}
}

void
CPICParticleEmitter::SetPicType(EPIC _ePicType)
{
	m_ePICType = _ePicType;
	AddParticle();
}

void
CPICParticleEmitter::ResetAssets()
{
	s_uiMoveID = BAD_ID;
	s_uiBulletDamageID = BAD_ID;
	s_uiBulletMoveID = BAD_ID;
	s_uiRadiusID = BAD_ID;
	s_uiShieldID = BAD_ID;
}