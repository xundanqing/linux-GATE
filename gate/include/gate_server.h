/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : Server.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月16日
  最近修改   :
  功能描述   : gateserver.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月16日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __GATESERVER_H__
#define __GATESERVER_H__


using namespace std;

/*------------------------------常量定义-------------------------------------*/
#define MOUDLE_NUM_MAX             (0x0A)  // GateSvr监听最大连接数

// GateSvr状态定义
#define GATESVR_STATUS_START       (0x01)  // GateSvr已启动
#define GATESVR_STATUS_STOP        (0x02)  // GateSvr已停止

#define GATE_MODULE_NAME_LEN_MAX   (64)    // 模块名字长度最大值

/*------------------------------结构定义-------------------------------------*/
#pragma pack(1)

typedef struct tagTGateClientInfo
{
    int iModuleType;  // 模块类型
    int iHrtBtTime;   // 接收到心跳包时间
    CDecoupler *pcDecoupler;  // 模块对应的分包器
} TGateClientInfo, *PTGateClientInfo;

typedef struct tagTMdlInfo
{
    char achKillMdlCmd[GATE_MODULE_NAME_LEN_MAX];
} TMdlInfo, *PTMdlInfo;

#pragma pack()


/*----------------------------- 类定义 --------------------------------------*/
class CGateSvr
{
public:
    CGateSvr();
    CGateSvr(TSockAddrUn *ptGateSvrAddr);
    virtual ~CGateSvr();
    virtual int StartGateSvr();    // 启动服务器
    virtual int StopGateSvr();     // 停止服务器
    virtual int AcceptConnect(TSockAddr *pstAddr, SocketLen &iAddrLen);    // 接受客户端连接
    virtual int RecvData(int iFd, char *pchBuff, int iLen, int &iRecvLen); // 接收数据
    virtual int SendData(int iFd, char *pchBuff, int iLen);   // 发送数据
    virtual int AddGateClient(int iFd);  // 增加模块
    virtual int UpdateGateClientType(int iFd, int iMdlType);  // 更新模块类型
    virtual int RemoveClient(int iFd);  // 移除模块
    virtual int RemoveAllClient();      // 移除所有模块
    virtual int GetGateSvrFd(int &iFd); // 获取服务器Fd
    virtual int GetAllMdlFd(vector<int> &vtFd); // 获取所有连接模块Fd
    virtual int GetFdByMdlType(int iMdlType, int &iFd); // 通过模块类型获取模块Fd
    virtual int GetGateSvrStatus(int &iStatus);  // 获取GateSvr状态
    virtual int GetModuleInfo(map<int, PTGateClientInfo> &mapModule);
    virtual CDecoupler* GetFdDecoupler(int iFd);
    virtual int UpdateHrtBtTime(int iFd, int iSrcMdl);  // 更新模块心跳包时间
    virtual int CheckMdlHrtBtTimeOut();

private:
    TSockAddrUn *m_ptGateSvrAddr;     // 通讯文件路径
    int         m_iSvrFd;             // 服务器Fd
    int         m_iStatus;            // 服务器状态
    ThreadMutex m_tMutex;             // 放入数据和取数据互斥使用
    map<int, PTGateClientInfo> m_mapMdlContainer; // 与GateSvr连接的模块容器<模块Fd, 模块信息>
    map<int, PTMdlInfo> m_mapMdlInfo; // 模块信息映射，心跳超时kill模块使用
};



#endif /* __SERVER_H__ */




