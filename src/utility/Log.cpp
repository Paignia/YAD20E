#include "Log.h"

//SINGLETON
GlobalLog* GlobalLog::g_log=NULL;


GlobalLog::GlobalLog()
{
}

GlobalLog* GlobalLog::Instance()
{

  if(!g_log)
    g_log=new GlobalLog();
  return g_log;
}

