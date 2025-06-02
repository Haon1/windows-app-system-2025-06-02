#include "CAppSystem.h"
#include "CSystemConfig.h"
#include "CMainWindow.h"
#include "CThread.h"
#include "CTestHandler.h"
#include "CDataCollectHandler.h"
#include "CUiToolkit.h"

#include <QDebug>

CAppSystem *CAppSystem::m_pInstance = NULL;

CAppSystem::CAppSystem()
    : m_pMainWindow(NULL)
{
}

VOID CAppSystem::CreateUi()
{
    if (!m_pMainWindow)
    {
        m_pMainWindow = new CMainWindow();
        //保存主界面指针后续方便使用
        g_UiToolkit->SaveMainWindowPtr(m_pMainWindow);
    }
    m_pMainWindow->show();
}

VOID CAppSystem::CreateThreadHandlers()
{
    m_mapThreadHandlers[E_THREAD_HANDLER_DATA_COLLECT] = new CDataCollectHandler();
    m_mapThreadHandlers[E_THREAD_HANDLER_TEST]         = new CTestHandler();
}

VOID CAppSystem::CreateSysThread()
{
    //先创建线程任务
    CreateThreadHandlers();
    m_listThread.clear();   //清空线程列表
    struct _TASKATTR
    {
        std::string         threadName;     //线程名
        IThreadHandler      *threadHandler;//线程任务
        int                 interval;       //线程执行间隔（多少ms执行一次任务）
        QThread::Priority    m_emPriority;  //优先级
    } taskattr[] =
    {
    {"data_collect", m_mapThreadHandlers[E_THREAD_HANDLER_DATA_COLLECT], 1000,  QThread::HighPriority },
    {"test",         m_mapThreadHandlers[E_THREAD_HANDLER_TEST],         2000, QThread::NormalPriority},
    };

    for (INT32U i = 0; i < ARRAYSIZE(taskattr); i++)
    {
        if (NULL == taskattr[i].threadHandler)
        {
            //线程任务为NULL则不创建线程
            continue;
        }
        CThread *p_Thread = new CThread(taskattr[i].threadName,\
                                        taskattr[i].threadHandler,\
                                        taskattr[i].interval);

        if (NULL != p_Thread)
        {
            m_listThread.push_front(p_Thread);
            p_Thread->start();
            p_Thread->setPriority(taskattr[i].m_emPriority);    //设置优先级
        }
    }
}

CAppSystem::~CAppSystem()
{
    RELEASEIF(m_pMainWindow);
    for (INT32 i = 0; i < m_listThread.count(); i++)
    {
        RELEASEIF(m_listThread[i]);
    }
}

CAppSystem *CAppSystem::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new CAppSystem();
    }
    return m_pInstance;
}

VOID CAppSystem::Initialize()
{
    g_SystemConfig; //加载系统配置

//    CreateSysThread();  //创建多线程
    CreateUi();         //创建UI界面
}

