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
#ifndef __SQLUTIL_H__
#define __SQLUTIL_H__

#include <string>
#include <wx/string.h>

class SQLUtil
{
public:
	static std::string wxstr2str(wxString a_wxStr);
	static wxString str2wxstr(std::string a_Str);
	static void AlertDlg(wxString a_wxStr);
	
	
};


#endif // __SQLUTIL_H__
