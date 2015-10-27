// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   particleemitter.cpp
//  Description :   particleemitter.cppfor implementation of particleemitter.h
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

// Library Includes
#include <algorithm>

// Local Includes
#include "../../defines.h"
#include "../../Engine/Graphics and sound/renderer.h"
#include "../../Engine/Graphics and sound/texturemanager.h"
#include "../../Engine/TotalCubeDomination.h"
#include "emittermanager.h"

// This Includes
#include "particleemitter.h"
#include "particle.h"

// Static Variables

// Static Function Prototypes

// Implementation

CParticleEmitter::CParticleEmitter()
: m_fSize(3.0f)
, m_iMaxparticles(20)
, m_bAlive(true)
, m_bEmpty(false)
, m_eType(PARTICLE_NO)
, m_dwFVF(0)
{
}

CParticleEmitter::~CParticleEmitter()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = 0;
	}

	m_vecParticles.clear();
}

/*
* IsAlive Checks if emitter is alive
* @author Michael McQuarrie
* @return bool
*/
bool
CParticleEmitter::IsAlive()
{
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
* RemoveDeadParticles 
* @author Michael McQuarrie
* @return void
*/
void
CParticleEmitter::RemoveDeadParticles()
{

}

/*
* SetAlive 
* @author Michael McQuarrie
* @param _bAlive 
* @return void
*/
void
CParticleEmitter::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

EParticleType
CParticleEmitter::GetType()
{
	return(m_eType);
}

bool
CParticleEmitter::CheckAlive()
{
	return (true);
}

/*
* IsEmpty
* @author Rigardt de Vries
* @return bool
*/
bool 
CParticleEmitter::IsEmpty()
{
    return (m_bEmpty);
}

void
CParticleEmitter::KillParticles()
{
	for(uint32 uiParticle = 0; uiParticle < m_vecParticles.size(); ++uiParticle)
	{
		m_vecParticles[uiParticle].bAlive = false;
	}
}

void
CParticleEmitter::SortParticles()
{
	const D3DXMATRIX& _krMat = CTotalCubeDomination::GetInstance().GetRenderer()->GetViewMatrix();
	D3DXVECTOR3 vec3ViewPos;

	for (uint32 i = 0; i < m_vecParticles.size(); ++i)
	{
		D3DXVec3TransformCoord(&vec3ViewPos, &m_vecParticles[i].vec3Position, &_krMat);

		m_vecParticles[i].fDepth = vec3ViewPos.z;
	}

	std::sort(m_vecParticles.begin(), m_vecParticles.end());
}