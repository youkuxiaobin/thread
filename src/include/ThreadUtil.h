/*
 * =====================================================================================
 *
 *       Filename:  ThreadUtil.h
 *
 *    Description:  线程工具类
 *
 *        Version:  1.0
 *        Created:  2014年02月28日 15时49分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liyankun (), liyankun@baidu.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef	 __THREAD_UTIL_H_20140228__
#define	 __THREAD_UTIL_H_20140228__

#include <stdio.h>
#include <string.h>
#include <errno.h>

//DEBUG
#define LOGDBG(fmt, argv...) do {\
	printf("DBG[%s:%d]	%s	"fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##argv);\
}while(0)

//ERRMSG
#define LOGERR(fmt, argv...) do {\
	printf("ERR[%s:%d]	%s	"fmt"(%s)\n", __FILE__, __LINE__, __FUNCTION__, ##argv, strerror(errno));\
}while(0)	

enum 
{
	RET_SUC,
	SYS_ERR,
	PRO_ERR,
	OTH_ERR
};
#endif
