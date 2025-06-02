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
        //����������ָ���������ʹ��
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
    //�ȴ����߳�����
    CreateThreadHandlers();
    m_listThread.clear();   //����߳��б�
    struct _TASKATTR
    {
        std::string         threadName;     //�߳���
        IThreadHandler      *threadHandler;//�߳�����
        int                 interval;       //�߳�ִ�м��������msִ��һ������
        QThread::Priority    m_emPriority;  //���ȼ�
    } taskattr[] =
    {
    {"data_collect", m_mapThreadHandlers[E_THREAD_HANDLER_DATA_COLLECT], 1000,  QThread::HighPriority },
    {"test",         m_mapThreadHandlers[E_THREAD_HANDLER_TEST],         2000, QThread::NormalPriority},
    };

    for (INT32U i = 0; i < ARRAYSIZE(taskattr); i++)
    {
        if (NULL == taskattr[i].threadHandler)
        {
            //�߳�����ΪNULL�򲻴����߳�
            continue;
        }
        CThread *p_Thread = new CThread(taskattr[i].threadName,\
                                        taskattr[i].threadHandler,\
                                        taskattr[i].interval);

        if (NULL != p_Thread)
        {
            m_listThread.push_front(p_Thread);
            p_Thread->start();
            p_Thread->setPriority(taskattr[i].m_emPriority);    //�������ȼ�
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
    g_SystemConfig; //����ϵͳ����

//    CreateSysThread();  //�������߳�
    CreateUi();         //����UI����
}

