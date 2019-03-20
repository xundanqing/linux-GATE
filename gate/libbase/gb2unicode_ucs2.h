/******************************************************************************

  Copyright (C), 2001-2011, DCN Co., Ltd.

 ******************************************************************************
  File Name     : gb2unicode_ucs2.h
  Version       : Initial Draft
  Author        : wuquanwei
  Created       : 2015/9/14
  Last Modified :
  Description   : gb2unicode_ucs2.c header file
  Function List :
  History       :
  1.Date        : 2015/9/14
    Author      : wuquanwei
    Modification: Created file

******************************************************************************/
#ifndef __GB2UNICODE_UCS2_H__
#define __GB2UNICODE_UCS2_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


extern int Gbk2Utf8(const unsigned char *gb2132Data, int gb2132DataLen, char *utf8Data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GB2UNICODE_UCS2_H__ */
