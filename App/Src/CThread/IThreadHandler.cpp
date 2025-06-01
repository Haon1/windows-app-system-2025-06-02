#include "IThreadHandler.h"

IThreadHandler::IThreadHandler(QObject *parent)
    : QObject(parent)
    , m_pThread(NULL)
{

}

IThreadHandler::~IThreadHandler()
{

}

void IThreadHandler::Init()
{

}

void IThreadHandler::AttachThread(CThread *pThread)
{
    m_pThread = pThread;
}
