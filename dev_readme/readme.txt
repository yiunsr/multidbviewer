
==== [2009.10.27] ====



==== [2010.07.30] ====
	wxWidget �� Unicode ���忡��  wxString ���� utf-8 �� ���ڵ� �� const char * ��ȯ�ϱ� ���ؼ���
wxString  �� ��� �Լ�  mb_str(wxConvUTF8)  �� ����Ѵ�.
  �� �Լ��� ���� const char * ���� ���� ������ 
  const char *  szStrUTF8 =  wxStr.mb_str(wxConvUTF8);
 ���� ����ϸ� �ȵȴ�. �̹� ��ȯ�Ŀ� �����͸� �����ϱ� ������ ������ ���� ������ �ִ�.
 ( Ư��, Win32 �ý��ۿ���... )
 
 char * szBuffer[200];
 strcpy(szBuffer, wxStr.mb_str(wxConvUTF8)); 
 ���� ����ؾ� �Ѵ�. 
 
 
	SQLReader ��� class �� SQLDriver ��� ��Ī���� �����ϴ°� ���� ������?


==== [2011.06.14] ====



Execute���� CCI_INCLUDE_OID�� ������ ��� ���� fetch�� ���ڵ��� OID�� �����´�. OID�� page, slot, volume�� ���� ��Ʈ������ ǥ���ȴ�.

����
int cci_get_cur_oid(int req_handle, char *oid_str_buf)

