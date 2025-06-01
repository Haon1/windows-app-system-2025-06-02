#include "CThread.h"
#include "IThreadHandler.h"

class CThreadPrivate
{
public:
    friend class CThread;
    CThreadPrivate(const std::string &strThreadName
                   , IThreadHandler *pTaskHandler
                   , int iInterval)
        : m_strThreadName(strThreadName)
        , m_Semaphore(0)
        , m_iInterval(iInterval)
        , m_pTaskHandler(pTaskHandler)
        , m_blExit(false)
    {

    }

    ~CThreadPrivate()
    {
        if (m_pTaskHandler)
        {
            delete m_pTaskHandler;
            m_pTaskHandler = NULL;
        }
    }

private:
    std::string     m_strThreadName;
    QSemaphore      m_Semaphore;
    int             m_iInterval;
    IThreadHandler  *m_pTaskHandler;
    bool            m_blExit;
};

CThread::CThread(const std::string &strThreadName
                 , IThreadHandler *pTaskHandler
                 , int iInterval)
    : QThread()
    , m_Private(new CThreadPrivate(strThreadName, pTaskHandler, iInterval))
{
    setObjectName(QString::fromStdString(strThreadName));
    if (m_Private && m_Private->m_pTaskHandler)
    {
        m_Private->m_pTaskHandler->AttachThread(this);
    }
}

CThread::~CThread()
{
    ExitThread();
    if (m_Private)
    {
        delete m_Private;
        m_Private = NULL;
    }
}

void CThread::WakeUp(int n)
{
    m_Private->m_Semaphore.release(n);
}

void CThread::SetInterval(int iMilliSeconds)
{
    m_Private->m_iInterval = iMilliSeconds;
}

void CThread::ExitThread()
{
    m_Private->m_blExit = true;
    WakeUp();
    wait();
}

void CThread::run()
{
    if (m_Private && m_Private->m_pTaskHandler)
    {
        m_Private->m_pTaskHandler->Init();
    }

    while (!m_Private->m_blExit)
    {
        int i_TimeOut = (m_Private->m_iInterval == 0) ? -1 : m_Private->m_iInterval;
        m_Private->m_Semaphore.tryAcquire(1, i_TimeOut);

        if (m_Private->m_blExit)
        {
            return ;
        }

        //Ö´ĞĞÈÎÎñ
        if (m_Private->m_pTaskHandler)
        {
            m_Private->m_pTaskHandler->HandleTask();
        }
    }

}
