/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : tm_can_data_recv.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年10月17日
  最近修改   :
  功能描述   : 天迈CAN协议数据接收组包类声明
  函数列表   :
  修改历史   :
  1.日    期   : 2015年10月19日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TM_CAN_DATA_RECV_H__
#define __TM_CAN_DATA_RECV_H__


using namespace std;


/*----------------------------------宏定义-----------------------------------*/

#define CAN_FRAME_NO_INVALID       (-1)      // CAN帧序号无效值
#define CAN_DATA_RECV_WORKING      (0x00)    // CAN数据接收进行中
#define CAN_DATA_RECV_FINISH       (0x01)    // CAN数据接收完成
#define CAN_PACK_STATUS_NORMAL     (0x00)    // CAN组包状态正常
#define CAN_PACK_STATUS_ERROR      (0x01)    // CAN组包状态异常


/*----------------------------------类定义-----------------------------------*/

class CTmCanDataRecv
{
public:
    CTmCanDataRecv();
    ~CTmCanDataRecv();
    int PutCanData(unsigned int uiCanId, char *pchCanData, int iDataLen); // 将接收到的CAN数据存储
    int ResolveCanId(unsigned int uiCanId, PTTmCanDataInfo ptCanDataInfo);  // 解析CAN ID
    int AddNewNodeData(PTTmCanDataInfo ptCanDataInfo, char *pchCanData, int iDataLen);  // 新增节点数据存储
    int SaveCanData(PTTmCanDataInfo ptCanDataInfo, CTmCanPackInfoMng *pcCanPackInfo,
                    char *pchCanData, int iDataLen);  // 保存接收到的CAN数据存储(已有存储空间)
    int GetCanData(char &chSrcNode, char &chDestNode, char *pchData, int &iDataLen);  // 获取组包完成的CAN数据包

private:
    map<char, CTmCanPackInfoMng*> m_mpRecvData;   // <发送节点, 组包信息>

};


#endif /* __TM_CAN_DATA_RECV_H__ */




