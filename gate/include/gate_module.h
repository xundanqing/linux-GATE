/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tmgate.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年7月10日
  最近修改   :
  功能描述   : 头文件集中整理
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月10日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TMGATE_H__
#define __TMGATE_H__


/*-------------------------------系统定义头文件------------------------------*/

#include <stdio.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <memory.h>
#include <termios.h>
#include <map>
#include <vector>


/*----------------------gate自定义头文件(有先后顺序)-------------------------*/

#include "tm_libbase.h"
#include "gate_server.h"
#include "gate.h"


/*----------------------------------宏定义-----------------------------------*/

// 模块名定义
#ifdef  MODULE_NAME
#undef  MODULE_NAME
#endif

#define MODULE_NAME          "[Gate]"

// 当前模块定义
#ifdef CUR_MODULE
#undef CUR_MODULE
#endif

#define CUR_MODULE   MODULE_TYPE_GATE


#endif /* __TMGATE_H__ */




