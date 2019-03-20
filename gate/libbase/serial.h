/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : serial.h
  版 本 号   : 初稿
  作    者   : WangGaofeng
  生成日期   : 2016年4月20日
  最近修改   :
  功能描述   : 串口类
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月20日
    作    者   : WangGaofeng
    修改内容   : 创建文件

******************************************************************************/
#ifndef __SERIAL_H__
#define __SERIAL_H__


/*----------------------------------宏定义-----------------------------------*/

#define BIND_SRL_PT_FUNC(CLASS, FUNCTION)       bind(&CLASS::FUNCTION, this, _1, _2, _3)
#define BIND_SRL_CNT_SCS_FUNC(CLASS, FUNCTION)  bind(&CLASS::FUNCTION, this, _1)

#define SERIAL_PORT_NAME_LEN_MAX             (0x80)   // 串口名字长度最大值(128)


/*---------------------------------类型定义----------------------------------*/

class CSerial;

typedef boost::function<int(char, char*, int)>  PSrlPrtFunc;
typedef boost::function<int(CSerial* )>      PSrlCntScsFunc;


/*----------------------------------类定义-----------------------------------*/

class CSerial
{
public:
    CSerial();
    CSerial(char *pchSrlPrtNm, int iBaud, CDecoupler *pcSrlPrtDcplr);
    ~CSerial();
    int InitSerialPort();  // 初始化串口
    int OpenSerialPort();  // 打开串口
    int CfgSerialPort(int iBaud);   // 配置串口
    int DisCnctSrlPrt();   // 断开串口
    int SendData(char *pchSendData, int iSendLen);   // 从串口发送数据
    int RecvData(char *pchRecvBuff, int iRecvBuffLen, int &iRecvLen);  // 从串口接收数据
    int GetConnectStatus(int &iCnctStus);  // 获取串口连接状态
    int GetConnectFd(int &iFd);  // 获取串口连接的描述符
    int RegSerialPortCmdFunc(char chCmd, PSrlPrtFunc pfnSrlPrtFunc);  // 注册串口命令字处理函数
    int ProcSerialPortData(char chCmd, char *pchData, int iDataLen);  // 处理串口数据
    int PutDataToDcplr(char *pchData, int iDataLen);  // 将数据放入分包器
    int GetPackInfo(PTPackInfo ptPackInfo, char *pchPackData, int iPackBufSize, int &iPackLen);  // 获取分包数据
    int RegCnctSucsFunc(PSrlCntScsFunc pfnCntScsFunc);  // 注册串口连接成功处理函数
    bool IsDecouplerEmpty();  // 分包器是否为空

private:
    CCmdProc<char, PSrlPrtFunc, char*, int> m_cSrlPtProc;    // 串口命令处理类
    char m_achSrlPtNm[SERIAL_PORT_NAME_LEN_MAX];             // 串口名
    CDecoupler *m_pcSrlPtDplr;          // 分包器实例
    PSrlCntScsFunc m_pfnSrlCntScsFunc;  // 串口连接处理函数
    int m_iSrlPrtFd;     // 串口连接Fd
    int m_iSrlCnctStus;  // 串口连接状态
    int m_iBaud;  // 串口波特率
};


#endif /* __SERIAL_H__ */




