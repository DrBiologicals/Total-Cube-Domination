// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   tile.cpp
//  Description :   tile.cppfor implementation of tile.h
//  Author      :   Michael McQuarrie
//  Mail        :   michael.mcquarrie@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "../../Engine/TotalCubeDomination.h"
#include "../../engine/graphics and sound/modelmanager.h"
#include "../../engine/graphics and sound/texturemanager.h"
#include "wall.h"

// This Includes

#include "tile.h"

// Static Variables

// Static Function Prototypes


// Implementation
CTile::CTile()
: m_eFace(FACE_TOP)
, m_iTextureID(BAD_ID)
, m_iModelID(BAD_ID)
, m_bTraversable(true)
, m_iX(-1)
, m_iY(-1)
{
	D3DXMatrixIdentity(&m_matWorld);
}

CTile::~CTile()
{

}

int32 
CTile::GetX() const
{
	return (m_iX);
}

int32 
CTile::GetY() const
{
	return (m_iY);
}

/*
* 
* @author Michael McQuarrie
* @param _iModelId
* @return True if valid model ID
*/
bool
CTile::SetModel(int32 _iModelID)
{
	m_iModelID = _iModelID;

	return(true);
}

/*
* 
* @author Michael McQuarrie
* @param _iTextureID
* @return true if a valid Texture ID
*/
bool
CTile::SetTexture(int32 _iTextureID)
{
	m_iTextureID = _iTextureID;
	
	return(true);
}

/*
* 
* @author Michael McQuarrie
*
* @return if its traversable
*/
bool
CTile::IsTraversable() const
{
	return(m_bTraversable);
}

/**
* 
* Returns which face the tile is on.
* 
* @author Rebeccah Cox
* @return EFacePosition m_eFace
*/
EFacePosition
CTile::GetFacePosition() const
{
	return (m_eFace);
}
