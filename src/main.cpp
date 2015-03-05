/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  这是一个主函数cpp
 *
 *        Version:  1.0
 *        Created:  2014年02月28日 17时48分48秒
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
#include "ThreadMgr.h"

int main(int argc, char** argv)
{

	ThreadMgr mgr;
	mgr.ThreadMgrInit();
	sleep(60);
	mgr.ThreadMgrDestory();

	return 0;
}
