// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   particle.h
//  Description :   Declaration for Cparticle
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PARTICLE_H__
#define __IGFEB10_MODULE_PARTICLE_H__

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/renderer.h"

// Types

// Prototypes
struct TParticle
{
	D3DXVECTOR3 vec3Position;
    D3DXVECTOR3 vec3Velocity;

	bool bAlive;

	float32 fAge;
	float32 fLifeTime;
    float32 fDepth;
	float32 fSize;

    D3DXCOLOR colour;

	uint32 uiTextureID;

	bool operator<(const TParticle& _kr);
};

struct TVertexParticle
{
	D3DXVECTOR3 vec3Position;
	D3DCOLOR colour;
};

struct TVertexParticleSize
{
	D3DXVECTOR3 vec3Position;
    float32 fsize;
	D3DCOLOR colour;  
};

#endif // __IGFEB10_MODULE_PARTICLE_H__

