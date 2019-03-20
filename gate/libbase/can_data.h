/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : can_data.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年11月09日
  最近修改   :
  功能描述   : CAN数据业务类相关定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月09日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CAN_DATA_H__
#define __CAN_DATA_H__


/*---------------------------------类型定义----------------------------------*/

typedef boost::function<int(int, char*, int)>  PCanIdFunc;  // Can Id对应回调函数定义


/*----------------------------------宏定义-----------------------------------*/

#define BIND_CAN_ID_FUNC(CLASS, FUNCTION)  bind(&CLASS::FUNCTION, this, _1, _2, _3)


/*---------------------------------结构定义----------------------------------*/
#pragma pack(1)

// 设备Can数据描述
typedef struct tagTCanDataFromDev
{
    unsigned int  uiCanId;       // CAN ID
    unsigned int  uiDataLen;     // CAN数据长度
    unsigned char ucCanPort;     // CAN口 : CAN_PORT_1, CAN_PORT_2
    unsigned char aucCanData[0]; // CAN数据
} TCanDataFromDev, *PTCanDataFromDev;

#pragma pack()


/*----------------------------------类定义-----------------------------------*/

class CCanData
{
public:
    CCanData();
    virtual ~CCanData();
    virtual int Init();  // 初始化
    virtual int ProcessCanData(int iCanId, char *pcCanData, int iDataLen);  // 处理CAN数据
    virtual int RegCanIdFunc(int iCanId, PCanIdFunc pfnCanIdFunc);  // 注册CAN ID处理函数

protected:
    map<int, PCanIdFunc> m_mpCanIdFuncMap; // <CanId, CanId对应回调>

};


#endif /* __CAN_DATA_H__ */



