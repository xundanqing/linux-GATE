/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : gate.cc
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2015年6月17日
  最近修改   :
  功能描述   : CGate类的实现
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月17日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/


#include "gate_module.h"


/*****************************************************************************
 函 数 名  : CGate
 功能描述  : CGate类的构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
CGate::CGate()
{
}


/*****************************************************************************
 函 数 名  : CGate
 功能描述  : CGate类的构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
CGate::CGate(TSockAddrUn *ptGateSvrAddr) : m_cGateSvr(ptGateSvrAddr)
{
}


/*****************************************************************************
 函 数 名  : CGate
 功能描述  : CGate类的析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
CGate::~CGate()
{
}


/*****************************************************************************
 函 数 名  : Init
 功能描述  : 类的初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::Init()
{
    int iRet;

    // 启动GateSvr
    iRet = m_cGateSvr.StartGateSvr();
    if(RTN_FAIL == iRet)
    {
        ErrorPrint("GateSvr start fail. ");
        exit(-1);
    }

    // 启动调试线程
    iRet = CreatDebugCmdThread();
    if(RTN_FAIL == iRet)
    {
        ErrorPrint("Debug thread start fail. ");
        exit(-1);
    }

    iRet = CreatHrtBtThread();
    if(RTN_FAIL == iRet)
    {
        ErrorPrint("Heart beat thread start fail. ");
        exit(-1);
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ProcessData
 功能描述  : Gate数据转发处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ProcessData()
{
    int         iGateSvrFd;
    int         iFdMax;
    int         iResult;
    FdSet       fdReadSet;
    TTimeVal    tTimeOut;
    vector<int> vtMdlFd;
    vector<int>::iterator iter;

    while(1)
    {
        FD_ZERO(&fdReadSet);

        m_cGateSvr.GetAllMdlFd(vtMdlFd);
        m_cGateSvr.GetGateSvrFd(iGateSvrFd);

        iFdMax = iGateSvrFd;

        FD_SET(iGateSvrFd, &fdReadSet);

        for(iter = vtMdlFd.begin(); iter != vtMdlFd.end(); iter++)
        {
            if(*iter > iFdMax)
            {
                iFdMax = *iter;
            }

            FD_SET(*iter, &fdReadSet);
        }

        tTimeOut.tv_sec  = 2;
        tTimeOut.tv_usec = 0;

        iResult= select((iFdMax + 1), &fdReadSet, NULL, NULL, &tTimeOut);

        if(0 == iResult)
        {
            // ErrorPrint("select time out!!!");
            continue;
        }
        else if(iResult < 0)
        {
            ErrorPrint("select error happened errno = %d. ", errno);

            // 断开所有连接客户端
            m_cGateSvr.RemoveAllClient();

            continue;
        }
        else
        {
            // 若服务器Fd可读
            iResult = CheckGateSvrData(iGateSvrFd, fdReadSet);
            if(RTN_SUCCESS != iResult)
            {
                ErrorPrint("Check gate svr data error. ");
            }

            // 检查客户端Fd是否可读
            iResult = CheckClientData(vtMdlFd, fdReadSet);
            if(RTN_SUCCESS != iResult)
            {
                ErrorPrint("Check client data error. ");
                continue;
            }
        }
    }

    // 停止服务器
    m_cGateSvr.StopGateSvr();

    return RTN_FAIL;
}


/*****************************************************************************
 函 数 名  : ProcessCzjData
 功能描述  : 处理调试命令
 输入参数  : pArg----线程启动传入的CGate的实例
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
void* CGate::ProcessDebugCmd(void *pArg)
{
    int iRet;
    int iShowType;
    int iFd = FD_INVALID;
    int bOpenPipe = true;
    FdSet    fdReadSet;
    TTimeVal tTimeOut;
    CGate *pc3GGate = (CGate*)pArg;

    iRet = CreatFifo((char*)(GATE_DEBUG_FIFO));
    if (iRet != RTN_SUCCESS)
    {
        ErrorPrint("Create pipe file failed, path: %s. ", GATE_DEBUG_FIFO);
    }

    while(1)
    {
        if(bOpenPipe)
        {
            if(iFd > 0)
            {
                close(iFd);
            }

            iFd = open(GATE_DEBUG_FIFO, O_RDONLY | O_NONBLOCK);
            if(iFd < 0)
            {
                ErrorPrint("Open pipe file failed, path: %s", GATE_DEBUG_FIFO);
                sleep(2);     // 若打不开，延时2s再尝试
                continue;
            }
            else
            {
                bOpenPipe = false;
            }
        }

        FD_ZERO(&fdReadSet);
        FD_SET(iFd, &fdReadSet);

        tTimeOut.tv_sec  = 2;
        tTimeOut.tv_usec = 0;

        iRet = select((iFd + 1), &fdReadSet, NULL, NULL, &tTimeOut);

        if(0 == iRet)
        {
            //ErrorPrint("Debug select time out. ");
            continue;
        }
        else if(iRet < 0)
        {
            ErrorPrint("Debug select error. ");
            bOpenPipe = true;
            continue;
        }
        else
        {
            iRet = read(iFd, &iShowType, sizeof(iShowType));
            if(0 == iRet)
            {
                ErrorPrint("Debug read pipe error. ")
                bOpenPipe = true;
                continue;
            }

            iRet = pc3GGate->ShowGateRunInfo(iShowType);
            if(RTN_SUCCESS != iRet)
            {
                ErrorPrint("Debug show gate run info error. ");
                continue;
            }
        }
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CheckMdlHrtBtTime
 功能描述  : 检查模块心跳超时
 输入参数  : pArg----线程启动传入的CGate的实例
 输出参数  : 无
 返 回 值  : 无
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
void* CGate::CheckMdlHrtBtTime(void *pArg)
{
    CGate *pcGate = (CGate*)pArg;

    while(1)
    {
        sleep(30);

        ErrorPrint("CheckMdlHrtBtTime.");
        pcGate->CheckHrtBtTimeOut();
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CreatHrtBtThread
 功能描述  : 创建心跳处理线程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::CreatHrtBtThread()
{
    ThreadId tHrtBtThread;
    int iRet;

    iRet = pthread_create(&tHrtBtThread, NULL, CheckMdlHrtBtTime, this);
    if(iRet < 0)
    {
        ErrorPrint("Creat heart beat thread failed. ");
        return RTN_FAIL;
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CreatDebugCmdThread
 功能描述  : 创建调试命令处理线程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::CreatDebugCmdThread()
{
    // 暂不启动调试线程
#if 0
    ThreadId tDebugThread;
    int iRet;

    iRet = pthread_create(&tDebugThread, NULL, ProcessDebugCmd, this);
    if(iRet < 0)
    {
        ErrorPrint("Creat debug cmd thread failed. ");
        return RTN_FAIL;
    }
#endif

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ProcessGateData
 功能描述  : 处理发给Gate的数据包
 输入参数  : iFd-------------向GateSvr发送数据的fd
             ptPackInfo------包描述信息
             pchPackData-----包数据
             iDataLen--------包长度
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ProcessGateData(int iFd, PTPackInfo ptPackInfo, char *pchPackData, int iDataLen)
{
    int iResult;

    switch(ptPackInfo->chCmd)
    {
        case GATE_MOUDLE_REG_CMD:  // 模块注册包
        {
            // 注册模块
            iResult = m_cGateSvr.UpdateGateClientType(iFd, ptPackInfo->chSrcMdl);
            if(RTN_SUCCESS != iResult)
            {
                return RTN_FAIL;
            }

            // 发送应答包
            SendRegAckPacket(iFd, ptPackInfo);

            break;
        }
        case GATE_HEART_BEAT_CMD:
        {
            ErrorPrint("Recv heart beat packet, module type is %2x. ", ptPackInfo->chSrcMdl);
            iResult = m_cGateSvr.UpdateHrtBtTime(iFd, ptPackInfo->chSrcMdl);
            if(RTN_SUCCESS != iResult)
            {
                return RTN_FAIL;
            }

            break;
        }

        default:
        {
            ErrorPrint("Gate packet cmd = %d, not process. ", ptPackInfo->chCmd);

            return RTN_FAIL;
        }
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ProcessBroadcast
 功能描述  : 处理广播消息
 输入参数  : iFd------------发送广播数据源的fd
             pchPackData----广播数据
             iDataLen-------广播数据长度
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ProcessBroadcast(int iFd, char *pchPackData, int iDataLen)
{
    int         iRet;
    vector<int> vtAllMdl;
    vector<int>::iterator iter;

    iRet = m_cGateSvr.GetAllMdlFd(vtAllMdl);
    if(RTN_SUCCESS != iRet)
    {
        ErrorPrint("Get all module fd error. ");
        return RTN_FAIL;
    }

    for(iter = vtAllMdl.begin(); iter != vtAllMdl.end(); iter++)
    {
        if(*iter == iFd)  // 广播消息不发给自己
        {
            continue;
        }
        else
        {
            iRet = m_cGateSvr.SendData(*iter, pchPackData, iDataLen);
            if(RTN_SUCCESS != iRet)
            {
                ErrorPrint("Send broadcase data error, fd = %d. ", *iter);
                continue;
            }
        }
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : SendAckPacket
 功能描述  : 发送模块注册应答消息
 输入参数  : iFd-----------应答包目的模块的fd
             ptPackInfo----模块注册包的包描述信息
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::SendRegAckPacket(int iFd, PTPackInfo ptPackInfo)
{
    int   iOffset = 0;
    int   iResult;
    short sPackLen;
    short sCrc;
    CCrcPublic cCrc;
    PTPackInfo ptPacketInfo;

    char *pchBuff = new char[REG_ACK_PACK_LEN];

    memset(pchBuff, 0x00, REG_ACK_PACK_LEN);

    strncpy(pchBuff, "####", REG_ACK_PACK_PREFIX_LEN);
    iOffset += REG_ACK_PACK_PREFIX_LEN;

    sPackLen = REG_ACK_PACK_LEN;
    sPackLen = Reverse16(sPackLen);  // 大小端转换
    memcpy((pchBuff + iOffset), (char*)(&sPackLen), sizeof(sPackLen));
    iOffset += sizeof(sPackLen);

    ptPacketInfo = (PTPackInfo)(pchBuff + iOffset);
    ptPacketInfo->chDestMdl = ptPackInfo->chSrcMdl;
    ptPacketInfo->chSrcMdl  = MODULE_TYPE_GATE;
    ptPacketInfo->chPackId  = ptPackInfo->chPackId;
    ptPacketInfo->chCmd     = ptPackInfo->chCmd;
    iOffset += sizeof(TPackInfo);

    sCrc = cCrc.Crc16((unsigned char*)pchBuff, REG_ACK_PACK_LEN - 2);  // 去掉两个crc校验字节长度
    sCrc = Reverse16(sCrc);
    memcpy((pchBuff + iOffset), (char*)(&sCrc), sizeof(sCrc));

    iResult = m_cGateSvr.SendData(iFd, pchBuff, REG_ACK_PACK_LEN);
    if(RTN_SUCCESS != iResult)
    {
        ErrorPrint("Send regist ack packet error. ");
        delete[] pchBuff;

        return RTN_FAIL;
    }

    delete[] pchBuff;

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CheckGateSvrData
 功能描述  : 检查服务器端是否可读
 输入参数  : iGateSvrFd----GateSvr的fd
             fdReadSet-----select调用的描述符集
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::CheckGateSvrData(int &iGateSvrFd, FdSet &fdReadSet)
{
    int        iFd;
    SocketLen  sklAddrLen;
    TSockAddr  tSockAddr;

    memset(&tSockAddr, 0x00, sizeof(TSockAddr));
    sklAddrLen = 0;

    if(FD_ISSET(iGateSvrFd, &fdReadSet))
    {
        iFd = m_cGateSvr.AcceptConnect(&tSockAddr, sklAddrLen);
        if(ACCEPT_ERROR == iFd)
        {
            ErrorPrint("Accept connect error. ");
            exit(-1);
        }
        else
        {
            ErrorPrint("GateSvr client %d have connected, type unknow. ", iFd);

            // 注册客户端
            m_cGateSvr.AddGateClient(iFd);
        }
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CheckClientData
 功能描述  : 检查客户端是否可读
 输入参数  : vtMdlFd------GateSvr客户端fd集
             fdReadSet----select调用的描述符集
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::CheckClientData(vector<int> &vtMdlFd, FdSet &fdReadSet)
{
    int  iResult;
    int  iFd;
    int  iDestFd;
    int  iRecvNum;
    int  iGatePackLen;
    bool bError = false;   // 是否有异常发生
    char achReadBuff[PACK_LEN_MAX];
    char achGateBuff[PACK_LEN_MAX];
    CDecoupler  *pcDecoupler;
    TPackInfo   tPackInfo;
    vector<int>::iterator iter;

    for(iter = vtMdlFd.begin(); iter != vtMdlFd.end(); iter++)
    {
        if(FD_ISSET(*iter, &fdReadSet))
        {
            iFd = *iter;

            iResult= m_cGateSvr.RecvData(iFd, achReadBuff, PACK_LEN_MAX, iRecvNum);
            if(RTN_SUCCESS != iResult)
            {
                iResult = m_cGateSvr.RemoveClient(iFd);
                if(RTN_SUCCESS != iResult)
                {
                    ErrorPrint("Remove client fd = %d error. ", iFd);
                }

                return RTN_FAIL;
            }
            else
            {
                pcDecoupler = m_cGateSvr.GetFdDecoupler(iFd);
                if(NULL == pcDecoupler)
                {
                    ErrorPrint("Cant' find decopuler, then continue loop. ");
                    continue;
                }

                iResult = pcDecoupler->PutData(achReadBuff, iRecvNum);
                if(RTN_SUCCESS != iResult)
                {
                    ErrorPrint("Put date into decoupler error. ");
                    continue;
                }

                // 正常情况下一次接收一包数据，为了防止客户端数据发送过快一次收到多包数据，加了循环取包
                // 取包处理过程中如果出现异常，不立即返回，丢弃正在处理的包，进行下次取包，直到解包器空
                while(!(pcDecoupler->IsDcplrEmpty()))
                {
                    //获取包描述信息
                    iResult = pcDecoupler->GetPackInfo(&tPackInfo, achGateBuff, PACK_LEN_MAX, iGatePackLen);
                    if(RTN_SUCCESS != iResult)
                    {
                        bError = true;
                        ErrorPrint("Get pack infomation error src module fd = %d. ", iFd);
                        break;   // 若取包异常则跳出，防止发生死循环
                    }

                    // 是否发送给3GGate的包
                    if(MODULE_TYPE_GATE == tPackInfo.chDestMdl)
                    {
                        iResult = ProcessGateData(iFd, &tPackInfo, achGateBuff, iGatePackLen);
                        if(RTN_SUCCESS != iResult)
                        {
                            bError = true;
                            ErrorPrint("Process gate data error. ");
                            PrintBuffer((char*)("achGateBuff"), achGateBuff, iGatePackLen);
                            continue;
                        }
                    }
                    else if(MODULE_TYPE_BROADCAST == tPackInfo.chDestMdl) // 广播消息
                    {
                        iResult = ProcessBroadcast(iFd, achGateBuff, iGatePackLen);
                        if(RTN_SUCCESS != iResult)
                        {
                            bError = true;
                            ErrorPrint("Process broadcast data error. ");
                            continue;
                        }
                    }
                    else
                    {
                        // 获取包目标模块的Fd
                        iResult = m_cGateSvr.GetFdByMdlType(tPackInfo.chDestMdl, iDestFd);
                        if(RTN_SUCCESS != iResult)
                        {
                            bError = true;
                            ErrorPrint("Can't find moudle type %2x corresponding module, src module %2x. ",
                                       tPackInfo.chDestMdl, tPackInfo.chSrcMdl);
                            PrintBuffer((char*)("packet"), achGateBuff, iGatePackLen);
                            continue;
                        }

                        // 将包转给目标模块
                        iResult = m_cGateSvr.SendData(iDestFd, achGateBuff, iGatePackLen);
                        if(RTN_SUCCESS != iResult)
                        {
                            bError = true;
                            ErrorPrint("Send data to destination fd = %d error. ", iDestFd);

                            iResult = m_cGateSvr.RemoveClient(iDestFd);
                            if(RTN_SUCCESS != iResult)
                            {
                                ErrorPrint("Remove client fd = %d error. ", iDestFd);
                            }

                            continue;
                        }
                    }
                }
            }
        }
    }

    if(bError)
    {
        return RTN_FAIL;
    }
    else
    {
        return RTN_SUCCESS;
    }
}


/*****************************************************************************
 函 数 名  : ShowGateRunInfo
 功能描述  : 打印Gate的运行信息
 输入参数  : iShowType----需要打印的运行信息类型
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ShowGateRunInfo(int iShowType)
{
    int iResult;

    switch(iShowType)
    {
        case GATE_INFO_GATESVR:
        {
            iResult = ShowGateSvrInfo();
            if(iResult != RTN_SUCCESS)
            {
                ErrorPrint("Show gate svr info failed. ");
                return RTN_FAIL;
            }

            break;
        }
        case GATE_INFO_MODULE:
        {
            iResult = ShowModuleInfo();
            if(iResult != RTN_SUCCESS)
            {
                ErrorPrint("Show module info failed. ");
                return RTN_FAIL;
            }

            break;
        }
        case GATE_INFO_ALL:
        {
            iResult = ShowGateSvrInfo();
            if(iResult != RTN_SUCCESS)
            {
                ErrorPrint("Show gate svr info failed. ");
                return RTN_FAIL;
            }

            iResult = ShowModuleInfo();
            if(iResult != RTN_SUCCESS)
            {
                ErrorPrint("Show module info failed. ");
                return RTN_FAIL;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ShowGateSvrInfo
 功能描述  : 打印GateSvr的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ShowGateSvrInfo()
{
    int iFd;
    int iStatus = 0;
    int iRet;

    iRet = m_cGateSvr.GetGateSvrFd(iFd);
    if(iRet != RTN_SUCCESS)
    {
        ErrorPrint("Get gate svr fd error. ");
        return RTN_FAIL;
    }

    m_cGateSvr.GetGateSvrStatus(iStatus);

    printf(PURPLE"-------------------------------Gate svr info-------------------------------\n");
    printf("                   GateSvr Fd                        Status\n");

    if(GATESVR_STATUS_START == iStatus)
    {
        printf("                      %2d                             Start\n", iFd);
    }
    else
    {
        printf("                      %2d                             Stop\n", iFd);
    }

    printf("---------------------------------------------------------------------------\n"NONE);

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : ShowModuleInfo
 功能描述  : 打印连接模块的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::ShowModuleInfo()
{
    int  iMdlNum;
    int  iIdx;
    char *apchMdlType[13] = {(char*)("GATE"), (char*)("AV"), (char*)("GUI"), (char*)("BZQ"),
                             (char*)("PHONE"), (char*)("ACCESS/BASIC"),(char*)("MONITOR"), (char*)("PARA"),
                             (char*)("MCU"), (char*)("SCHDL"), (char*)("DATA_PROC"), (char*)("UPDATE"),
                             (char*)("SVR")};
    map<int, PTGateClientInfo> mapModule;
    map<int, PTGateClientInfo>::iterator iter;

    m_cGateSvr.GetModuleInfo(mapModule);

    iMdlNum = mapModule.size();

    printf(YELLOW"--------------------------Gate svr connect module--------------------------\n");
    printf("             Module Fd                                Module Type          \n");

    for(iter = mapModule.begin(); iter != mapModule.end(); iter++)
    {
        if(0x40 == iter->second->iModuleType)
        {
            iIdx = 12;
        }
        else
        {
            iIdx = iter->second->iModuleType - 0x31;   // 0x31为GATE
        }

        printf("                %2d                                       %s\n",
               iter->first, apchMdlType[iIdx]);
    }

    printf("---------------------------------------------------------------------------\n");

    printf("Module total num = %d.\n", iMdlNum);

    printf("---------------------------------------------------------------------------\n"NONE);

    return RTN_SUCCESS;
}


/*****************************************************************************
 函 数 名  : CheckHrtBtTimeOut
 功能描述  : 打印连接模块的信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RTN_SUCCESS----成功 正常
             RTN_FAIL-------失败 异常
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
*****************************************************************************/
int CGate::CheckHrtBtTimeOut()
{
    int iRet = m_cGateSvr.CheckMdlHrtBtTimeOut();

    return iRet;
}




