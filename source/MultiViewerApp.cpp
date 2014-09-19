/***************************************************************
 * Name:      MultiViewerApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2009-11-15
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MultiViewerApp.h"
#include "MultiViewerMain.h"


// Visual Studio 에서 메모리 릭 체크를 위해서
//#if _MSC_VER
//	#define _CRTDBG_MAP_ALLOC
//	#include <stdlib.h>
//	#include <crtdbg.h>
//	#include <iostream>
//#endif



IMPLEMENT_APP(MultiViewerApp);

bool MultiViewerApp::OnInit()
{
//#if _MSC_VER
//	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//#endif

    MultiViewerMain* frame = new MultiViewerMain(0L);
#if WIN32
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
#endif
    frame->Show();
    
    return true;
}


int MultiViewerApp::OnExit()
{

//#if _MSC_VER
//	_CrtDumpMemoryLeaks();
//#endif

	return 0;
}

