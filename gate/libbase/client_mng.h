/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : client_mng.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年9月23日
  最近修改   :
  功能描述   : 客户端管理类
  函数列表   :
  修改历史   :
  1.日    期   : 2015年9月23日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CLIENT_MNG_H__
#define __CLIENT_MNG_H__

/*---------------------------------结构定义----------------------------------*/

#pragma pack(1)

// 客户端实例信息
typedef struct tagTClientInfo
{
    int iSvrType;      // 服务器类型
    CClient *pcClient; // 客户端实例指针
} TClientInfo, *PTClientInfo;

// 客户端实例列表
typedef struct tagTClientList
{
    int  iClientNum;        // 客户端数量
    char achClientInfo[0];  // 客户端实例信息集
} TClientList, *PTClientList;

#pragma pack()


/*----------------------------------类定义-----------------------------------*/

class CClientMng
{
public:
    CClientMng();
    CClientMng(PTClientList ptClientList);
    ~CClientMng();
    int  ConnectToAllSvr();  // 连接所有服务器
    int  DisCnctToAllSvr();  // 断开与所有服务器的连接
    int  AddClient(int iSvrType, CClient *pcClient);  // 增加客户端
    int  DelCilent(int iSvrType);  // 删除客户端
    int  ModifyClient(int iSvrType, PTAddr ptSvrAddr);  // 修改客户端
    bool GetAllConnectStatus();  // 获取所有服务器连接状态
    int  GetCnctFdTypeMap(map<int, int> &mpFdType); // 获取已连接客户端Fd与连接服务器类型的映射
    int  RecvData(int iSvrType, char *pchRecvBuff, int iBuffLen, int &iRecvLen);  // 从指定类型服务器接收数据
    int  SendData(int iSvrType, char *pchSendBuff, int iBuffSize);  // 向指定类型服务器发送数据
    int  ProcSvrData(int iSvrType, char *pchData, int iDataLen);    // 处理指定服务器类型的数据
    int  GetConnectStatus(int iSvrType, int &iStatus);  // 获取服务器连接状态
    int  IncRecvTimeOut(int iSvrType);    // 将指定服务器接收超时次数加1
    bool CheckSvrExist(int iSvrType);     // 判断指定类型服务器存在与否
    CClient* GetSvrClient(int iSvrType);  // 获取指定类型服务器的客户端
    int  DisCnctSvr(int iSvrType);  // 断开与指定服务器的连接

private:
    bool m_bAllSvrCnct;  // 所有服务器连接状态 true :所有服务器都已连接
                                            // false:不是所有服务器都已连接
    map<int, CClient*> m_mpTypeClient;      // <服务器类型, 对应客户端>

};


#endif /* __CLIENT_MNG_H__ */



