/*
 * =====================================================================================
 *
 *       Filename:  Thread.cpp
 *
 *    Description:  线程管理函数，实现cpp
 *
 *        Version:  1.0
 *        Created:  2014年02月28日 16时20分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyankun (), liyankun@baidu.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "Thread.h"

Thread::Thread()
{	
	LOGDBG("Thread Create ...");	
}

int Thread::ThreadInit()
{
	m_pThreadWrite = new (std::nothrow)std::vector<uint32_t>;
	if (NULL == m_pThreadWrite)
	{
		LOGERR("new thread write quque failed");
		return SYS_ERR;
	}

	m_pThreadDump = new (std::nothrow)std::vector<uint32_t>;
	if (NULL == m_pThreadDump)
	{
		LOGERR("new thread dump queue failed");
		return SYS_ERR;
	}

	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);

	m_run = false;

	int ret = pthread_create(&m_ptid, NULL, ThreadFunc, this);
	if (ret)
	{
		LOGERR("new thread failed");
		return SYS_ERR;
	}
	return 0;
}

int Thread::ThreadAdd(uint32_t value)
{
	pthread_mutex_lock(&m_mutex);
	m_pThreadWrite->push_back(value);
	pthread_mutex_unlock(&m_mutex);
	pthread_cond_signal(&m_cond);

	LOGDBG("add one element(%d)", value);
	return 0;
}
void* Thread::ThreadFunc(void* args)
{
	Thread* pMgr = (Thread*)args;
	pMgr->m_run = true;

	LOGDBG("Thread(%u) start ...", pMgr->m_ptid);
	if (pthread_self() != pMgr->m_ptid)
	{
		LOGERR("Thread(%u) exit ...", pMgr->m_ptid);
		return NULL;
	}
#define M(args)	(pMgr->args)
	std::vector<uint32_t>* temp;

	//在某些情况下，break while循环
	while(1)
	{
		pthread_mutex_lock(&M(m_mutex));
		//如果线程在运行着，同时队列为空,这里用if也是可以的
		while(M(m_pThreadWrite)->empty() && M(m_run))
		{
			pthread_cond_wait(&M(m_cond), &M(m_mutex));//发送信号一共两处，1新增节点2程序退出
		}	

		if (!M(m_run))
		{
			pthread_mutex_unlock(&M(m_mutex));
			LOGDBG("thread will exit ...");
			sleep(2);
			break;
		}

		temp = M(m_pThreadWrite);
		M(m_pThreadWrite) = M(m_pThreadDump);
		M(m_pThreadDump) = temp;
		pthread_mutex_unlock(&M(m_mutex));

		std::vector<uint32_t>::iterator it = M(m_pThreadDump)->begin();
		for(; it != M(m_pThreadDump)->end(); it++)
		{
			M(ThreadDump)(*it);
		}
		M(m_pThreadDump)->clear();

	}
	LOGDBG("thead exit...");
	return NULL;
}

int Thread::ThreadDump(uint32_t value)
{
	LOGDBG("ptid(%u)		dump value(%u)", m_ptid, value);
	sleep(3);
	return 0;
}

int Thread::ThreadDestory()
{
	m_run = false;
	pthread_cond_signal(&m_cond);
	pthread_join(m_ptid, NULL);
	//线程退出之后，在析构互斥变量和条件变量
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);

	//可以接着处理节点，然后再释放
	m_pThreadDump->clear();
	m_pThreadWrite->clear();
	delete m_pThreadDump;
	delete m_pThreadWrite;

	LOGDBG("thread_exit(%u)", m_ptid);
	return 0;
}

