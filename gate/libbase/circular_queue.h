/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : circularqueue.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月17日
  最近修改   :
  功能描述   : circularqueue.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CIRCULARQUEUE_H__
#define __CIRCULARQUEUE_H__

class CCirQue
{
public:
    CCirQue(int iBuffSize);
    ~CCirQue();
    int  PutData(const char *pchBuff, int iCount);   // 往队列缓冲中放数据
    int  GetData(char *pchBuff, int iCount);         // 从队列中取数据
    int  GetDataTemp(char *pchBuff, int iCount);     // 从队列缓冲中临时取数据
    bool IsEmpty();          // 判断队列是否为空
    bool IsFull();           // 判断队列是否已满
    int  GetUsedSpace();     // 获取队列缓冲已使用的空间
    int  GetFreeSpace();     // 获取队列缓冲剩余空间
    int  SetFront();         // 设置队头指针
    int  Clear();            // 清空队列
    int  PrintCirQueBuff();  // 打印队列内容

private:
    char *m_pchBuff;     // 循环队列缓冲区
    int  m_iBuffSize;    // 缓冲区大小
    int  m_iFront;       // 循环队列对头
    int  m_iRear;        // 循环队列队尾
    int  m_iTempCnt;     // 临时取数据数量
};

#endif /* __CIRCULARQUEUE_H__ */




