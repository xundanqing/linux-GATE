/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tmbaselib.h
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
#ifndef __TMBASELIB_H__
#define __TMBASELIB_H__


/*-------------------------------系统定义头文件------------------------------*/

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <map>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <termios.h>


/*----------------------baselib自定义头文件(有先后顺序)----------------------*/

#include "print_color.h"
#include "zlog.h"
#include "lib_config.h"
#include "log_mng.h"
#include "debug.h"
#include "tm_socket.h"
#include "common.h"
#include "crc_public.h"
#include "circular_queue.h"
#include "decoupler.h"
#include "gb2unicode_ucs2.h"
#include "client.h"
#include "client_mng.h"
#include "cmd_proc.h"
#include "serial.h"
#include "tm_can_pack_info_mng.h"
#include "tm_can_data_send.h"
#include "tm_can_data_recv.h"
#include "timer.h"
#include "can_data.h"
#include "can_data_mng.h"
#include "can_data_recv.h"
#include "resend_data.h"
#include "resend_data_mng.h"


#endif /* __TMBASELIB_H__ */




