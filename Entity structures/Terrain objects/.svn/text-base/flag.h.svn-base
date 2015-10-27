// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flag.h
//  Description :   Declaration for Cflag
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_FLAG_H__
#define __IGFEB10_MODULE_FLAG_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "../../defines.h"
#include "../renderentity.h"

// Types

// Prototypes
class CParticleEmitter;
class CFlagPlate;

class CFlag : public CRenderEntity
{
	// Member Functions
public:
	CFlag();
	virtual ~CFlag();

	bool Initialise(uint32 _iModelID, uint32 _iTextureID, ETeam _eTeam, CFlagPlate* _pFlagSpawnLocation);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

	void SetPosition(D3DVECTOR _vecPosition);
	void SetFacePosition(EFacePosition _eFacePosition);
	void ResetPosition();

	void SetVectors(const D3DXVECTOR3& _Up, const D3DXVECTOR3& _Right, const D3DXVECTOR3& _Dir, const D3DXVECTOR3& _Pos);

	const D3DXVECTOR3& GetUp() const;
	const D3DXVECTOR3& GetRight() const;
	const D3DXVECTOR3& GetDirection() const;

    void SetFlagPickedUp(bool _bPickedUp);
    bool GetFlagPickedUp();

	ETeam GetTeam();
	bool IsFlagOnFlagPlate();

	D3DXVECTOR3 GetPosition();
	EFacePosition& GetFace();

protected:

private:

	// Member Variables
public:

protected:
	CFlagPlate* m_pFlagSpawnLocation;
	uint32 m_uiTextureID;
	uint32 m_uiModelID;
	ETeam m_eTeam;
	EFacePosition m_eFace;

    bool m_bPickedUp;

	D3DXVECTOR3 m_vec3Up;
	D3DXVECTOR3 m_vec3Right;
	D3DXVECTOR3 m_vec3Direction;
	D3DXVECTOR3 m_vec3Position;

private:

}; 

#endif // __IGFEB10_MODULE_FLAG_H__

