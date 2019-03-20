/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : can_data_recv.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年11月09日
  最近修改   :
  功能描述   : CAN数据接收处理类相关定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月09日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CAN_DATA_RECV_H__
#define __CAN_DATA_RECV_H__


class CCanDataRecv
{
public:
    CCanDataRecv();
    CCanDataRecv(CCanDataMng *pcCanDataMng);
    ~CCanDataRecv();
    int Init();  // 初始化
    int ProcRecvCanData(int iCanId, char *pchCanData, int iDataLen);  // 处理接收到的CAN数据

private:
    CCanDataMng *m_pcCanDataMng;  // CAN数据处理管理

};


#endif /*__CAN_DATA_RECV_H__*/




