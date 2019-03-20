/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : cmd_proc.h
  版 本 号   : 初稿
  作    者   : WangGaofeng
  生成日期   : 2016年3月4日
  最近修改   :
  功能描述   : 指令处理类模板
  函数列表   :
  修改历史   :
  1.日    期   : 2016年3月4日
    作    者   : WangGaofeng
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CMD_PROC_H__
#define __CMD_PROC_H__


/*----------------------------------类定义-----------------------------------*/

template <typename TypeCmd, typename TypeFunc, typename TypeFnData, typename TypeFnDataLen>
class CCmdProc
{
public:
    CCmdProc() {}
    ~CCmdProc() {}
    int RegCmdProcFunc(TypeCmd tpCmd, TypeFunc tpCmdProcFunc);   // 注册处理函数
    int ProcCmdData(TypeCmd tpCmd, TypeFnData tpData, TypeFnDataLen tpDataLen);  // 处理指令数据
protected:
    map<TypeCmd, TypeFunc> m_mpCmdProcMap;   // 命令字与处理函数映射表
};


/*----------------------------------类实现-----------------------------------*/

template <typename TypeCmd, typename TypeFunc, typename TypeFnData, typename TypeFnDataLen>
int CCmdProc<TypeCmd, TypeFunc, TypeFnData, TypeFnDataLen>::RegCmdProcFunc(TypeCmd tpCmd, TypeFunc tpCmdProcFunc)
{
    typename map<TypeCmd, TypeFunc>::iterator iter = m_mpCmdProcMap.find(tpCmd);
    if(iter != m_mpCmdProcMap.end())
    {
        cout<<"Cmd "<<tpCmd<<" has been registered. "<<endl;
        return RTN_FAIL;
    }
    else
    {
        m_mpCmdProcMap[tpCmd] = tpCmdProcFunc;
    }

    return RTN_SUCCESS;
}


template <typename TypeCmd, typename TypeFunc, typename TypeFnData, typename TypeFnDataLen>
int CCmdProc<TypeCmd, TypeFunc, TypeFnData, TypeFnDataLen>::ProcCmdData(TypeCmd tpCmd, TypeFnData tpData, TypeFnDataLen tpDataLen)
{
    typename map<TypeCmd, TypeFunc>::iterator iter = m_mpCmdProcMap.find(tpCmd);
    if(iter != m_mpCmdProcMap.end())
    {
        iter->second(tpCmd, tpData, tpDataLen);
    }
    else
    {
        cout<<"Can't find cmd "<<tpCmd<<" process function. "<<endl;
        return RTN_FAIL;
    }

    return RTN_SUCCESS;
}


#endif /* __CMD_PROC_H__ */




