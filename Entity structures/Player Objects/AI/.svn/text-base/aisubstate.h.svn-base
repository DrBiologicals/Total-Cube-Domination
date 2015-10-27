// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   aisubstate.h
//  Description :   Declaration for CAISubstate
//  Author      :   Cameron MacIntosh
//  Mail        :   cameron.macintosh@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_AISUBSTATE_H__
#define __IGFEB10_MODULE_AISUBSTATE_H__

// Library Includes

// Local Includes
#include "../../entity.h"
#include "../../../defines.h"
#include "../../terrain objects/cube.h"
#include "../tank.h"
#include "aihelper.h"

// Types

// Prototypes
class CPathfinder;

class CAISubstate : public CEntity
{
	// Member Functions
public:
	CAISubstate();
	virtual ~CAISubstate();
	virtual void Process(float32 _fDeltaTick);

	virtual EDirection GetClosestNode();
	void CAISubstate::FireAtEnemy();

	static void SetCube(CCube* _pCube);

protected:

private:

	// Member Variables
public:

protected:
	CTank* m_pTank;
	int32 m_iSPTID;
	static CCube* s_pCube;
private:

}; 

#endif // __IGFEB10_MODULE_AISUBSTATE_H__

