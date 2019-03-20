/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : can_data_mng.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年11月09日
  最近修改   :
  功能描述   : CAN数据管理类相关定义
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月09日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CAN_DATA_MNG_H__
#define __CAN_DATA_MNG_H__


class CCanDataMng
{
public:
    CCanDataMng();
    ~CCanDataMng();
    int Init();  // 初始化
    int ProcessCanData(int iCanId, char *pchCanData, int iDataLen);  // 处理CAN数据
    int AddCanDataItem(int iItemType, CCanData *pcCanData);  // 增加CAN数据处理项
    int RemoveCanDataItem(int iItemType);  // 删除CAN数据处理项

private:
    map<int, CCanData*> m_mpCanDataMng;  // Can数据管理容器 <CAN数据处理项类型, 处理项实例指针>

};


#endif /* __CAN_DATA_MNG_H__ */




