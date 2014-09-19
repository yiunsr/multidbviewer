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

/******************************************************************************
** ���� ���ۺο� GUI���� ���ÿ� ����ϴ� �͵��� ����
*/

#ifndef __MID_INTER_H__
#define __MID_INTER_H__

// NULL ���ǰ� �Ǿ� �ִ� �� stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>

using namespace std;

enum TraceType_t{
	emTraceType = 0,
	emTraceTest,
	emTraceUiProcess,
	emTraceProgramProcess,
	emTraceSQLQuery,
	emTraceExcetion, // �ý����� ���� ������ ������ �ƴ� ���ܻ���
	emTraceError,  // �Ͼ�� �ȵǴ� ��Ȳ
	emTraceTypeMax,
};



typedef void(*TraceCB_t)(const char *pszMessage)   ;

class MidInter{
	public:
		static MidInter* GetInstance()
		{
			if (m_pInstance == NULL)
				m_pInstance = new MidInter;
			return m_pInstance;
		}
		~MidInter();

		static void Finalize();
	private:
		MidInter();

		static MidInter* m_pInstance;
		static void (*m_functionPtr)(const char *pszMessage);

	private:
		static unsigned int m_bitmapLogOnTraceType;



	public:
		static void SetTraceCB( TraceCB_t functionPtr);
		static void Trace(TraceType_t traceType, const char *pszMessage);

};



#endif // __MID_INTER_H__
