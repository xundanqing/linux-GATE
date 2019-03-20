/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : client.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年9月23日
  最近修改   :
  功能描述   : 客户端功能类
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月23日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CLIENT_H__
#define __CLIENT_H__


using namespace std;

class CClient;    // 向前引用声明


/*---------------------------------类型定义----------------------------------*/

typedef boost::function<int(PTPackInfo, char*, int)> PClientCmdFunc;
typedef boost::function<int(CClient *)>  PCnctSucsFunc;
typedef boost::function<int(CClient *)>  PDisCnctFunc;


/*---------------------------------结构定义----------------------------------*/
#pragma pack(1)

// 客户端与服务器间连接状态
typedef struct tagTSvrConStatus
{
    char chSvrType;  // 服务器类型
    char chStatus;   // 连接状态
} TSvrConStatus, *PTSvrConStatus;

typedef struct tagTRecvTimeOutPara
{
    bool bValid;        // 是否启用接收超时处理
    int  iTmIntrvl;     // select时间间隔
    int  iNtcTmLen;     // 超时提醒时长
    int  iHrtTmLen;     // 超时发送心跳包时长
    int  iHrtPackLen;   // 心跳包长度
    char achHrtPack[0]; // 心跳包
} TRvTmOutPara, *PTRvTmOutPara;

typedef struct tagTRvTmOutInfo
{
    bool bValid;       // 是否启动接收超时处理
    int  iRvTmOut;     // 接收超时次数
    int  iNtcTimes;    // 打印超时提醒超时次数
    int  iHrtTimes;    // 发送心跳包超时次数
    int  iHrtPackLen;  // 心跳包长度
    char *pchHrtPack;  // 心跳包
} TRvTmOutInfo, *PTRvTmOutInfo;

#pragma pack()


/*----------------------------------宏定义-----------------------------------*/

#define BIND_CLIENT_FUNC(CLASS, FUNCTION)    bind(&CLASS::FUNCTION, this, _1, _2, _3)
#define BIND_CNCT_SUCS_FUNC(CLASS, FUNCTION) bind(&CLASS::FUNCTION, this, _1)
#define BIND_DIS_CNCT_FUNC(CLASS, FUNCTION)  bind(&CLASS::FUNCTION, this, _1)

#define SVR_TYPE_GATE                (0x00)     // Gate服务器
#define SVR_TYPE_SCHDL               (0x01)     // 调度服务器


/*----------------------------------类定义-----------------------------------*/

class CClient
{
public:
    CClient();
    CClient(PTAddr ptSvrAddr, int iSvrType, CDecoupler *pcDecoupler, PTRvTmOutPara ptRvTmOutPara = NULL);
    ~CClient();
    int ConnectToSvr();   // 连接到服务器
    int DisConctToSvr();  // 断开与服务器的连接
    int SendData(char *pchSendBuff, int iDataLen);  // 向服务器发送数据
    int RecvData(char *pchRecvBuff, int iBuffSize, int &iRecvLen);  // 接收服务器数据
    int GetConnectFd(int &iFd);  // 获取与服务器连接Fd
    int GetConnectStatus(int &iStatus);  // 获取与服务器连接状态
    int GetSvrType(int &iSvrType);  // 获取连接的服务器类型
    int ModifySvrAddr(PTAddr ptSvrAddr);  // 修改连接服务器的地址
    int RegCmdFunc(char chCmd, char chSrcMdl, PClientCmdFunc pfnCmdFunc);  // 注册服务器命令字处理函数
    int ProcessSvrData(PTPackInfo ptPackInfo, char *pchPackData, int iPackLen);  // 处理服务器命令
    int PutDataInDecoupler(char *pchData, int iDataLen);  // 将数据放入分包器
    int GetPackInfo(PTPackInfo ptPackInfo, char *pchPackData, int iPackBuffSize, int &iPackLen);  // 获取分包数据
    bool IsDcplrEmpty();   // 判断分包器中是否还有数据
    int IncRecvTimeOut();  // 接收超时次数加1
    int AddCnctSucsFunc(PCnctSucsFunc pfnCnctSucsFunc); // 添加连接成功处理函数
    int AddDisCnctFunc(PDisCnctFunc pfnDisCnctFunc);    // 添加连接断开处理函数
    int UpdateHeartBeatPacket(char *pchHtBtPkt, int iPkLen);  // 更新心跳包数据

private:
    TAddr m_tSvrAddr;  // 服务器地址
    int   m_iSvrType;  // 服务器类型
    int   m_iFd;       // 与服务器连接Fd
    int   m_iStatus;   // 与服务器连接状态
    TRvTmOutInfo m_tRvTmOutInfo;  // 接收超时处理信息
    CDecoupler  *m_pcDecoupler;   // 分包器
    map<int, map<int, vector<PClientCmdFunc> > > m_mpCmdMap;  // <命令字, <源模块, <回调函数集合> > >
    PCnctSucsFunc m_pfnCnctSucsFunc;  // 连接成功处理函数
    PDisCnctFunc  m_pfnDisCnctFunc;   // 连接失败处理函数

};


#endif /* __CLIENT_H__ */




