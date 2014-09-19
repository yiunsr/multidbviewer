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
** 실제 동작부와 GUI에서 동시에 사용하는 것들을 정의
*/

#ifndef __MID_INTER_H__
#define __MID_INTER_H__

// NULL 정의가 되어 있는 곳 stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>

using namespace std;

enum TraceType_t{
	emTraceType = 0,
	emTraceTest,
	emTraceUiProcess,
	emTraceProgramProcess,
	emTraceSQLQuery,
	emTraceExcetion, // 시스템을 멈출 정도의 에러는 아닌 예외사항
	emTraceError,  // 일어나면 안되는 상황
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
