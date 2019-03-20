/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : crcpublic.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月17日
  最近修改   :
  功能描述   : crcpublic.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CRCPUBLIC_H__
#define __CRCPUBLIC_H__

class CCrcPublic
{
 public:
    CCrcPublic();
    virtual ~CCrcPublic();
    virtual unsigned short Crc16(unsigned char *pucDt, unsigned short usLen);     // CRC16计算
    virtual unsigned short Crc16Big(unsigned char *pucDt, unsigned short usLen);  // CRC16计算(输出为大端模式)
    virtual unsigned char  Crc8(unsigned char *pucDt, unsigned short usLen);      // CRC8计算
 private:
    static const unsigned short m_asCrc16Tab[256];  // CRC16表格
    static const unsigned char  m_aucCrc8Tab[256];  // CRC8表格
};

#endif




