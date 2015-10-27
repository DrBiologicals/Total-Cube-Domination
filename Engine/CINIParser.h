//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   CINIParser.h
//  Description :   Template for declaration (header) files
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

#ifndef __IGFEB10_CINIPARSER_H__
#define __IGFEB10_CINIPARSER_H__

#include <map>
#include <string>
#include <fstream>

using namespace std;

class CINIParser
{
    // Member Functions
public:
	CINIParser();
	~CINIParser();

	bool LoadIniFile(const char* _pcFilename);
	bool AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);
	bool GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue);
	bool GetIntValue(const char* _pcSection, const char* _pcKey, int32& _riValue);
	bool GetFloatValue(const char* _pcSection, const char* _pcKey, float32& _rfValue);
	bool GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue);
	bool SaveIniFile();


private:
	map<string, string> m_mapPairs;
	string m_strFilename;
	fstream m_filestream;

};

#endif // __IGFEB10_CININPARSER_H__
