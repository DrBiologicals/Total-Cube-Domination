// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   font.h
//  Description :   
//  Author      :   
//  Mail        :   
//

#ifndef __IGFEB10_MODULE_FONT_H__
#define __IGFEB10_MODULE_FONT_H__

// Library Includes
#include <string>

// Local Includes

// Types

// Prototypes
class CFont
{
	// Member Functions
public:
	CFont();
	~CFont();

    bool Initialise(int32 _iHeight, int32 _iWidth, int32 _iWeight, bool _bItalic, const char* _kpcFontName);

	void OnDeviceLost();
	void OnDeviceReset();

    LPD3DXFONT GetFont();

protected:

private:

	// Member Variables
public:

protected:
	LPD3DXFONT m_pFont;

	int32 m_iHeight;
	int32 m_iWidth;
	int32 m_iWeight;
	
	std::string m_strFontName;

	bool m_bItalic;

private:

}; 

#endif // __IGFEB10_MODULE_TEXTURE_H__

