/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tm_can_data_send.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年10月17日
  最近修改   :
  功能描述   : 天迈CAN协议数据发送拆包类声明
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TM_CAN_DATA_SEND_H__
#define __TM_CAN_DATA_SEND_H__

/*----------------------------------宏定义-----------------------------------*/

#define TM_CAN_DATA_LEN_MAX             (0x07)    // 天迈CAN数据包中数据长度最大值
#define CAN_DATA_LEN_MAX                (0x08)    // CAN数据包长度最大值
#define TM_CAN_END_PACK_FLAG            (0x00)    // 天迈CAN结束包标志
#define TM_CAN_CONTINUE_PACK_FLAG       (0x80)    // 天迈CAN后续包标志


/*----------------------------------类定义-----------------------------------*/

class CTmCanDataSend
{
public:
    CTmCanDataSend();
    ~CTmCanDataSend();
    int PutData(char chDestNode, char chSrcNode, char *pchData, int iDataLen);  // 将发送数据放入缓存
    int GetCanDataPack(unsigned int &uiCanId, char *pchCanDataPack, int &iPackLen, bool &bEndPack);  // 获取CAN数据包
    int CalcCanId(unsigned int &uiCanId);  // 计算CAN Id

private:
    char m_chCurFrmNo;   // 当前帧序号
    char m_chDestNode;   // CAN数据发送目的节点
    char m_chSrcNode;    // CAN数据发送源节点
    int  m_iRestLen;     // 剩余数据长度
    CCirQue *m_pcSendBuff;  // 存放CAN数据的循环队列
};


#endif /* __TM_CAN_DATA_SEND_H__ */




