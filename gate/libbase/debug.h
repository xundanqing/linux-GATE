/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : debug.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月27日
  最近修改   :
  功能描述   : debug.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月27日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DEBUG_H__
#define __DEBUG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern bool g_bErrorPrintFlag;

#define MODULE_NAME   "[Libbase]"

#if ERROR_PRINT_ON
#define ErrorPrint(format,...) \
{\
    if (g_bErrorPrintFlag) \
    {\
        printf(MODULE_NAME"[%s:%d][%s]:", __FILE__,  __LINE__, __FUNCTION__), \
        printf(format,##__VA_ARGS__), printf("\n");\
    }\
}
#else
#define ErrorPrint(format,...)
#endif

void SetErrorPrintFlag(bool bFlag);
void PrintBuffer(char *pchBuffName, char *pchBuff, int iLen);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DEBUG_H__ */




