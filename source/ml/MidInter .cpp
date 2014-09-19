

#ifndef MID_INTER_CPP
#define MID_INTER_CPP

#include "MidInter.h"
// NULL 정의가 되어 있는 곳 stddef : gcc ,  stdlib :  visual c++
#include <cstddef>
#include <cstdlib>

#define ALL_LOG_ON	0xFFFFFFFF
#define ALL_LOG_OFF	0x00000000


MidInter* MidInter::m_pInstance = NULL;
unsigned int  MidInter::m_bitmapLogOnTraceType = ALL_LOG_ON;

void (*MidInter::m_functionPtr)(const char *m_pszMessage) = NULL;

MidInter::MidInter()
{
}


MidInter::~MidInter()
{
}

void MidInter::Finalize()
{
	if(!m_pInstance)
		return;
	MidInter *pInstance = m_pInstance;
	m_pInstance = NULL;
	delete pInstance;
}


void MidInter::SetTraceCB(TraceCB_t functionPtr)
{
		m_functionPtr = functionPtr;
}


void MidInter::Trace(TraceType_t traceType, const char *pszMessage)
{
	if( (m_bitmapLogOnTraceType & (0x01<<traceType)) == 0 )
		return;


	if(m_functionPtr)
		m_functionPtr(pszMessage);
}

#endif // MID_INTER_CPP

