/*
 * =====================================================================================
 *
 *       Filename:  ThreadMgr.h
 *
 *    Description:  线程管理类(头文件) 
 *
 *        Version:  1.0
 *        Created:  2014年03月01日 10时55分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyankun (), liyankun@baidu.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __THREAD_MGR_H_2014_03_01__
#define __THREAD_MGR_H_2014_03_01__

#include "Thread.h"

class ThreadMgr
{
	public:
		ThreadMgr(uint32_t threadnum = 10):m_threadnum(threadnum)
		{
			m_pushindex = 0;
			m_pThreadArr = NULL;
			m_pde = false;
		}
		//线程初始化，用于创建线程
		bool ThreadMgrInit();
		//生产线程
		static void* ThreadProduce(void*);
		//线程管理退出
		bool ThreadMgrDestory();

	private:
		uint32_t  m_threadnum;
		uint32_t  m_pushindex;
		Thread* m_pThreadArr;
		pthread_t	m_ptid;
		bool m_pde;

};
#endif
