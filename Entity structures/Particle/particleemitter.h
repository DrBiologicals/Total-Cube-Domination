// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   particleemitter.h
//  Description :   Declaration for CparticleEmitter
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_PARTICLEEMITTER_H__
#define __IGFEB10_MODULE_PARTICLEEMITTER_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

// Local Includes
#include "../entity.h"
#include "../renderentity.h"
#include "../../defines.h"

// Types
const D3DXCOLOR KCOLYELLOW = D3DXCOLOR(0xffcccc00);
const D3DXCOLOR KCOLRED = D3DXCOLOR(0xffaa2200);
const D3DXCOLOR KCOLGREY = D3DXCOLOR(0xff7f7f7f);
const D3DXCOLOR KCOLBLUE = D3DXCOLOR(0xff0022dd);
const D3DXCOLOR KCOLTEAM_PURPLE = D3DXCOLOR(0xffdd00dd);
const D3DXCOLOR KCOLTEAM_GREEN = D3DXCOLOR(0xff11dd11);
const D3DXCOLOR KCOLBLACK = D3DXCOLOR(0xff000000);

// Prototypes
struct TParticle;
class CBullet;

class CParticleEmitter : public CRenderEntity
{
	// Member Functions
public:
	CParticleEmitter();
	virtual ~CParticleEmitter();

	virtual void Resetparticle(TParticle* _pParticle) = 0;

	virtual void AddParticle() = 0;

	virtual void Process(float32 _fDeltaTick) = 0;

	virtual void PreDraw() = 0;
	virtual void Draw() = 0;
	virtual void PostDraw() = 0;

	virtual bool IsEmpty();

	virtual bool CheckAlive();

    virtual void OnDeviceLost() = 0;
    virtual void OnDeviceReset() = 0;

	virtual EParticleType GetType();

	virtual bool IsAlive();

    virtual void SetAlive(bool _bAlive);

	void KillParticles();

protected:
	virtual void RemoveDeadParticles();

	void SortParticles();
	
private:

	// Member Variables
public:

protected:
	D3DXVECTOR3 m_vec3Origin;

	float32 m_fSize;
    float32 m_fEmitRate;

	std::vector<TParticle> m_vecParticles;

	int32 m_iMaxparticles;

	EParticleType m_eType;

	bool m_bAlive;
    bool m_bEmpty;
	
    DWORD m_dwVertexBufferSize;
	DWORD m_dwVertexBufferOffset;
	DWORD m_dwVertexBufferBatchSize;
    IDirect3DVertexBuffer9* m_pVertexBuffer;

	DWORD m_dwFVF;

private:

}; 

#endif // __IGFEB10_MODULE_PARTICLEEMITTER_H__

