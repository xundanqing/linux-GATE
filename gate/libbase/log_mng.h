/******************************************************************************

                  版权所有 (C), 2001-2011, 郑州天迈科技有限公司

 ******************************************************************************
  文 件 名   : logmng.h
  版 本 号   : 初稿
  作    者   : tm8731_xgui
  生成日期   : 2015年7月11日
  最近修改   :
  功能描述   : logmng.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月11日
    作    者   : tm8731_xgui
    修改内容   : 创建文件

******************************************************************************/
#ifndef __LOGMNG_H__
#define __LOGMNG_H__

#define LOG_CONFIG "/mnt/flash/gate_log.conf"
#define LOG_PATH   "/mnt/nand/log/"
#define LOG_CAT    "gate_cat"


#define LOG_CONFIG_TEXT   \
"[global]\n"\
"strict init = true\n"\
"buffer min = 1024\n"\
"buffer max = 2048\n"\
"#日志访问权限,600 只允许当前用户访问\n"\
"file perms = 600\n"\
"[formats]\n"\
"simple	= \"%d.%-8.8us %-5V [%-8.8p.%-8.8t %F %L] %m%n\"\n"\
"simple1 = \"[%F %L] %m%n\"\n"\
"[rules]\n"\
"gate_cat.warn		>stderr;simple1\n"\
"gate_cat.ERROR	\"/mnt/nand/log/gate.txt\",100kb * 3 ~ \"/mnt/nand/log/gate.txt.#r\";simple\n"


typedef zlog_category_t     TLog;

extern TLog *g_ptLogHdl;

// 分级打印,不同级别颜色不同
#define LOG_DEBUG(format, args...)        zlog_debug(g_ptLogHdl, LIGHT_GREEN format NONE, ##args) // 浅绿
#define LOG_INFO(format, args...)         zlog_info(g_ptLogHdl, BLUE format NONE, ##args)         // 蓝
#define LOG_NOTICE(format, args...)       zlog_notice(g_ptLogHdl, YELLOW format NONE, ##args)     // 黄
#define LOG_WARN(format, args...)         zlog_warn(g_ptLogHdl,  CYAN format NONE, ##args)        // 青
#define LOG_ERROR(format, args...)        zlog_error(g_ptLogHdl, PURPLE format NONE, ##args)      // 紫
#define LOG_FATAL(format, args...)        zlog_fatal(g_ptLogHdl,  RED format NONE, ##args)        // 红


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

int  InitLogMng(); // 初始化日志模块
int  CheckLogCfgFile(const char *pchFile);   // 检查日志配置文件
int  CheckLogSaveDir(const char *pchLogDir); // 检查日志文件目录
TLog *GetLogHandler();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LOGMNG_H__ */




