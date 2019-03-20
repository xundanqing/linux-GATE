/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : main.cc
  版 本 号   :
  作    者   : wanggaofeng
  生成日期   :
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :
******************************************************************************/


#include "gate_module.h"


/*****************************************************************************
 函 数 名  : SignalHander
 功能描述  : 信号处理函数
 输入参数  : int signal
 输出参数  : 无
 返 回 值  :
 修改历史      :
  1.日    期   : 2013年11月8日 星期五
    作    者   : wuquanwei
    修改内容   : 新生成函数

*****************************************************************************/
void SignalHander(int signal)
{
    printf("Gate get signal ( signal : %d )( pid: %d )\n", signal, (int)(getpid()));

    if ( signal != 6 )  //28: SIGWINCH 6: SIGABRT
    {
        exit(-1);
    }
}


/*****************************************************************************
 函 数 名  : AvCaptureAllSignal
 功能描述  : 捕捉所有的信号
 输入参数  : 无
 输出参数  : 无
 返 回 值  :

 修改历史      :
  1.日    期   : 2012年12月1日 星期六
    作    者   : wuquanwei
    修改内容   : 新生成函数

*****************************************************************************/
void CaptureAllSignal()
{
    int iLoop;
    for(iLoop = 0; iLoop < 32; iLoop++)
    {
        if((iLoop == SIGCHLD) || (iLoop == SIGPIPE) || (iLoop == SIGWINCH))
        {
            continue;
        }

        signal(iLoop, SignalHander);
    }
}


/*****************************************************************************
 函 数 名  : main
 功能描述  : main函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int main(int argc, char* argv[])
{
    int         iResult;
    TSockAddrUn tGateSvrAddr;

    CaptureAllSignal();
    signal(SIGPIPE, SIG_IGN);

    tGateSvrAddr.sun_family = AF_UNIX;
    strcpy(tGateSvrAddr.sun_path, GATE_LOCAL_PATH);

    // 调用带参构造函数
    CGate cGate(&tGateSvrAddr);
    iResult = cGate.Init();
    if(RTN_SUCCESS != iResult)
    {
        ErrorPrint("Gate init failed. ");
        exit(-1);
    }

    cGate.ProcessData();

    return RTN_SUCCESS;
}




