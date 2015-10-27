// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   statistics.h
//  Description :   Declaration for CStatistics
//  Author      :   Rigardt de Vries
//  Mail        :   rigardt.vries@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_STATISTICS_H__
#define __IGFEB10_MODULE_STATISTICS_H__

// Library Includes
#include <string>
#include <vector>
// Local Includes
#include "../../Entity structures/renderentity.h"
// Types

// Prototypes
class CText;
class CStaticGraphic;

class CStatistics : public CRenderEntity
{
	// Member Functions
public:
	CStatistics();
	~CStatistics();

	bool Initialise(uint32 _uiTankID);
	virtual void Draw();
	virtual void Process(float32 _fDeltaTick);
	float32 GetExitTime();

protected:

private:

	// Member Variables
public:

protected:
	std::string m_strStats[7];
	std::vector<CText*> m_vecText;
	CStaticGraphic* m_pStatGraphic;
	uint32 m_uiTankID;
	uint32 m_uiTextID;
	float32 m_fCurrentTime;
	RECT m_rect;

private:

}; 

#endif // __IGFEB10_MODULE_STATISTICS_H__

