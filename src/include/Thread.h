/*
 * =====================================================================================
 *
 *       Filename:  Thread.h
 *
 *    Description:  线程管理类，用于线程的创建
 *
 *        Version:  1.0
 *        Created:  2014年02月28日 15时48分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyankun (), liyankun@baidu.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef	 __THREAD_MANAGER_H_2014_02_28__
#define	 __THREAD_MANAGER_H_2014_02_28__

#include <iostream>
#include <vector>
#include "ThreadUtil.h"

class Thread
{
	public:
		//线程默认构造函数
		Thread();
		//线程初始化(线程创建、初始化互斥量、条件变量)
		int ThreadInit();
		//线程销毁
		int ThreadDestory();
		//线程追加任务
		int ThreadAdd(uint32_t value);

		//线程处理函数
		int ThreadDump(uint32_t value);
		//线程函数
		static void* ThreadFunc(void* args);

	private:
		std::vector<uint32_t>* m_pThreadWrite;	//往线程写入的队列
		std::vector<uint32_t>* m_pThreadDump;		//线程处理队列

		pthread_mutex_t m_mutex;		//当写的时候，需要加锁.交换队列的时候也需要加锁
		pthread_cond_t	m_cond;			//条件变量，这里还不清楚怎么处理条件变量呢

		bool m_run;						//线程是否运行

		pthread_t m_ptid;				//线程id
};

#endif
