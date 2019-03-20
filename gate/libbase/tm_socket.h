/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tmsocket.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年7月10日
  最近修改   :
  功能描述   : tmsocket.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月10日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TMSOCKET_H__
#define __TMSOCKET_H__

/*--------------------------------常量定义-----------------------------------*/

#define BIND_ERROR             (-1)         // bind调用返回错误
#define ACCEPT_ERROR           (-1)         // accept调用返回错误


/*--------------------------------类型定义-----------------------------------*/

typedef struct sockaddr    TSockAddr;
typedef struct sockaddr_un TSockAddrUn;
typedef struct sockaddr_in TSockAddrIn;
typedef struct timeval     TTimeVal;
typedef struct linger      TSoLinger;


/*--------------------------------接口定义-----------------------------------*/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

int WriteN(int iFd, char *pchBuff, int iWriteLen);                    // 写n个byte到描述符
int ReadN(int iFd, char *pchBuff, int iBuffLen, int &iReadLen);       // 从描述符读n个byte
int CnnctToServerUn(TSockAddrUn tSvrAddr, int *piSvrFd);              // 连接到Unix本地服务端
int CnnctToServerIn(TSockAddrIn tSvrAddr, int *piSvrFd);              // 连接到IP网络服务器
int StartServerUn(TSockAddrUn tSvrAddr, int *piSvrFd, int iLstnNum);  // 建立Unix服务端

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TMSOCKET_H__ */




