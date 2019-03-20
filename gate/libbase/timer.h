/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : timer.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月19日
  最近修改   :
  功能描述   : 定时器管理类
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月19日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__

/*---------------------------------类型定义----------------------------------*/

typedef boost::function<int(void*, int)>  PTimerFunc;   // 定时器回调函数定义

typedef struct timezone   TTimeZone;


/*----------------------------------宏定义-----------------------------------*/

#define BIND_TIMER_FUNC(CLASS, FUNCTION)   bind(&CLASS::FUNCTION, this, _1, _2)
#define BIND_TIMER_FUNC_INST(CLASS, FUNCTION, INSTANCE) bind(&CLASS::FUNCTION, INSTANCE, _1, _2)

#define TIMER_PRIORITY_HIGH           (0x01)   // 定时器优先级高
#define TIMER_PRIORITY_NORMAL         (0x02)   // 定时器优先级正常
#define TIMER_PRIORITY_LOW            (0x03)   // 定时器优先级低

#define TIMER_ID_INVALID              (-1)     // 定时器ID无效值


/*---------------------------------结构定义----------------------------------*/
#pragma pack(1)

typedef struct tagTTimerInfo
{
    int        iTimeOut;       // 定时器超时时长(单位ms)
    char       chPriority;     // 定时器触发优先级(用于多个定时器同时超时回调函数调用时序控制)
    TTimeVal   tTmVal;         // 定时器上次超时时间
    PTimerFunc pfnTmrFunc;     // 定时器回调函数
    char       achTmrName[0];  // 定时器名字
} TTimerInfo, *PTTimerInfo;

#pragma pack()


/*----------------------------------类定义-----------------------------------*/

class CTimer
{
public:
    CTimer();
    ~CTimer();
    int AddTimer(char *pchTmrName, int iTmrLen, char chPriority, PTimerFunc pfnTmrFunc, int &iTmrId); // 增加定时器
    int DelTimer(int iTimerId);      // 通过定时器ID删除定时器
    int DelTimer(char *pchTmrName);  // 通过定时器名字删除定时器
    static CTimer *GetInstance();    // 获取定时器实例(单实例模式)
    int CheckTimeOut();  // 检查定时器超时
private:
    int AddTimer(PTTimerInfo ptTmrInfo, int &iTimerId);  // 增加定时器

private:
    static CTimer *m_pcTmrInst;       // 实例指针
    int m_iTmrIdMax;                  // 定时器Id最大值,用于定时器Id分配
    map<int, PTTimerInfo> m_mpTimer;  // <定时器Id, 定时器信息>
    class CGarbo  // 垃圾工
    {
    public:
        ~CGarbo()
        {
            if (NULL != CTimer::m_pcTmrInst)
            {
                delete CTimer::m_pcTmrInst;
            }
        }
    };
    static CGarbo m_cGarbo;  // 静态成员为析构CTimer单实例使用
};


#endif /* __TIMER_H__ */




