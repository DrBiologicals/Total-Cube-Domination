// 
//  Diploma of Interactive Gaming 
//  Game Development Faculty 
//  Media Design School 
//  Auckland
//  New Zealand
// 
//  (c) 2005-2010 Media Design School
//
//  File Name   :   fontmanager.h
//  Description :   
//  Author      :   
//  Mail        :   
//

#ifndef __IGFEB10_MODULE_FONTMANAGER_H__
#define __IGFEB10_MODULE_FONTMANAGER_H__

// Library Includes

// Local Includes

// Types
const int32 AMOUNTOFFONTS = 32;

// Prototypes
class CFont;

class CFontManager
{
	// Member Functions
public:

	static CFontManager& GetInstance();
	static void DestroyInstance();

	bool Initialise();

    void Clear();

	void OnDeviceLost();
	void OnDeviceReset();

	uint32 CreateDirect3DFont(int32 _iHeight, int32 _iWidth, int32 _iWeight, bool _bItalic, const char* _kpcFontName);
	void Draw(uint32 _uiID, const char* _kpcString, LPRECT _pRect, DWORD _dwFormat, DWORD _dwColour);

protected:

private:
	CFontManager();
	CFontManager(const CFontManager& _kr);
	~CFontManager();

	CFontManager& operator=(const CFontManager& _kr);

	// Member Variables
public:

protected:
	CFont* m_apFonts[AMOUNTOFFONTS];

    static CFontManager* s_pInstance;

private:

}; 

#endif // __IGFEB10_MODULE_TOWER_H__

