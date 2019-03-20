/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : common.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月16日
  最近修改   :
  功能描述   : 公用常量及结构定义头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月16日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__


/*-------------------------------常量定义------------------------------------*/

#define RTN_SUCCESS            (0x00)       // 成功 正常
#define RTN_FAIL               (0x01)       // 失败 异常

#define ABS(val)   (((val) > 0) ? (val) : (-(val)))    // 计算绝对值

#define GATE_RCVE_TIME_OUT      (0x00)      // 接收超时

#define PATH_LEN_MAX            (128)       // 路径长度最大值

// 模块类型定义
#define MODULE_TYPE_INVALID     (0x00)      // 无效的模块类型
#define MODULE_TYPE_MIN         (0x2F)      // 模块类型最小值(校验使用)
#define MODULE_TYPE_BROADCAST   (0x30)      // 广播地址,发给所有模块
#define MODULE_TYPE_GATE        (0x31)      // 3GGATE模块
#define MODULE_TYPE_AV          (0x32)      // AV模块
#define MODULE_TYPE_GUI         (0x33)      // UI模块
#define MODULE_TYPE_BZQ         (0x34)      // 报站器模块
#define MODULE_TYPE_PHONE       (0x35)      // PHONE模块
#define MODULE_TYPE_ACCESS      (0x36)      // ACCESS模块(tm8726中使用)
#define MODULE_TYPE_BASIC       (0x36)      // BASIC模块(tm8721中使用)
#define MODULE_TYPE_MONITOR     (0x37)      // Monitor模块
#define MODULE_TYPE_PARA        (0x38)      // 参数模块
#define MODULE_TYPE_MCU         (0x39)      // 车载机模块
#define MODULE_TYPE_SCHDL       (0x3A)      // 调度模块
#define MODULE_TYPE_DATA_PROC   (0x3B)      // 数据处理模块
#define MODULE_TYPE_NET_UPDATE  (0x3C)      // 升级模块
#define MODULE_TYPE_WIFI        (0x3D)      // WIFI模块
#define MODULE_TYPE_SVR         (0x40)      // 服务器模块
#define MODULE_TYPE_MAX         (0x41)      // 模块类型最大值(校验使用)

#define CUR_MODULE              MODULE_TYPE_INVALID

#define FD_INVALID              (-1)        // Fd的无效值

#define CONNECT_STATUS_OK       (0x00)      // 连接状态 OK
#define CONNECT_STATUS_BAD      (0x01)      // 连接状态 断开

#define SOCK_ADDR_INET          (0x01)      // INET地址
#define SOCK_ADDR_UNIX          (0x02)      // UNIX本地

#define PACK_LEN_MAX            (2048)      // 包的最大长度

// 命令字定义
#define GATE_MOUDLE_REG_CMD     (0x01)      // 模块向Gate发送注册包命令字
#define GATE_HEART_BEAT_CMD     (0x02)      // 模块向Gate发送心跳包

#define GATE_LOCAL_PATH   "/tmp/tm_sock"    // GATE本地Sock file


// 向调度模块发送协议数据包
#define SendDataToSchdl(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_SCHDL; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向报站器模块发送协议数据包
#define SendDataToBzq(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_BZQ; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向Access模块发送协议数据包
#define SendDataToAccess(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_ACCESS; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向Svr模块发送协议数据包
#define SendDataToSvr(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_SVR; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向DataProc模块发送协议数据包
#define SendDataToDataProc(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_DATA_PROC; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向参数模块发送协议数据包
#define SendDataToPara(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_PARA; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向GUI模块发送协议数据包
#define SendDataToGui(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_GUI; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向升级模块发送协议数据包
#define SendDataToNetUpdate(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_NET_UPDATE; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向Gate模块发送协议数据包
#define SendDataToGate(pcGate, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_GATE; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToGate(pcGate, &tPackInfo, pchData, iDataLen); \
}

// 向单片机模块发送协议数据包
#define SendDataToMcu(pcSerial, chPackCmd, pchData, iDataLen)  \
{ \
    TPackInfo tPackInfo; \
\
    tPackInfo.chDestMdl = MODULE_TYPE_MCU; \
    tPackInfo.chSrcMdl  = CUR_MODULE; \
    tPackInfo.chPackId  = 0x00;  \
    tPackInfo.chCmd     = chPackCmd; \
\
    SendPackToSrlPrt(pcSerial, &tPackInfo, pchData, iDataLen); \
}


/*-------------------------------类型定义----------------------------------*/

typedef pthread_t          ThreadId;
typedef fd_set             FdSet;
typedef socklen_t          SocketLen;
typedef pthread_mutex_t    ThreadMutex;


/*-------------------------------结构定义----------------------------------*/
#pragma pack(1)

// 包描述信息
typedef struct tagTPackInfo
{
    char chDestMdl;  // 目标模块
    char chSrcMdl;   // 源模块
    char chPackId;   // 包Id
    char chCmd;      // 命令字
} TPackInfo, *PTPackInfo;

// 需要打包的数据描述
typedef struct tagTPackData
{
    char *pchPrefix;   // 包前缀
    int  iPrefixLen;   // 前缀长度
    char *pchData;     // 打包数据
    int  iDataLen;     // 打包数据长度
} TPackData, *PTPackData;

// 地址类型定义
typedef struct tagTAddr
{
    int iAddrType;  // 地址类型(SOCK_ADDR_INET或SOCK_ADDR_UNIX)
    TSockAddrIn tSockAddr;    // INET套接字地址
    TSockAddrUn tSockAddrUn;  // UNIX本地套接字地址
} TAddr, *PTAddr;

// 时间数据
typedef struct tagTTimeData
{
    char chYear;   // 年
    char chMonth;  // 月
    char chDay;    // 日
    char chHour;   // 时
    char chMin;    // 分
    char chSec;    // 秒
} TTimeData, *PTTimeData;

#pragma pack()

class CClient;
class CSerial;

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

bool  CheckModuleType(int iMdlType);    // 检查模块类型的有效性
int   CreatFifo(char *pchPath);         // 创建管道文件
short Reverse16(short sVal);            // short型变量的大小端转换
int   Reverse32(int iVal);              // int型变量的大小端转换
int   GetCompressTime(unsigned int &uiCmprsTime);  // 获取压缩格式的时间
int   GetCurTime(PTTimeData ptCurTime);            // 获取当前时间(格式NNYYDDHHMMSS)
void  EncryptData(unsigned char *pucEyptData);     // 加密投币机数据

// Gate转发数据打包
int PackGateData(PTPackData ptPackData, PTPackInfo ptPackInfo, char *pchData, short &sDataLen);
// 向Gate发送协议数据包
int SendPackToGate(CClient *pcGate, PTPackInfo ptPackInfo, char *pchData, int iDataLen);
int SendPackToSrlPrt(CSerial *pcSerial, PTPackInfo ptPackInfo, char *pchData, int iDataLen);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __COMMON_H__ */




