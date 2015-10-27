// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   boundingbox.h
//  Description :   Declaration for TBoundingBox
//  Author      :   Daniel Jay
//  Mail        :	ryan.jay@mediadesign.school.nz
//

#ifndef __IGFEB10_MODULE_BOUNDINGBOX_H__
#define __IGFEB10_MODULE_BOUNDINGBOX_H__

// Library Includes
#include <d3dx9.h>

// Local Includes

// Types

// Prototypes
struct TBoundingBox
{
	D3DXVECTOR3 m_vec3Min;
	D3DXVECTOR3 m_vec3Max;
}; 

#endif // __IGFEB10_MODULE_BOUNDINGBOX_H__

