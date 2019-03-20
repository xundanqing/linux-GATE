/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : gate.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月17日
  最近修改   :
  功能描述   : gate.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __GTAE_H__
#define __GTAE_H__


/*------------------------------常量定义------------------------------------*/

#define REG_ACK_PACK_LEN             (0x0C)       // 模块注册应答包长度
#define REG_ACK_PACK_PREFIX_LEN      (0x04)       // 应答包前缀长度

#define GATE_INFO_GATESVR            (0x01)       // GateSvr的运行信息
#define GATE_INFO_MODULE             (0x02)       // 连接GateSvr的模块运行信息
#define GATE_INFO_ALL                (0x03)       // GateSvr和module的信息

#define GATE_DEBUG_FIFO      "/tmp/gate_debug"    // 调试使用管道文件

#define GATE_HEART_BEAT_TIME_INVALID       (-1)   // 接收心跳包时间无效值
#define GATE_HEART_BEAT_TIME_OUT_LEN       (60)   // 模块心跳超时时长
#define GATE_HEEAT_BEAT_TIME_OUT_FILTER    (600)  // 过滤系统启动没有校时导致错杀模块的情况


/*-------------------------------类定义-------------------------------------*/

class CGate
{
public:
    CGate();
    CGate(TSockAddrUn *ptGateSvrAddr);
    ~CGate();
    int Init();         // 初始化
    int ProcessData();  // Gate数据转发处理
    static void* ProcessDebugCmd(void *pArg);   // 处理调试命令
    static void* CheckMdlHrtBtTime(void *pArg); // 检查模块心跳超时
    int CreatHrtBtThread();     // 创建心跳处理线程
    int CreatDebugCmdThread();  // 创建调试命令处理线程
    int ProcessGateData(int iFd, PTPackInfo ptPackInfo, char *pchPackData, int iDataLen); // 处理发给3GGate的数据包
    int ProcessBroadcast(int iFd, char *pchPackData, int iDataLen);
    int SendRegAckPacket(int iFd, PTPackInfo ptPackInfo);
    int CheckGateSvrData(int &iGateSvrFd, FdSet &fdReadSet);      // 检查服务器端是否可读
    int CheckClientData(vector<int> &vtMdlFd, FdSet &fdReadSet);  // 检查客户端是否可读
    int ShowGateRunInfo(int iShowType);   // 打印Gate的运行信息
    int ShowGateSvrInfo();  // 打印GateSvr的信息
    int ShowModuleInfo();   // 打印连接模块的信息
    int CheckHrtBtTimeOut();

private:
    CGateSvr   m_cGateSvr;  // 3GGate服务器
    TLog       *m_ptLogHdl;  // 日志文件
};

#endif /* __GTAE_H__ */




