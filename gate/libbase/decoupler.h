/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : decoupler.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月17日
  最近修改   :
  功能描述   : decoupler.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DECOUPLER_H__
#define __DECOUPLER_H__


#define PREFIX_LEN_MAX               (4)        // 前缀最大长度
#define PACK_OFFSET_COMMON           (6)        // (前缀+包长度)的字节数
// 包数据偏移
#define PACK_DATA_OFFSET             (PACK_OFFSET_COMMON + sizeof(TPackInfo))
#define CRC16_VAL_LEN                (0x02)     // CRC16值长度

// 分包器状态定义
#define PACK_STATUS_INIT             (0x01)     // 初始状态
#define PACK_STATUS_GET_PREFIX       (0x02)     // 找到前缀
#define PACK_STATUS_GET_LENGTH       (0x03)     // 取到长度
#define PACK_STATUS_DECOUPLE_OK      (0x04)     // 分包完成

#define BUFF_SIZE                    (2048)     // 缓冲区大小定义

class CDecoupler
{
public:
    CDecoupler();
    CDecoupler(char *pchPrefix, int iPrefixLen, int iQueBufSize);
    virtual ~CDecoupler();
    int  PutData(const char *pchBuff, int iCount);         // 往分包器中输入需要分包的数据
    int  GetData(char *pchBuff, int iLen, int &iPackLen);  // 获取分包完成的数据
    int  SetPrefix(char *pchPrefix, int iPrefixLen);       // 设置分包器前缀
    int  FindPrefix();                                     // 从数据中查找前缀
    bool IsDcplrEmpty();    // 判断分包器中是否还有数据
    virtual int GetPackInfo(PTPackInfo ptPackInfo, char *pchPackData, int iPackBuffSize, int &iPackLen);   // 获取包描述信息

private:
    int     m_iStatus;     // 分包器状态
    char    m_achPrefix[PREFIX_LEN_MAX];  // 包前缀
    int     m_iPrefixLen;  // 前缀长度
    short   m_sPackLen;    // 包长度
    CCirQue *m_pcCirQue;   // 循环队列
    int     m_iCirQueLen;  // 循环队列缓存长度
    ThreadMutex m_tMutex;  // 放入数据和取数据互斥使用
};

#endif /* __DECOUPLER_H__ */




