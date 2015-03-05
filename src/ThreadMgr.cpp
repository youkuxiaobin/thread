/*
 * =====================================================================================
 *
 *       Filename:  ThreadMgr.cpp
 *
 *    Description:  线程管理类(实现类)
 *
 *        Version:  1.0
 *        Created:  2014年03月01日 10时55分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyankun (), liyankun@baidu.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "ThreadMgr.h"

//创建生产线程，消费线程
bool ThreadMgr::ThreadMgrInit()
{
	assert(m_threadnum > 0);

	m_pThreadArr = new (std::nothrow)Thread[m_threadnum];
	if (NULL == m_pThreadArr)
	{
		LOGERR("new thread failed");
		return false;
	}

	int i = 0, ret;
	for(; i<m_threadnum; i++)
	{
		ret = m_pThreadArr[i].ThreadInit();
		if (ret)
		{
			LOGERR("thread initialize failed");
			return false;
		}
	}

	ret = pthread_create(&m_ptid, NULL, ThreadProduce, this);
	if (ret)
	{
		LOGDBG("thread create failed");
		return false;
	}
	m_pde = true;
}

void* ThreadMgr::ThreadProduce(void* args)
{
	ThreadMgr *tmgr = (ThreadMgr*)args;
#define M(args) (tmgr->args)	
	while(1)
	{
		if (!M(m_pde))
		{
			LOGDBG("produce thread will exit ...");
			break;
		}
		M(m_pThreadArr)[M(m_pushindex)%M(m_threadnum)].ThreadAdd(M(m_pushindex));
		M(m_pushindex)++;
		LOGDBG("##########produce(%u)", M(m_pushindex));
		sleep(2);
	}
	return NULL;
}

bool ThreadMgr::ThreadMgrDestory()
{
	m_pde = false;
	pthread_join(m_ptid,NULL);
	for(int i =0; i<m_threadnum; i++)
	{
		m_pThreadArr[i].ThreadDestory();
	}
	return true;	
}

