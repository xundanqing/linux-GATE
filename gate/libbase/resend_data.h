/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : resend_data.h
  版 本 号   : 初稿
  作    者   : WangGaofeng
  生成日期   : 2016年3月28日
  最近修改   :
  功能描述   : 重发数据类
  函数列表   :
  修改历史   :
  1.日    期   : 2016年3月28日
    作    者   : WangGaofeng
    修改内容   : 创建文件

******************************************************************************/
#ifndef __RESEND_DATA_H__
#define __RESEND_DATA_H__


/*----------------------------------宏定义-----------------------------------*/

#define BIND_RSND_FNSH_FUNC(CLASS, FUNCTION)    bind(&CLASS::FUNCTION, this, _1, _2)
#define BIND_RSND_DT_FUNC(CLASS, FUNCTION)      bind(&CLASS::FUNCTION, this, _1, _2, _3, _4)
#define BIND_RSND_DT_FUNC_C(FUNCTION)           bind(&FUNCTION, _1, _2, _3, _4)

#define RSND_TIMES_INFINITE           (0xFF)                // 无限次重发


/*---------------------------------类型定义----------------------------------*/

typedef boost::function<int(void*, int)>    PReSndFnshFunc;
typedef boost::function<int(CClient*, PTPackInfo, char*, int)> PReSndDtFunc;


/*---------------------------------结构定义----------------------------------*/

#pragma pack(1)

// 重发数据包信息
typedef struct tagTReSndDtInfo
{
    char chDest;      // 数据包发送目的地址
    char chSrc;       // 数据包发送源地址
    char chCmd;       // 数据包命令字
    int  iDataLen;    // 数据包长度
    char achData[0];  // 重发数据包
} TReSndDtInfo, *PTReSndDtInfo;

#pragma pack()


/*----------------------------------类定义-----------------------------------*/

class CReSendData
{
public:
    CReSendData();
    CReSendData(TReSndDtInfo *ptReSndDtInfo, int iReSndInfoLen, CClient *pcGate);
    ~CReSendData();
    int ReSendData(void);                     // 重发数据
    int SetReSendTimes(char chReSendTimes);   // 设置重发次数
    int SetReSendInterval(int iInterval);     // 设置重发间隔
    int CheckReSendData(void);                // 检查是否重发
    int RegReSendFinishFunc(PReSndFnshFunc pfnReSndFnshFunc);  // 注册超次回调函数
    int RegReSendDataFunc(PReSndDtFunc pfnReSndDtFunc);        // 注册重发数据回调函数

private:
    PTReSndDtInfo m_ptReSndDtInfo;      // 重发数据信息
    char m_chReSendTimes;               // 重发次数
    int  m_iReSndIntvl;                 // 重发间隔
    char m_chSentTimes;                 // 已发送数据次数
    int  m_iSecCnt;                     // 两次重发间隔间秒计数
    PReSndFnshFunc m_pfnReSndFnshFunc;  // 超次回调函数
    PReSndDtFunc   m_pfnReSndDtFunc;    // 重发数据回调函数
    CClient       *m_pcGate;            // 连接Gate的客户端实例指针
};


#endif /* __RESEND_DATA_H__ */




