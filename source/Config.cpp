#include "Config.h"
#include <wx/dir.h>

const wxChar * FILE_NAME = _T("config.txt");


Config* Config::m_pInstance = NULL;

Config::Config()
{

	DefaultValue();
	ReadConfigValue();
}

Config::~Config()
{

}

void Config::Finalize()
{
	if(!m_pInstance)
		return;
	Config *pInstance = m_pInstance;
	m_pInstance = NULL;
	delete pInstance;
}

void Config::DefaultValue()
{
	m_nRecordPerTable = 100;
}


void Config::ReadConfigValue()
{
	wxFileInputStream fileStream(FILE_NAME);
	wxFileConfig fileConfig(fileStream);

	m_nRecordPerTable = fileConfig.Read(_T("/DBTable/RecodePerTable"), (long)m_nRecordPerTable);
	
}

