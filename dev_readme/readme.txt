
==== [2009.10.27] ====



==== [2010.07.30] ====
	wxWidget 를 Unicode 빌드에서  wxString 에서 utf-8 로 인코딩 된 const char * 변환하기 위해서는
wxString  의 멤버 함수  mb_str(wxConvUTF8)  를 사용한다.
  이 함수를 통해 const char * 형을 얻을 때에는 
  const char *  szStrUTF8 =  wxStr.mb_str(wxConvUTF8);
 같이 사용하면 안된다. 이미 반환후에 테이터를 삭제하기 때문에 쓰래기 값을 가지고 있다.
 ( 특히, Win32 시스템에서... )
 
 char * szBuffer[200];
 strcpy(szBuffer, wxStr.mb_str(wxConvUTF8)); 
 같이 사용해야 한다. 
 
 
	SQLReader 라는 class 는 SQLDriver 라는 명칭으로 변경하는게 맞지 않을까?


==== [2011.06.14] ====



Execute에서 CCI_INCLUDE_OID가 설정된 경우 현재 fetch된 레코드의 OID를 가져온다. OID는 page, slot, volume에 의한 스트링으로 표현된다.

구문
int cci_get_cur_oid(int req_handle, char *oid_str_buf)

