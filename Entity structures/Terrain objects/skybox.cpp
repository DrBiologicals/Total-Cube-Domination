// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   flag.cpp
//  Description :   flag.cppfor implementation of flag.h
//  Author      :   Rebeccah Cox
//  Mail        :	rebeccah.cox@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../engine/totalcubedomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/renderer.h"
#include "../../engine/graphics and sound/model.h"
#include "../../engine/graphics and sound/texturemanager.h"

// This Includes
#include "skybox.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* 
* Constructor.
* 
* @author Rebeccah Cox
*/
CSkyBox::CSkyBox()
: m_uiModelID(BAD_ID)
, m_uiTextureID(BAD_ID)
{
}

/**
* 
* Destructor.
* 
* @author Rebeccah Cox
*/
CSkyBox::~CSkyBox()
{
}

/**
* 
* Sets the model and texture IDs, returns false if they are invalid.
* 
* @author Rebeccah Cox
* @param uint32 uiModelID
* @param uint32 uiTextureID
* @return bool 
*/
bool
CSkyBox::Initialise(uint32 _uiModelID, uint32 _uiTextureID)
{
	CRenderEntity::Initialise();

	D3DXMatrixIdentity(&m_matWorld);

	m_uiModelID = _uiModelID;
	if(BAD_ID == m_uiModelID)
	{
		return (false);
	}

	m_uiTextureID = _uiTextureID;
	if(BAD_ID == m_uiTextureID)
	{
		return (false);
	}

	return (true);
}

/**
* 
* Adds this object to all of the viewports to draw.
* 
* @author Rebeccah Cox
* @param float32 _fDeltaTick
* @return void
*/
void
CSkyBox::Process(float32 _fDeltaTick)
{
	CTotalCubeDomination::GetInstance().GetRenderer()->AddToAllViewports(this, RENDERTYPE_3DCOORDS | RENDERTYPE_OPAQUE);
}

/**
* 
* Sets the texture and draws the model.
* 
* @author Rebeccah Cox
* @return void
*/
void
CSkyBox::Draw()
{
	D3DXMatrixScaling(&m_matWorld, 4.0f, 4.0f, 4.0f);

	// Set the world matrix, and the texture of the tank and then draw the model using the IDs.
	CTotalCubeDomination::GetInstance().GetRenderer()->SetWorldMatrix(m_matWorld);
    CTextureManager::GetInstance().SetTexture(0, m_uiTextureID);
	CModelManager::GetInstance().Draw(m_uiModelID);
}
