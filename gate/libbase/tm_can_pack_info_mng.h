/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tm_can_pack_info_mng.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年10月17日
  最近修改   :
  功能描述   : 天迈CAN协议数据接收信息管理类定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月19日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TM_CAN_PACK_INFO_MNG_H__
#define __TM_CAN_PACK_INFO_MNG_H__


/*---------------------------------结构定义----------------------------------*/
#pragma pack(1)

// 天迈CAN协议CAN数据信息
typedef struct tagTTmCanDataInfo
{
    char chDestNode;  // 数据发送目的节点
    char chSrcNode;   // 数据源节点
    char chFrmNo;     // 帧序号
    char chFrmFlag;   // CAN数据包标志
} TTmCanDataInfo, *PTTmCanDataInfo;

#pragma pack()


/*----------------------------------类定义-----------------------------------*/

class CTmCanPackInfoMng
{
public:
    CTmCanPackInfoMng();
    ~CTmCanPackInfoMng();
    int PutCanData(PTTmCanDataInfo ptCanDataInfo, char *pchCanData, int iDataLen);  // 将CAN数据存放组包
    int GetCanPackStatus(int &iStatus);              // 获取CAN数据包接收状态
    int GetCanPack(char *pchCanPack, int &iPackLen); // 获取CAN数据包
    int SetCanPackDestNode(char chDestNode);   // 设置CAN包的目的节点
    int GetCanPackDestNode(char &chDestNode);  // 获取CAN包的目的节点

private:
    char m_chDestNode;   // CAN包发送目的节点
    int  m_iRecvLen;     // 接收数据长度
    int  m_iRecvFinish;  // 接收完成
    int  m_iEndFrmNo;    // 结束帧序号
    int  m_iEndFrmLen;   // 结束帧长度
    int  m_iPackStatus;  // 包状态
    vector<char> m_vtRecvFrmNo;   // 接收到的帧序号
    char m_achPack[PACK_LEN_MAX]; // 组包数据
};


#endif /* __TM_CAN_PACK_INFO_MNG_H__ */




