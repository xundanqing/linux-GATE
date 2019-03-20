/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : resend_data_mng.h
  版 本 号   : 初稿
  作    者   : WangGaofeng
  生成日期   : 2016年3月28日
  最近修改   :
  功能描述   : 重发数据管理类
  函数列表   :
  修改历史   :
  1.日    期   : 2016年3月28日
    作    者   : WangGaofeng
    修改内容   : 创建文件

******************************************************************************/
#ifndef __RESEND_DATA_MNG_H__
#define __RESEND_DATA_MNG_H__


/*----------------------------------类定义-----------------------------------*/

class CReSendDataMng
{
public:
    CReSendDataMng();
    ~CReSendDataMng();
    int AddReSendData(PTReSndDtInfo ptReSendDataInfo, int iReSndDtInfoLen, CClient *pcGate);  // 增加重发数据
    int CheckReSendData(void *pvData, int iDataLen);       // 检查数据重发
    int StopReSendData(int iDataId);                       // 停止重发指定数据
    static CReSendDataMng* GetInstance();                  // 获取实例指针
    int SetReSendDataTimes(int iDataId, char chTimes);     // 设置指定数据发送次数
    int SetReSendDataInterval(int iDataId, int iInterval); // 设置指定数据发送间隔
    int RegReSendDataFunc(int iDataId, PReSndDtFunc pfnReSndDtFunc);      // 设置指定数据重发函数
    int RegReSendFnshFunc(int iDataId, PReSndFnshFunc pfnReSndFnshFunc);  // 设置指定数据重发超次函数

private:
    int m_iTmrId;  // 定时器ID
    int m_iDataId; // 重发数据ID(从1开始)
    static CReSendDataMng* m_pcInstance;   // 实例指针
    map<int, CReSendData*> m_mpReSndDtMap;  // 重发数据映射表
    class CGarbo  // 垃圾工
    {
    public:
        ~CGarbo()
        {
            if (NULL != CReSendDataMng::m_pcInstance)
            {
                delete CReSendDataMng::m_pcInstance;
            }
        }
    };
    static CGarbo m_cGarbo;  // 静态成员为析构CReSendDataMng单实例使用
};


#endif /* __RESEND_DATA_MNG_H__ */




