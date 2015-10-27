// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   skybox.h
//  Description :   Declaration for CSkyBox
//  Author      :   Rebeccah Cox
//  Mail        :	rebeccah.cox@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_SKYBOX_H__
#define __IGFEB10_MODULE_SKYBOX_H__

// Library Includes

// Local Includes
#include "../renderentity.h"

// Types

// Prototypes

class CSkyBox : public CRenderEntity
{
	// Member Functions
public:
	CSkyBox();
	virtual ~CSkyBox();

	bool Initialise(uint32 _uiModelID, uint32 _uiTextureID);
	virtual void Process(float32 _fDeltaTick);
	virtual void Draw();

protected:

private:

	// Member Variables
public:

protected:
	uint32 m_uiModelID;
	uint32 m_uiTextureID;

private:

}; 

#endif // __IGFEB10_MODULE_SKYBOX_H__

