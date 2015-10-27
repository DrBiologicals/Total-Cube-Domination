//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2005-2010 Media Design School
//
//  File Name   :   CINIParser.cpp
//  Description :   Template for implementation IniParser files
//  Author      :   Carsten Scholz
//  Mail        :   carsten.scholz@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes

// This Include
#include "CINIParser.h"

// Static Variables

// Static Function Prototypes

// Implementation
CINIParser::CINIParser()
:m_strFilename("")
{

}

CINIParser::~CINIParser()
{

}
/**
*
* This function Loads a .ini file 
*
* @Author Carsten Scholz
* @param _pcFilename is the name of the file which will be loading
* @This function goes through the file and scans through it looking at the sections and the values.
* 
*/
bool
CINIParser::LoadIniFile(const char* _pcFilename)
{
	bool bResult = true;

	//Our string values for section and the current line.
	std::string strLine;
	std::string strSection;
	std::string strMapKey;

	//Setting the filename string
	std::string strFilename(_pcFilename);
	m_strFilename = strFilename + ".ini";;
 
	m_filestream.open(m_strFilename.c_str());

	if (m_filestream.is_open())
	{
		while (!m_filestream.eof())
		{
			bool bReadingKey = true;
			std::string strKey = "";
			std::string strValue = "";

			getline( m_filestream, strLine );

			if (strLine[0] == ';')
			{
				//this line is a comment, ignore it
				continue;
			}
			else if (strLine[0] == '[')
			{
				//Its a section, read it
				strSection = "";

				for(int32 i = 0; i < static_cast<int32>(strLine.size()); ++i)
				{
					if (strLine[i] == '[' || strLine[i] == ']')
					{
						continue;
					}
					
					strSection += strLine[i];
				}

				continue;
			}
			else if (strLine.empty())
			{
				//string is empty, read next line
				continue;
			}

			for(int32 i = 0; i < static_cast<int32>(strLine.size()); ++i)
			{
				if (strLine[i] == ' ')
				{
					continue;
				}
				else if (strLine[i] == '"')
				{
					continue;
				}
				else if (strLine[i] == '=')
				{
					bReadingKey = false;
					continue;
				}
				else if (strLine[i] == ';')
				{
					//the rest of the line are comments
					break;
				}

				if (bReadingKey)
				{
					strKey += strLine[i];
				}
				else
				{
					strValue += strLine[i];
				}
			
			}
			strMapKey = strSection + "|" + strKey;
			m_mapPairs[strMapKey] = strValue;

		}

		m_filestream.close();
	}
	else
	{
		bResult = false;
	}

	return (bResult);
}
/**
*
* This function Adds a value to the ini file when it is saved
*
* @Author Carsten Scholz
* @param _pcSection is the section in the ini file it will be saved to.
* @param _pcKey is the key to the value
* @param _pcValue is the value of which will be saved
* 
*/
bool
CINIParser::AddValue(const char *_pcSection, const char *_pcKey, const char *_pcValue)
{
	bool bResult = true;

	std::string strValueCheck(_pcValue);
	if (strValueCheck == "")
	{
		bResult = false;
	}
	else
	{
		std::string strTempKey(_pcSection);
		strTempKey += "|";
		strTempKey += _pcKey;

		m_mapPairs[strTempKey] = strValueCheck;
	}

	return (bResult);
	
}
/**
*
* This function Gets the string value in the ini file
*
* @Author Carsten Scholz
* @param _pcSection is the section in the ini file it is located
* @param _pcKey is the key to the string value
* @param _rStrValue is then filled with the value if it is found
* @return Returns bResult if true the value was found
* 
*/
bool
CINIParser::GetStringValue(const char *_pcSection, const char *_pcKey, std::string &_rStrValue)
{
	bool bResult = false;

	std::string strSection(_pcSection);
	std::string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rStrValue = m_mapPairs[strKey];
		bResult = true;
	}

	return (bResult);
}
/**
*
* This function Gets the int32 value in the ini file
*
* @Author Carsten Scholz
* @param _pcSection is the section in the ini file it is located
* @param _pcKey is the key to the string value
* @param _riValue is then filled with the value if it is found
* @return Returns bResult if true the value was found
* 
*/
bool
CINIParser::GetIntValue(const char *_pcSection, const char *_pcKey, int32 &_riValue)
{
	bool bResult = false;

	std::string strSection(_pcSection);
	std::string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_riValue = atoi(m_mapPairs[strKey].c_str());
		bResult = true;
	}

	return (bResult);
}
/**
*
* This function Gets the float32 value in the ini file
*
* @Author Carsten Scholz
* @param _pcSection is the section in the ini file it is located
* @param _pcKey is the key to the string value
* @param _rfValue is then filled with the value if it is found
* @return Returns bResult if true the value was found
* 
*/
bool
CINIParser::GetFloatValue(const char *_pcSection, const char *_pcKey, float32 &_rfValue)
{
 	bool bResult = false;

	std::string strSection(_pcSection);
	std::string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rfValue = static_cast<float32>(atof(m_mapPairs[strKey].c_str()));
		bResult = true;
	}

	return (bResult);
}
/**
*
* This function Gets the bool value in the ini file
*
* @Author Carsten Scholz
* @param _pcSection is the section in the ini file it is located
* @param _pcKey is the key to the string value
* @param _rbValue is then filled with the value if it is found
* @return Returns bResult if true the value was found
* 
*/
bool
CINIParser::GetBoolValue(const char *_pcSection, const char *_pcKey, bool &_rbValue)
{
 	bool bResult = false;

	std::string strSection(_pcSection);
	std::string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rbValue = (m_mapPairs[strKey] == "true");
		bResult = true;
	}

	return (bResult);
}


/*
*
*This function write all data into the ini file
*
*@author Carsten Scholz
*@return true if the save was successful
*
*/
bool
CINIParser::SaveIniFile()
{
	std::ofstream myFile;
	std::string strSection;
	std::string strCurrentSection;
	std::string strKey;
	std::string strMapKey;
	std::string strValue;

	bool bIsSaved = false;

	std::map<std::string, std::string>::iterator mapIterator;
	mapIterator = m_mapPairs.begin();

	myFile.open(m_strFilename.c_str());

	if(myFile.is_open())
	{

		for(mapIterator = m_mapPairs.begin(); mapIterator != m_mapPairs.end(); mapIterator++)
		{	
			strMapKey = mapIterator->first;
			int32 i = 0;

			while (strMapKey[i] != '|')
			{
				strSection += strMapKey[i];
				++i;
			}
			i += 1;
			while(strMapKey[i] != '\0')
			{
				strKey += strMapKey[i];
				++i;
			}

			strValue = mapIterator->second;

			if(strCurrentSection != strSection)
			{
				strCurrentSection = strSection;
				myFile << "[";
				myFile << strSection;
				myFile << "]" << std::endl;	
			}	
			myFile << strKey << " = " << strValue << std::endl;
			

			strSection.clear();
			strKey.clear();
			strValue.clear();
		}

		bIsSaved = true;

		myFile.close();
	}
	else
	{
		std::cout << "Opening file failed" << std::endl;
	}

	return bIsSaved; //default
}