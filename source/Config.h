//The contents of this file are subject to the Mozilla Public License Version 1.1 
//(the "License"); you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//http://www.mozilla.org/MPL/
//
//Software distributed under the License is distributed on an "AS IS" basis,
//WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
//specific language governing rights and limitations under the License.
//
//The Original Code is MultiDBViewer(http://code.google.com/p/multidbviewer/).
//The Initial Developer of the Original Code is Yiun Seungryong(http://yiunsr.tistory.com/) .
// Portions created by  Initial Developer are Copyright (C) 2011 the Initial Developer.
//All Rights Reserved.
//Contributor(s): Yiun Seungryong(http://yiunsr.tistory.com/)


#ifndef __CONFIG_H__
#define __CONFIG_H__

#define __VERSION__ "0.1"

// 테스트시 일일이 File Load 아이콘을 눌러 찾아서 로드하기가 힘들어서 프로그램
// 실행시 자동으로 로드되게 하는 옵션
//#define DEBUG_AUTO_FILE_LOAD 1


//#define __CUBRID__SUPPORT__


#include <wx/fileconf.h>
#include <wx/wfstream.h>


#define TABLE_NAME_DLG_ST_TABLE_NAME  "Table Name : "
#define TABLE_NAME_DLG_ST_NEW_TABLE_NAME  "New Table Name : "

#pragma warning( disable : 4996 )


class Config
{
public:
static Config* GetInstance()
		{
			if (m_pInstance == NULL)
				m_pInstance = new Config;
			return m_pInstance;
		}
		~Config();
		static void Finalize();

private:
	static Config* m_pInstance;
	Config();


public:
	int GetRecordPerTable(){	return m_nRecordPerTable;	}


private:
	void ReadConfigValue();
	void DefaultValue();

private:
	int m_nRecordPerTable;
	
	
};


#endif // __CONFIG_H__
