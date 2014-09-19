

This program is Database viewer. It work on buntu and windows.

This version only support sqlite. Next Version will support cubrid. 



It test on Windows 7 + Visual Studio
2008 and Windows 7 + Mingw + codeblock 8.02 and ubuntu 11.04 + codeblock 10.05 + gcc 4.5.2

This project build on visual studio 2008( build_vs/MultiViewer.sln) , codeblocks(build_cb/MultiDBViewer.cbp).



Build on Windows using visual studio.
1. build wxwidget first. (using visual studio)
  compile wx.dsw or wx_dll.dsw (wxwidget\build\msw ) 
  (  http://wiki.wxwidgets.org/Microsoft_Visual_C%2B%2B_Guide  )
2. open build_vs/MultiViewer.sln 
3. set build target same as wxwidget compile.
(If 1st step wxwidget compile target DLL Unicode Debug, MultiViewer.sln build target shoud be
 DLL Unicode Debug )
 


Build on Windows using codeblocks(mingw)
1.  compile wxWidget 
   mingw32-make -f makefile.gcc MONOLITHIC=1 SHARED=1 UNICODE=1 BUILD=debug   or
   mingw32-make -f makefile.gcc MONOLITHIC=1 SHARED=1 UNICODE=1 BUILD=release
    (http://wiki.wxwidgets.org/CodeBlocks_Setup_Guide)
2. open build_cb/MultiDBViewer.cbp with codeblock
3. set build target Win_Debug or Win_Release


Build on Ubuntu using codeblocks
1. install wxWidget
   libwxgtk2.8-dev libwxgtk2.8-dbg (http://wiki.wxwidgets.org/Installing_and_configuring_under_Ubuntu)
2.  open build_cb/MultiDBViewer.cbp with codeblock
3. set build target Linux_Debug or Linux_Release



