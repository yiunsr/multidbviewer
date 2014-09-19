/***************************************************************
 * Name:      MultiViewerApp.h
 * Purpose:   Defines Application Class
 * Created:   2009-11-15
 * License: MPL 1.1
 **************************************************************/
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

#ifndef __MultiViewERAPP_H__
#define __MultiViewERAPP_H__

#include <wx/app.h>

class MultiViewerApp : public wxApp
{
    public:
        virtual bool OnInit();
		virtual int OnExit();
};

#endif // __MultiViewERAPP_H__
